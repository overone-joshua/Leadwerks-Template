#ifndef _ACTOR_HPP_
	#define _ACTOR_HPP_
	
#pragma once
#include "IActor.hpp"
	
class Actor : public IActor {
public:

	virtual void Update(float deltaTime) = 0;
	virtual void Render(void) { };
	virtual void Draw(void) { };

}; // end class.
	
#endif _ACTOR_HPP_