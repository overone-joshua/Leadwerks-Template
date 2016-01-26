#ifndef _ICOMPONENT_HPP_
	#define _ICOMPONENT_HPP_
	
#pragma once
#include "../Utilities/IHasId.hpp"

class IComponent : public virtual IHasId<long> {
public:	

	virtual const char* ObjectType(void) = 0;

}; // < end class.

#endif _ICOMPONENT_HPP_