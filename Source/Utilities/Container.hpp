/*-------------------------------------------------------
                    <copyright>
    
    File: Container.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Container utility.
                 This file contains the source for a
                 very simple and lightweight Dependency
                 Injection service.
    
    Functions: 1. template <typename I, class C>
                  I* Register(C* pInstance);
                  
               2. template <typename I>
                  I* Resolve(void);
                  
               3. template <typename I>
                  bool TryResolve(I* value);                     

---------------------------------------------------------*/

#ifndef _CONTAINER_HPP_
    #define _CONTAINER_HPP_
    
#pragma once
#include <exception>
#include <map>
#include <string>

class Container_Resolve_Exception : public std::exception
{
	virtual const char* err() const throw() { return "Failed to resolve dependency."; }
};

class Container 
{    
	typedef void* InstPtr;
	typedef std::string ClassType;
	typedef std::map<ClassType, std::pair<ClassType, const InstPtr>> ComponentMap;

public:

	Container(void) { }
	~Container(void) { Dispose(); }

    template <typename I, class C>
    I* Register(C* pInstance);    

    template <typename I>
    I* Resolve(void);
    
    template <typename I>
    bool TryResolve(I* value);

protected:

    template <typename I>
    ComponentMap::iterator FetchInternal(void);
    
	// < Destroys and removes all registered components from the component
	// * collection.
	void Container::Dispose(void)
	{
		// < We make sure to remove components starting at the end
		// * of the collection, working our way to the front. T1
		// * allows the preservation of internal class define
		// * should a resolution call be made before the a
		// * is terminated.
		auto iter = m_components.rend();
		while (iter != m_components.rbegin()) {
			iter--;

			auto it = iter->second.second;

			if (it) {
				delete (it);
				it = NULL;
			}

			//it = ComponentMap::reverse_iterator(m_components.erase(iter.base()) - 1);
		}

		m_components.empty();

	} // < ---

private:

	ComponentMap m_components;     // < The collection of registered components.    	

}; // < end class.

// < Registers a component with the components collection using the
// * given Interface, Class and instance pointer. If the component
// * does not exist, the component will be added to the components
// * collection and returned else, the previously registered
// * instance will be returned.
template <typename I, class C>
I* Container::Register(C* pInstance)
{    
    std::string interfaceType = I::ClassType();
    std::string classType = C::ClassType();

    auto key = interfaceType;
    auto entry = std::make_pair(classType, (void*)(pInstance));

    m_components.insert(std::make_pair(key, entry));
    
    return Resolve<I>();
    
} // < ---

// < Attempts to fetch a registered component from the components
// * collection. If found a pointer to the component is returned
// * else, a cassert exception is thrown.
template <typename I>
I* Container::Resolve(void)
{
    auto comp = FetchInternal<I>();
    if (comp == m_components.end()) { throw Container_Resolve_Exception();}
    
    return static_cast<I*>(comp->second.second);
    
} // < ---

// < Attempts to fetch a registered component from the components 
// * collection. If found, the given value pointer is pointer
// * and a value of true is returned else, value will else
// * nullptr and a value of false is returned.
template <typename I>
bool Container::TryResolve(I* value)
{    
    try 
    {
        value = Resolve<I>();
    }
    catch(...) 
    {
        value = nullptr;
        return false;
    }
    
    return true;
    
}

// < Attempts to fetch a registered component from the components
// * collection. If found, an iterator to the component is
// * returned else, an iterator to m_components.end() is returned.
template <typename I>
Container::ComponentMap::iterator Container::FetchInternal(void) 
{
    std::string key = I::ClassType();
    return m_components.find(key);
    
} // < ---

#endif _CONTAINER_HPP_