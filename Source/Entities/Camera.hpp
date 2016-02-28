#ifndef _CAMERA_ENTITY_HPP_
    #define _CAMERA_ENTITY_HPP_
    
#pragma once
#include "Leadwerks.h"

#include "../Utilities/CameraHandle.hpp"

#include "../Components/ComponentDictionary.hpp"

#include "../Components/Camera.hpp"
#include "../Components/Placement.hpp"
#include "../Components/Velocity.hpp"
#include "../Components/World.hpp"

namespace Entities
{
	class Camera
	{
		static inline unsigned Create(Components::World* pWorld, Leadwerks::Vec3 vPos, Leadwerks::Vec3 vRot, CameraHandle* pCameraHndl)
		{
			unsigned entity = pWorld->CreateEntity(pWorld);

			pWorld->Get(entity) = COMPONENT_POSITION | COMPONENT_VELOCITY | COMPONENT_CAMERA;

			pWorld->AddComponent<Components::Placement>(pWorld, entity, Components::Placement(vPos, vRot));
			pWorld->AddComponent<Components::Velocity>(pWorld, entity, Components::Velocity());
			pWorld->AddComponent<Components::Camera>(pWorld, entity, Components::Camera(pCameraHndl));

			return entity;
		}

		static void Update(float dt) 
		{

		}

	}; // < end class.

} // < end namespace.
    
#endif _CAMERA_ENTITY_HPP_
