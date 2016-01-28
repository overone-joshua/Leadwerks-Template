#ifndef _COMPONENT_HPP_
	#define _COMPONENT_HPP_
	
#pragma once
#include "IComponent.hpp"
#include "../Utilities/HasId.hpp"
#include "../Utilities/Factory.hpp"

class ActorManager;

class Component : public HasId<uint64_t>, public virtual IComponent {
public:	

	virtual const char* ObjectType(void) = 0;

	Component(void);
	virtual ~Component(void);

protected:

	friend class ActorManager;

}; // < end class.

extern Factory<Component> gComponentFactory;

#endif _COMPONENT_HPP_