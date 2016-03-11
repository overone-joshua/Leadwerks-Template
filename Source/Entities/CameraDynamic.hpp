/*-------------------------------------------------------
                    <copyright>
    
    File: CameraDynamic.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for CameraDynamic System.

    Functions: 1. static inline uint64_t Create(Components::World* pWorld, Leadwerks::Vec3 vPos, Leadwerks::Vec3 vRot, CameraHandle* pCameraHndl);
    
               2. static void Update(Components::World* pWorld, float dt); 

---------------------------------------------------------*/

#ifndef _CAMERA_ENTITY_HPP_
    #define _CAMERA_ENTITY_HPP_
    
#pragma once
#include "Leadwerks.h"
#include "../Services/ScriptController.hpp"

#include "../Utilities/CameraHandle.hpp"

#include "../Components/ComponentDictionary.hpp"
#include "../Components/Input.hpp"
#include "../Components//InputDictionary.hpp"

#include "../Components/Camera.hpp"
#include "../Components/Placement.hpp"
#include "../Components/Velocity.hpp"
#include "../Components/World.hpp"

#include <sqrat.h>

namespace Entities
{
	const unsigned MASK_CAMERA_DYNAMIC = COMPONENT_INPUT | COMPONENT_PLACEMENT | COMPONENT_VELOCITY | COMPONENT_CAMERA;

	class CameraDynamic
	{
	public:
		static inline uint64_t Create(Components::World* pWorld, Leadwerks::Vec3 vPos, Leadwerks::Vec3 vRot, CameraHandle* pCameraHndl)
		{
			uint64_t entity = pWorld->CreateEntity(pWorld);

			pWorld->Get(entity) = MASK_CAMERA_DYNAMIC;

			pWorld->AddComponent<Components::Placement>(pWorld, entity, Components::Placement(vPos, vRot));
			pWorld->AddComponent<Components::Input>(pWorld, entity, Components::Input());
			pWorld->AddComponent<Components::Velocity>(pWorld, entity, Components::Velocity());
			pWorld->AddComponent<Components::Camera>(pWorld, entity, Components::Camera(pCameraHndl));

			auto cam = pCameraHndl->getInst();
			cam->SetRotation(vRot, false);
			cam->SetPosition(vPos, true);

			return entity;
		}

		static void Update(InputManager* pInputMgr, Components::World* pWorld, float dt) 
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
                float dX, dY;

				// < Are we rotating the camera left or right?
                if ( (bool(inputMask & INPUT_ROTATE_LEFT | INPUT_ROTATE_RIGHT)) ) {
                    dY = (((bool(inputMask & INPUT_ROTATE_RIGHT)) - (bool(inputMask & INPUT_ROTATE_LEFT))) + pInputMgr->DeltaX())  * dt * 0.75f;
                }

				// < Are we tilting the camera up or down?
                if ( (bool(inputMask & INPUT_ROTATE_UP |INPUT_ROTATE_DOWN)) ) {
                    dX = (((bool(inputMask & INPUT_ROTATE_UP)) - (bool(inputMask & INPUT_ROTATE_DOWN))) + pInputMgr->DeltaY())  * dt * 0.75f;
                }

				// < Are we looking to move the camera?
				float vX = ( (bool(inputMask & INPUT_MOVE_RIGHT))	- (bool(inputMask & INPUT_MOVE_LEFT)) )		* dt * 0.075f;
				float vY = ( (bool(inputMask & INPUT_MOVE_UP))		- (bool(inputMask & INPUT_MOVE_DOWN)) )		* dt * 0.075f;
				float vZ = ( (bool(inputMask & INPUT_MOVE_FORWARD))	- (bool(inputMask & INPUT_MOVE_BACKWARD)) ) * dt * 0.075f;

				velocityComponent.vVel.x = vX;
				velocityComponent.vVel.y = vY;
				velocityComponent.vVel.z = vZ;			
								
                placementComponent.vRot += Leadwerks::Vec3(dX, dY, 0.0f);

				// < Set the camera's rotation and position.
				auto cam = cameraComponent.pCamHndl->getInst();

				cam->SetRotation(placementComponent.vRot, false);
				cam->Move(velocityComponent.vVel, true);

				// < ---

				iter++;

			}

		}

        static void Bind(void)
        {
            using namespace Sqrat;

            auto entityTable = ScriptController::GetTable("Entities");

            entityTable->Bind("CameraDynamic", Class<CameraDynamic>()
                .StaticFunc("Create", &CameraDynamic::Create)
                .StaticFunc("Update", &CameraDynamic::Update)
            );
        }

	}; // < end class.

} // < end namespace.
    
#endif _CAMERA_ENTITY_HPP_
