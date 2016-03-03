/*-------------------------------------------------------
                    <copyright>
    
    File: EntityHandle.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for EntityHandle utility.
                 The EntityHandle is a wrapper around
                 the Leadwerks::Entity object.
    
    Functions: 1. Leadwerks::Entity* getInst(void);                                                     

---------------------------------------------------------*/

#ifndef _ENTITY_HANDLE_HPP_
	#define _ENTITY_HANDLE_HPP_

#pragma once
#include "Leadwerks.h"
#include "Macros.hpp"

class EntityHandle
{
	CLASS_TYPE(EntityHandle);

public:

	EntityHandle(Leadwerks::Entity* pEntity)
		: m_pEntity(pEntity) {

	}

	~EntityHandle(void) {

		SAFE_RELEASE(m_pEntity);
		SAFE_DELETE(m_pEntity);

	}

	Leadwerks::Entity* getInst(void) { return m_pEntity; }

private:

	Leadwerks::Entity* m_pEntity;

}; // < end class.

#endif _ENTITY_HANDLE_HPP_