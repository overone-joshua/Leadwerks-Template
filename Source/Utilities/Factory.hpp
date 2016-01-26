#ifndef _FACTORY_HPP_
	#define _FACTORY_HPP_

#pragma once
#include <map>
#include <string>

#define CLASS_TYPE(classname) \
	public: \
		virtual const char* ObjectType() { return ClassType(); } \
		static const char* ClassType() { return #classname; }

template <typename T>
class FactoryMakerBase {
public:
	virtual T* Create() const = 0;
	virtual const char* ObjectType() const = 0;
}; // end class FactoryMakerBase.

template <typename Type, typename Base>
class FactoryMaker : public FactoryMakerBase < Base > {
public:
	virtual Base* Create() const {
		return new Type;
	}

	virtual const char* ObjectType() const {
		return Type::ClassType();
	}
}; // end class FactoryMaker.

template <typename T>
class Factory {
public:
	typedef FactoryMakerBase<T> FactoryType;

	T* Create(const std::string& objType);
	void Register(FactoryType* pMaker);
	void Unregister(const std::string& objType);

private:
	typedef std::map<std::string, FactoryType*> TypeMap;
	TypeMap m_makers;
}; // end class Factory.

template <typename T>
void Factory<T>::Register(FactoryType* pMaker) {
	assert(pMaker != nullptr);
	m_makers[std::string(pMaker->ObjectType())] = pMaker;
} // end Register.

template <typename T>
void Factory<T>::Unregister(const std::string& objType) {
	typename TypeMap::iterator it = m_makers.find(objType);
	if (it != m_makers.end()) {
		FactoryType* pMaker = (*it).second;
		assert(pMaker != nullptr);
		delete pMaker;
		m_makers.erase(it);
	}
} // end Unregister.

template <typename T>
T* Factory<T>::Create(const std::string& objType) {
	typename TypeMap::iterator it = m_makers.find(objType);
	if (it == m_makers.end())
		return nullptr;

	FactoryType* pMaker = (*it).second;
	return pMaker->Create();
} // end Create.

#endif // _FACTORY_HPP_