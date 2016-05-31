#ifndef _PLACEMENT_COMPONENT_HPP_
#define _PLACEMENT_COMPONENT_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"

#include <string>

namespace Components
{
	typedef struct Component_Placement : public Component
	{
		CLASS_TYPE(Placement);

		Leadwerks::Vec3 vForward;
		Leadwerks::Vec3 vRight;

		Leadwerks::Mat4 mWorld;
		Leadwerks::Mat4 mView;

		Leadwerks::Vec3 vTranslation;
		Leadwerks::Vec3 vRotation;

		Leadwerks::Vec3 vVelocity;
		Leadwerks::Vec3 vSpin;

		Leadwerks::Mat4 mTranslation;
		Leadwerks::Mat4 mRotation;

		float nFriction;
		bool bVisible;
		bool bGhost;
		bool bIgnoreCollision;
		bool bTouchingGround;

		explicit Component_Placement(const std::string& name = "")
			: Component(name)
		{
			vTranslation = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);
			vRotation = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);

			vVelocity = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);
			vSpin = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);

			vForward = Leadwerks::Vec3(0.0f, 0.0f, 1.0f);
			vRight = Leadwerks::Vec3(1.0f, 0.0f, 0.0f);

			nFriction = 0.0f;

			bVisible = true;
			bGhost = false;
			bIgnoreCollision = false;

			bTouchingGround = false;

		}

	} Placement; // < end struct
} // < end namespace.

#endif _PLACEMENT_COMPONENT_HPP