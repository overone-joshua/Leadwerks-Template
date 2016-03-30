#ifndef _SPECTATOR_CAMERA_ENTITY_HPP_
	#define _SPECTATOR_CAMERA_ENTITY_HPP_

#pragma once
#include "Leadwerks.h"
#include "../../Common.hpp"
#include "../../Utilities/Event.hpp"

#include "../Entity.hpp"
#include "../Camera.hpp"
#include "../Input.hpp"

#include "../../Components/World.hpp"
#include "../../Components/Trigger.hpp"
#include "../../Components//Custom/MouseMoveTrigger.hpp"
#include "../../Components//Custom/KeyDownTrigger.hpp"
#include "../../Components//Custom/KeyUpTrigger.hpp"

namespace Entities
{
	class SpectatorCamera : public Entities::Entity<SpectatorCamera>
	{
        CLASS_TYPE(SpectatorCamera);

    public:

        SpectatorCamera(void) { }

	    static uint64_t Create(Components::World& world, std::string _cScriptPath)
	    {
            auto entity = Entities::Camera::Create(world, _cScriptPath);

            // < Wire up our game logic events for each entity.
			Entities::Camera::BindMouseMove<&SpectatorCamera::MouseMove>(world, entity, "Camera");
			Entities::Camera::BindKeyDown<&SpectatorCamera::KeyDown>(world, entity, "Camera");
			Entities::Camera::BindKeyUp<&SpectatorCamera::KeyUp>(world, entity, "Camera");

            return entity;
	    }

        static void MouseMove(Components::World& world, Entities::Camera entity, Event_MouseMove* pEvent)
        {
            // < Check for any mouse movement. If there is any movement, we should
            // * look to rotate the camera.
            auto iter = entity.inputComponents->begin();
            while (iter != entity.inputComponents->end())
            {
                (*iter).vDelta = pEvent->Delta();

                if (pEvent->Delta().x < 0) { (*iter).nMask |= INPUT_ROTATE_LEFT; }
                if (pEvent->Delta().x > 0) { (*iter).nMask |= INPUT_ROTATE_RIGHT; }

                if (pEvent->Delta().y < 0) { (*iter).nMask |= INPUT_ROTATE_DOWN; }
                if (pEvent->Delta().y > 0) { (*iter).nMask |= INPUT_ROTATE_UP; }

                ++iter;
            }
        }

        static void KeyDown(Components::World& world, Entities::Camera entity, Event_KeyDown* pEvent)
        {
            // < Check for any key presses from the keyboard. If any key is pressed
            // * we should look to move the camera.
            auto iter = entity.inputComponents->begin();
            while (iter != entity.inputComponents->end())
            {
                if (pEvent->Key() == Leadwerks::Key::W) { (*iter).nMask |= INPUT_MOVE_FORWARD; }
                if (pEvent->Key() == Leadwerks::Key::A) { (*iter).nMask |= INPUT_MOVE_LEFT; }
                if (pEvent->Key() == Leadwerks::Key::S) { (*iter).nMask |= INPUT_MOVE_BACKWARD; }
                if (pEvent->Key() == Leadwerks::Key::D) { (*iter).nMask |= INPUT_MOVE_RIGHT; }

                if (pEvent->Key() == Leadwerks::Key::E) { (*iter).nMask |= INPUT_MOVE_UP; }
                if (pEvent->Key() == Leadwerks::Key::Q) { (*iter).nMask |= INPUT_MOVE_DOWN; }

                ++iter;
            }
        }

        static void KeyUp(Components::World& world, Entities::Camera entity, Event_KeyUp* pEvent)
        {
            // < Just like key press however, here we pop the movement bitmask to signal
            // * a key release.
            auto iter = entity.inputComponents->begin();
            while (iter != entity.inputComponents->end())
            {
                if (pEvent->Key() == Leadwerks::Key::W) { (*iter).nMask &= ~INPUT_MOVE_FORWARD; }
                if (pEvent->Key() == Leadwerks::Key::A) { (*iter).nMask &= ~INPUT_MOVE_LEFT; }
                if (pEvent->Key() == Leadwerks::Key::S) { (*iter).nMask &= ~INPUT_MOVE_BACKWARD; }
                if (pEvent->Key() == Leadwerks::Key::D) { (*iter).nMask &= ~INPUT_MOVE_RIGHT; }

                if (pEvent->Key() == Leadwerks::Key::E) { (*iter).nMask &= ~INPUT_MOVE_UP; }
                if (pEvent->Key() == Leadwerks::Key::Q) { (*iter).nMask &= ~INPUT_MOVE_DOWN; }

                ++iter;
            }
        }

        static void Update(Components::World& world, uint64_t entity, float dt)
        {
            auto res = Components::World::Get<Entities::Camera>(world, entity);
            auto& input = res.inputComponents->front();
            auto& velocity = res.velocityComponents->front();
            auto& placement = res.placementComponents->front();

            // < Perform any game logic here.
            // < ---
            uint64_t inputMask = input.nMask;
            float dX, dY, dZ;

            // < Are we rotating the camera left or right?
            if ((bool(inputMask & INPUT_ROTATE_RIGHT)) || (bool(inputMask & INPUT_ROTATE_LEFT))) {
                dY = ((bool(inputMask & INPUT_ROTATE_RIGHT)) - (bool(inputMask & INPUT_ROTATE_LEFT))) + input.vDelta.x * dt * velocity.vRotSpeed.y;
                input.nMask &= ~(INPUT_ROTATE_RIGHT | INPUT_ROTATE_LEFT);
            }

            // < Are we tilting the camera up or down?
            if ((bool(inputMask & INPUT_ROTATE_UP)) || (bool(inputMask & INPUT_ROTATE_DOWN))) {
                dX = ((bool(inputMask & INPUT_ROTATE_UP)) - (bool(inputMask & INPUT_ROTATE_DOWN))) + input.vDelta.y * dt * velocity.vRotSpeed.x;
                input.nMask &= ~(INPUT_ROTATE_UP | INPUT_ROTATE_DOWN);
            }

            // < Are we rolling the camera left or right?
            if ((bool(inputMask & INPUT_ROLL_RIGHT)) || (bool(inputMask & INPUT_ROLL_LEFT))) {
                dZ = (((bool(inputMask & INPUT_ROLL_RIGHT)) - (bool(inputMask & INPUT_ROLL_LEFT))) + input.vDelta.z)  * dt * velocity.vRotSpeed.z;
                input.nMask &= ~(INPUT_ROLL_LEFT | INPUT_ROLL_RIGHT);
            }

            // < Are we looking to move the camera?
            float vX = ((bool(inputMask & INPUT_MOVE_RIGHT)) - (bool(inputMask & INPUT_MOVE_LEFT)))		* dt * velocity.vMovSpeed.x;
            float vY = ((bool(inputMask & INPUT_MOVE_UP)) - (bool(inputMask & INPUT_MOVE_DOWN)))		* dt * velocity.vMovSpeed.y;
            float vZ = ((bool(inputMask & INPUT_MOVE_FORWARD)) - (bool(inputMask & INPUT_MOVE_BACKWARD))) * dt * velocity.vMovSpeed.z;

            velocity.vVel.x = vX;
            velocity.vVel.y = vY;
            velocity.vVel.z = vZ;

            placement.vRot += Leadwerks::Vec3(dX, dY, 0.0f);

            // < Set the camera's rotation and position.
            auto& camHndl = res.cameraHandles->front().pCamHndl;

            if (camHndl != nullptr)
            {
                auto cam = camHndl->getInst();

                cam->SetRotation(Leadwerks::Vec3(
                    Leadwerks::Math::Curve(placement.vRot.x, cam->GetRotation().x, 5.0f),
                    Leadwerks::Math::Curve(placement.vRot.y, cam->GetRotation().y, 5.0f),
                    Leadwerks::Math::Curve(placement.vRot.z, cam->GetRotation().z, 5.0f)), false);
                cam->Move(velocity.vVel, true);
            }
        }

    }; // < end class.

} // < end namespace.

#endif _SPECTATOR_CAMERA_ENTITY_HPP_