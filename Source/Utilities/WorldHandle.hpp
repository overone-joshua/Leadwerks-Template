#ifndef _WORLD_HANDLE_HPP_
	#define _WORLD_HANDLE_HPP_

#pragma once
#include "Leadwerks.h"
#include "Macros.hpp"

class WorldHandle {

	CLASS_TYPE(World);

public:

	WorldHandle(Leadwerks::World* pWorld) 
		:m_pWorld(pWorld){

	}

	~WorldHandle(void) {

		SAFE_RELEASE(m_pWorld);
		SAFE_DELETE(m_pWorld);

	}

	Leadwerks::World* getInst(void) { return m_pWorld; }

private:

	Leadwerks::World* m_pWorld;

}; // < end class.

#endif _WORLD_HANDLE_HPP_