#ifndef _HASID_HPP_
	#define _HASID_HPP_
	
#pragma once
#include "IHasId.hpp"

template <typename T>
class HasId : public virtual IHasId<T> {
public:
	
	HasId(void);
	~HasId(void);
	
	T Id(void);

protected:
	HasId(T _id);

	void setId(T _id);

private:

	T m_id;

}; // end class.
	
template <typename T>
void HasId<T>::setId(T _id) { m_id = _id; }

template <typename T>
T HasId<T>::Id(void) { return m_id; }
	
template <typename T>
HasId<T>::HasId(void) { m_id = 0; }

template <typename T>
HasId<T>::HasId(T _id) : m_id(_id) { }
	
template <typename T>
HasId<T>::~HasId(void) { m_id = -1; }
	
#endif _HASID_HPP_