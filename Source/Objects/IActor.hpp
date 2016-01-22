#ifndef _ACTOR_HPP_
	#define _ACTOR_HPP_
	
 #pragma once
 
class IActor : public virtual HasId<long> {
public:	 

	virtual void Update(float deltaTime) = 0;
	virtual void Render(void) = 0;
	virtual void Draw(void) = 0;

}; // < end class. 
	
#endif _ACTOR_HPP_