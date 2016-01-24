#ifndef _ACTOR_MANAGER_HPP_
	#define _ACTOR_MANAGER_HPP_
	
#pragma once
#include "Manager.hpp"
#include "../Objects/Actor.hpp"

#include <map>

class ActorMgr {
public:

	ActorMgr(void);
	~ActorMgr(void);	

	Actor* Fetch(long _id);

	Actor* Create(void);

	void Delete(long _id);
	
protected:
	long GenerateId(void);

private:	

	long m_nRunningIndex;

	Manager<Actor>* m_pActorManager;

}; // < end class.

#endif _ACTOR_MANAGER_HPP_