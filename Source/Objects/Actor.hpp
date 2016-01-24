#ifndef _ACTOR_HPP_
	#define _ACTOR_HPP_
	
#pragma once
#include "IActor.hpp"
#include "../Utilities/HasId.hpp"
	
class Actor : public HasId<long>, public virtual IActor {
public:

	Actor(long _id);
	~Actor(void);

}; // end class.

#endif _ACTOR_HPP_