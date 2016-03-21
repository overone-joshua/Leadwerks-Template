/*-------------------------------------------------------
                    <copyright>
    
    File: ContrextHandle.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for ContextHandle utility.
                 The ContextHandle is a wrapper around
                 the Leadwerks::Context object.
    
    Functions: 1. Leadwerks::Context* getInst(void);                                                     

---------------------------------------------------------*/

#ifndef _CONTEXT_HANDLE_HPP_
	#define _CONTEXT_HANDLE_HPP_

#pragma once
#include "Leadwerks.h"
#include "Macros.hpp"

class ContextHandle
{
	CLASS_TYPE(Context);

public:

	explicit ContextHandle(Leadwerks::Context* pContext) 
		:m_pContext(pContext){

	}

	~ContextHandle(void) {

		SAFE_RELEASE(m_pContext);
		SAFE_DELETE(m_pContext);

	}

	Leadwerks::Context* getInst(void) { return m_pContext; }

private:

	Leadwerks::Context* m_pContext;

}; // < end class.

#endif _CONTEXT_HANDLE_HPP_