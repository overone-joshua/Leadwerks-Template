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

        Leadwerks::PickInfo stepResult;

		explicit Component_Placement(uint64_t _nEntityId = 0, const std::string& name = "")
			: Component(_nEntityId, name)
		{
			vTranslation = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);
			vRotation = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);

			vVelocity = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);
			vSpin = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);

			vForward = Leadwerks::Vec3(0.0f, 0.0f, 1.0f);
			vRight = Leadwerks::Vec3(1.0f, 0.0f, 0.0f);

			nFriction = 8.0f;

			bVisible = true;
			bGhost = false;
			bIgnoreCollision = false;

			bTouchingGround = false;
		}

        Component_Placement(const Component_Placement& _other)
            : Component(_other.nEntityId, _other.cName)
        {
            nId = _other.nId;

            vTranslation = _other.vTranslation;
            vRotation = _other.vRotation;

            vVelocity = _other.vVelocity;
            vSpin = _other.vSpin;

            vForward = _other.vForward;
            vRight = _other.vRight;

            nFriction = _other.nFriction;

            bVisible = _other.bVisible;
            bGhost = _other.bGhost;
            bIgnoreCollision = _other.bIgnoreCollision;

            bTouchingGround = _other.bTouchingGround;
        }

	} Placement; // < end struct
} // < end namespace.

#endif _PLACEMENT_COMPONENT_HPP