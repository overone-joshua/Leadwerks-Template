#ifndef _VELOCITY_HPP_
	#define _VELOCITY_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

namespace Components
{
	typedef struct Velocity : public Component
	{
		using Component::Component;

		CLASS_TYPE(Velocity);

		Leadwerks::Vec3 vVel;

		Velocity(void) 
			: vVel(0.0f, 0.0f) { }

	} Velocity; // < end struct.

} // < end namespace.

#endif _VELOCITY_HPP_