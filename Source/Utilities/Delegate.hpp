/*-------------------------------------------------------
                    <copyright>
    
    File: Delegate.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Delegate utility.
                 The Delegate class provieds an easy an
                 lighteright implementation for the
                 registration of functions and member 
                 function for callback.
    
    Functions: 1. template <void(*function)(*)>
                  void Bind(void);
                  
               2. template <class C, void(C::*Function)(T)>
                  void Bind(void);
                  
               3. void Invoke(T ARG0);

---------------------------------------------------------*/

#ifndef _DELEGATE_HPP_
	#define _DELEGATE_HPP_

#pragma once
#include <cassert>
#include <utility>

template <typename T>
class Delegate
{
	typedef void* InstancePtr;
	typedef void(*InternalFunction)(InstancePtr, T);
	typedef std::pair<InstancePtr, InternalFunction> Stub;

	/* Turns a free function into our internal function stub */
	template <void(*Function)(T)>
	static inline void FunctionStub(InstancePtr, T ARG0)
    {
		return (Function)(ARG0);
	}

	/* Turns a member function into our internal function stub */
	template <class C, void(C::*Function)(T)>
	static inline void ClassMethodStub(InstancePtr instance, T ARG0)
    {
		return (static_cast<C*>(instance)->*Function)(ARG0);
	}

public:
	Delegate(void) : m_stub(nullptr, nullptr) { };

	/* Binds a free-function */
	template <void(*Function)(T)>
	void Bind(void)
    {
		this->m_stub.first = nullptr;
		this->m_stub.second = &FunctionStub < Function > ;
	}

	/* Binds a class-method */
	template <class C, void(C::*Function)(T)>
	void Bind(C* instance)
    {
		this->m_stub.first = instance;
		this->m_stub.second = &ClassMethodStub < C, Function > ;
	}

	/* Invokes the delegate */
	void Invoke(T ARG0) const
    {
		assert(m_stub.second != nullptr);	 // Cannot invoke unbound delegate. Call Bind() first.
		return this->m_stub.second(m_stub.first, ARG0);
	}

	bool operator== (const Delegate<T>& other)
    {
		if (this->m_stub.first != other.m_stub.first ||
			this->m_stub.second != other.m_stub.second)
            {
			return false;
		}

		return true;
	}

private:
	Stub m_stub;

}; // end class.

#endif // _DELEGATE_HPP_