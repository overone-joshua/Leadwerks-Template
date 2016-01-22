#ifndef _IACTOR_HPP_
	#define _IACTOR_HPP_
	
 #pragma once
#include "../Utilities/HasId.hpp"

class IActor : public virtual HasId<long> {
public:	 

	virtual void Update(float deltaTime) = 0;
	virtual void Render(void) = 0;
	virtual void Draw(void) = 0;

}; // < end class. 
	
#endif _IACTOR_HPP_