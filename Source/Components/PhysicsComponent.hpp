#ifndef _PHYSICS_COMPONENT_HPP_
	#define _PHYSICS_COMPONENT_HPP_

#pragma once
#include "Leadwerks.h"
#include "Component.hpp"

#include "../Utilities/Macros.hpp"

class PhysicsComponent : public Component {

	CLASS_TYPE(PhysicsComponent);

public:

	PhysicsComponent(void);
	~PhysicsComponent(void);

	Leadwerks::Vec3 getPosition(void);
	Leadwerks::Vec3 getRotation(void);
	Leadwerks::Vec3 getScale(void);

	void setPosition(Leadwerks::Vec3 vPosition);
	void setRotation(Leadwerks::Vec3 vRotation);
	void setScale(Leadwerks::Vec3 vScale);
	

private:

	Leadwerks::Vec3 m_vPosition;
	Leadwerks::Vec3 m_vRotation;
	Leadwerks::Vec3 m_vScale;

}; // end class.


#endif _PHYSICS_COMPONENT_HPP_