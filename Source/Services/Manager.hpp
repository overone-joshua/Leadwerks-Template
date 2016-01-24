#ifndef _MANAGER_HPP_
	#define _MANAGER_HPP_

#pragma once
#include "../Utilities/Macros.hpp"
#include "../Utilities/HasId.hpp"
#include <map>

template <typename T>
class Manager {
public:

	Manager(void);
	~Manager(void);

	T* Fetch(long _id);	

	T* Create(long _id);

	void Delete(long _id);

protected:	

	typename std::map<long, T*>::iterator FetchIterator(long _id);

	std::map<long, T*> m_components;

}; // < end class.

template <typename T>
Manager<T>::Manager(void) { }

template <typename T>
Manager<T>::~Manager(void) {

	auto iter = m_components.begin();
	while (iter != m_components.end()) {
		auto it = iter->second;
		
		if (it != nullptr) { SAFE_DELETE(it); }

		iter++;
	}
	m_components.empty();

}

template <typename T>
T* Manager<T>::Fetch(long _id) {

	auto it = m_components.find(_id);
	if (it == m_components.end()) { return nullptr; }

	return it->second;
}

template <typename T>
typename std::map<long, T*>::iterator Manager<T>::FetchIterator(long _id) {

	auto it = m_components.find(_id);
	
	return it;
}

template <typename T>
T* Manager<T>::Create(long _id) {

	auto it = Fetch(_id);
	
	if (it == nullptr) { m_components[_id] = new T(_id); }

	return m_components[_id];
}

template <typename T>
void Manager<T>::Delete(long _id) {

	auto it = FetchIterator(_id);
	if (it != m_components.end() && it->second != nullptr) {
		SAFE_DELETE(it->second);
		it->second = nullptr;
		m_components.erase(_id);
	}	
}

#endif _MANAGER_HPP_