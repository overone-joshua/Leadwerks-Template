/*-------------------------------------------------------
                    <copyright>

    File: WorldHandle.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for WorldHandle utility.
                 The WorldHandle is a wrapper around
                 the Leadwerks::World object.

    Functions: 1. Leadwerks::World* getInst(void);

---------------------------------------------------------*/

#ifndef _WORLD_HANDLE_HPP_
	#define _WORLD_HANDLE_HPP_

#pragma once
#include "Leadwerks.h"
#include "Disposable.hpp"
#include "Macros.hpp"

class WorldHandle : public Disposable
{
	CLASS_TYPE(World);

public:

	explicit WorldHandle(Leadwerks::World* pWorld)
		:m_pWorld(pWorld){

	}

	~WorldHandle(void)
    {
        Dispose();
	}

    void Dispose(void)
    {
        SAFE_RELEASE(m_pWorld);
        SAFE_DELETE(m_pWorld);
    }

	Leadwerks::World* getInst(void) { return m_pWorld; }

private:

	Leadwerks::World* m_pWorld;

}; // < end class.

#endif _WORLD_HANDLE_HPP_