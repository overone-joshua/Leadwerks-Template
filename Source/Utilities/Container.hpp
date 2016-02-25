#ifndef _CONTAINER_HPP_
    #define _CONTAINER_HPP_
    
#pragma once
#include "../Common.hpp"
#include "Macros.hpp"

#include <cassert>
#include <map>
#include <string>

class Container 
{
	template <typename T1, typename T2>
	struct ComponentKeyComparer {
		bool operator () (const std::pair<T1, T2>& x, const std::pair<T1, T2>& y) {
			return x.first < y.first && x.second < y.second;
		}
	};

	typedef void* InstPtr;
	typedef std::string ClassType;
	typedef std::map<ClassType, std::pair<ClassType, InstPtr>> ComponentMap;

public:

	Container(void) { }
	
	~Container(void) {

		Dispose();

	}

	template <typename I, class C>
	I* Register(C* pInstance) {
	
		auto comp = this->FetchInternal<I>();
		assert(comp == m_components.end());

		std::string interfaceType = I::ClassType();
		std::string classType = C::ClassType();

		auto key = interfaceType;
		auto entry = std::make_pair(classType, (void*)(pInstance));

		auto newComp = m_components.insert(std::make_pair(key, entry));
		
		return Resolve<I>();
	}

	template <typename I>
	I* Resolve() {

		auto comp = FetchInternal<I>();
		assert(comp != m_components.end());

		return (I*)(comp->second.second);

	}

protected:

	template <typename I>
	ComponentMap::iterator FetchInternal(void) {

		std::string key = I::ClassType();
		return m_components.find(key);

	}

private:

	ComponentMap m_components;

	void Dispose(void) {

		auto iter = m_components.rend();
		while (iter != m_components.rbegin()) {
			iter--;
			SAFE_DELETE(iter->second.second);
		}

		m_components.empty();

	}

}; // < end class.

#endif _CONTAINER_HPP_