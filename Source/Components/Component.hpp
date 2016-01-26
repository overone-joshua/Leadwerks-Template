#ifndef _COMPONENT_HPP_
	#define _COMPONENT_HPP_
	
#pragma once
#include "IComponent.hpp"
#include "../Common.hpp"

class Component : public HasId<uint64_t>, public virtual IComponent {
public:	

	virtual const char* ObjectType(void) = 0;

	Component(void);
	virtual ~Component(void);

}; // < end class.

#endif _COMPONENT_HPP_