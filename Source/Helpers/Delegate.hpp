#ifndef _DELEGATE_H_
	#define _DELEGATE_H_

#pragma once
#include <cassert>
#include <utility>

template <typename T>
class Delegate {
	typedef void* InstancePtr;
	typedef void(*InternalFunction)(InstancePtr, T);
	typedef std::pair<InstancePtr, InternalFunction> Stub;

	/* Turns a free function into our internal function stub */
	template <void(*Function)(T)>
	static inline void FunctionStub(InstancePtr, T ARG0) {
		return (Function)(ARG0);
	}

	/* Turns a member function into our internal function stub */
	template <class C, void(C::*Function)(T)>
	static inline void ClassMethodStub(InstancePtr instance, T ARG0) {
		return (static_cast<C*>(instance)->*Function)(ARG0);
	}

public:
	Delegate(void) : m_stub(nullptr, nullptr) { };

	/* Binds a free-function */
	template <void(*Function)(T)>
	void Bind(void) {
		this->m_stub.first = nullptr;
		this->m_stub.second = &FunctionStub < Function > ;
	}

	/* Binds a class-method */
	template <class C, void(C::*Function)(T)>
	void Bind(C* instance) {
		this->m_stub.first = instance;
		this->m_stub.second = &ClassMethodStub < C, Function > ;
	}

	/* Invokes the delegate */
	void Invoke(T ARG0) const {
		assert(m_stub.second != nullptr);	 // Cannot invoke unbound delegate. Call Bind() first.
		return this->m_stub.second(m_stub.first, ARG0);
	}

	const bool operator == (Delegate<T> other) const {
		if (this->m_stub.first != other.m_stub.first ||
			this->m_stub.second != other.m_stub.second) {
			return false;
		}

		return true;
	}

private:
	Stub m_stub;

}; // end class Delegate.

#endif // _DELEGATE_H_