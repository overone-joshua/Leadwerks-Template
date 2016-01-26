#ifndef _ACTOR_HPP_
	#define _ACTOR_HPP_
	
#pragma once
#include "IActor.hpp"
#include "../Common.hpp"
	
class ActorManager;

class Actor : public HasId<uint64_t>, public virtual IActor {
public:

	Actor(void);
	~Actor(void);

protected:

	friend class ActorManager;

}; // end class.

#endif _ACTOR_HPP_