#ifndef _DELEGATE_H_
	#define _DELEGATE_H_

#pragma once
#include <cassert>
#include <utility>

template <typename R, typename T>
class Delegate {
	typedef void* InstancePtr;
	typedef void(*InternalFunction)(InstancePtr, T);
	typedef std::pair<InstancePtr, InternalFunction> Stub;

	/* Turns a free function into our internal function stub */
	template <R(*Function)(T)>
	static inline void FunctionStub(InstancePtr, T ARG0) {
		/* We do not need the instance pointer because we are dealing with free functions */
		return (Function)(ARG0);
	}

	/* Turns a member function into our internal function stub */
	template <class C, R(C::*Function)(T)>
	static inline void ClassMethodStub(InstancePtr instance, T ARG0) {
		/* Cast the instance pointer back into the original class instance */
		return (static_cast<C*>(instance)->*Function)(ARG0);
	}

public:
	Delegate(void) : m_stub(nullptr, nullptr) {}

	/* Binds a free function */
	template <R(*Function)(T)>
	void Bind(void) {
		m_stub.first = nullptr;
		m_stub.second = &FunctionStub < Function > ;
	}

	/* Binds a class method */
	template <class C, R(C::*Function)(T)>
	void Bind(C* instance) {
		m_stub.first = instance;
		m_stub.second = &ClassMethodStub < C, Function > ;
	}

	/* Invoke the delegate */
	R Invoke(T ARG0) const {
		assert(m_stub.second != nullptr); // Cannot invoke unbound delegate. Call Bind() first.
		return m_stub.second(m_stub.first, ARG0);
	}

protected:

private:
	Stub m_stub;

}; // end class Delegate.

#endif // _DELEGATE_H_