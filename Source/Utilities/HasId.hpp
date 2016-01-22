#ifndef _HASID_HPP_
	#define _HASID_HPP_
	
#pragma once
#include "IHasId.hpp"

template <typename T>
class HasId : public virtual IHasId<T> {
public:

	HasId(T _id);
	virtual ~HasId(void);
	
	T Id(void);

private:

	T m_id;

}; // end class.
	
template <typename T>
T HasId<T>::Id(void) { return m_id; }
	
template <typename T>
HasId<T>::HasId(T _id) : m_id(_id) { }
	
template <typename T>
HasId<T>::~HasId(void) { }
	
#endif _HASID_HPP_