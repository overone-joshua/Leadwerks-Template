#ifndef _CAMERA_ENTITY_HPP_
    #define _CAMERA_ENTITY_HPP_
    
#pragma once
#include "Leadwerks.h"

#include "../Utilities/CameraHandle.hpp"

#include "../Components/ComponentDictionary.hpp"
#include "../Components/Input.hpp"
#include "../Components//InputDictionary.hpp"

#include "../Components/Camera.hpp"
#include "../Components/Placement.hpp"
#include "../Components/Velocity.hpp"
#include "../Components/World.hpp"

namespace Entities
{
	const unsigned MASK_CAMERA_DYNAMIC = COMPONENT_INPUT | COMPONENT_POSITION | COMPONENT_VELOCITY | COMPONENT_CAMERA;

	class CameraDynamic
	{
	public:
		static inline unsigned Create(Components::World* pWorld, Leadwerks::Vec3 vPos, Leadwerks::Vec3 vRot, CameraHandle* pCameraHndl)
		{
			uint64_t entity = pWorld->CreateEntity(pWorld);

			pWorld->Get(entity) = MASK_CAMERA_DYNAMIC;

			pWorld->AddComponent<Components::Placement>(pWorld, entity, Components::Placement(vPos, vRot));
			pWorld->AddComponent<Components::Input>(pWorld, entity, Components::Input());
			pWorld->AddComponent<Components::Velocity>(pWorld, entity, Components::Velocity());
			pWorld->AddComponent<Components::Camera>(pWorld, entity, Components::Camera(pCameraHndl));

			return entity;
		}

		static void Update(Components::World* pWorld, float dt) 
		{
			// < Get a collection of entities that are of type cameraDynamic.
			auto entities = pWorld->GetEntities(pWorld, MASK_CAMERA_DYNAMIC);
			
			auto iter = entities.begin();
			while (iter != entities.end())
			{
				unsigned entity = (*iter);

				Components::Input& inputComponent = pWorld->GetComponents<Components::Input>(pWorld, entity)
						->front();
				Components::Placement& placementComponent = pWorld->GetComponents<Components::Placement>(pWorld, entity)
						->front();
				Components::Velocity& velocityComponent = pWorld->GetComponents<Components::Velocity>(pWorld, entity)
						->front();
				Components::Camera& cameraComponent = pWorld->GetComponents<Components::Camera>(pWorld, entity)
						->front();

				// < Perform any game logic here.
				// < ---
				uint64_t inputMask = inputComponent.nMask;

				float vX = ( (bool(inputMask & INPUT_MOVE_RIGHT))	- (bool(inputMask & INPUT_MOVE_LEFT)) )		* dt * 0.075f;
				float vY = ( (bool(inputMask & INPUT_MOVE_UP))		- (bool(inputMask & INPUT_MOVE_DOWN)) )		* dt * 0.075f;
				float vZ = ( (bool(inputMask & INPUT_MOVE_FORWARD))	- (bool(inputMask & INPUT_MOVE_BACKWARD)) ) * dt * 0.075f;

				velocityComponent.vVel.x = vX;
				velocityComponent.vVel.y = vY;
				velocityComponent.vVel.z = vZ;


				// < Add the velocity to the camera's placement.
				placementComponent.vPos += velocityComponent.vVel;

				// < Set lerp the camera's position.
				auto cam = cameraComponent.pCamHndl->getInst();
				cam->SetPosition(placementComponent.vPos, true);
				cam->SetRotation(placementComponent.vRot, false);

				// < ---

				iter++;

			}


		}

	}; // < end class.

} // < end namespace.
    
#endif _CAMERA_ENTITY_HPP_
