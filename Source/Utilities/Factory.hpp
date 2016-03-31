/*-------------------------------------------------------
                    <copyright>
    
    File: Factory.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Factory utility.
                 The Factory class provides a clean way
                 to easily register and create objects
                 of a similar base class.
    
    Functions: 1. T* Create(const std::string& objType);
                                                         
               2. void Register(FactoryYupe* pMaker);
               
               3. void Unregister(const std::string& objType);
               
    Example:
     
        Factory<State> gStateFactory;
        
        gStateFactory.Register(new FactoryMaker<DefaultState, State>);
    
        gStateFactory.Unregister(DefaultState::ClassType());

---------------------------------------------------------*/

#ifndef _FACTORY_HPP_
	#define _FACTORY_HPP_

#pragma once
#include <map>
#include <string>

#define CLASS_TYPE(classname) \
	public: \
		virtual const char* ObjectType() { return ClassType(); } \
		static const char* ClassType() { return #classname; }

template <typename T, typename... ARGS>
class FactoryMakerBase
{
public:
	virtual T* Create(ARGS... args) const = 0;
	virtual const char* ObjectType() const = 0;
}; // end class FactoryMakerBase.

template <typename Type, typename Base, typename... ARGS>
class FactoryMaker : public FactoryMakerBase < Base , ARGS...>
{
public:
	virtual Base* Create() const
    {
		return new Type;
	}

	virtual const char* ObjectType() const
    {
		return Type::ClassType();
	}
}; // end class FactoryMaker.

template <typename T>
class Factory {
public:
	typedef FactoryMakerBase<T> FactoryType;

	template <typename... ARGS>
	T* Create(const std::string& objType, ARGS... args);
	void Register(FactoryType* pMaker);
	void Unregister(const std::string& objType);

private:
	typedef std::map<std::string, FactoryType*> TypeMap;
	TypeMap m_makers;
}; // end class Factory.

template <typename T>
void Factory<T>::Register(FactoryType* pMaker)
{
	assert(pMaker != nullptr);
	m_makers[std::string(pMaker->ObjectType())] = pMaker;
} // end Register.

template <typename T>
void Factory<T>::Unregister(const std::string& objType)
{
	typename TypeMap::iterator it = m_makers.find(objType);
	if (it != m_makers.end())
    {
		FactoryType* pMaker = (*it).second;
		assert(pMaker != nullptr);
		delete pMaker;
		m_makers.erase(it);
	}
} // end Unregister.

template <typename T>
template <typename... ARGS>
T* Factory<T>::Create(const std::string& objType, ARGS... args)
{
	typename TypeMap::iterator it = m_makers.find(objType);
	if (it == m_makers.end())
		return nullptr;

	FactoryType* pMaker = (*it).second;
	return pMaker->Create(std::forward<ARGS>(args)...);
} // end Create.

#endif // _FACTORY_HPP_