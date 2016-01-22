#ifndef _ICOMPONENT_HPP_
	#define _ICOMPONENT_HPP_
	
#pragma once
#include "../Utilities/HasId.hpp"

class IComponent : public virtual HasId<long> {
public:
	
	virtual void Update(float dt) = 0;
	virtual void Render(void) = 0;
	virtual void Draw(void) = 0;

}; // < end class.
	
#endif _ICOMPONENT_HPP_