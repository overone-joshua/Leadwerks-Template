#ifndef _ACTOR_MANAGER_HPP_
	#define _ACTOR_MANAGER_HPP_
	
#pragma once
#include "../Common.hpp"
#include "../Utilities/Macros.hpp"

class Actor;

class ActorManager {
public:

	ActorManager(void);
	~ActorManager(void);	

	Actor* Fetch(uint64_t _id);

	Actor* Create(void);

	void Delete(uint64_t _id);

protected:
	uint64_t GenerateId(void);

private:	

	uint64_t m_nRunningIndex;

}; // < end class.

#endif _ACTOR_MANAGER_HPP_