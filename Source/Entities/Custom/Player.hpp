#ifndef _PLAYER_ENTITY_HPP_
    #define _PLAYER_ENTITY_HPP_

#pragma once
#include "Leadwerks.h"
#include "../../Common.hpp"
#include "../../Utilities/Event.hpp"

#include "../Entity.hpp"
#include "../Actor.hpp"
#include "../Input.hpp"

#include "../Custom/Bullet.hpp"

#include "../../Components/World.hpp"
#include "../../Components/Trigger.hpp"
#include "../../Components//Custom/MouseMoveTrigger.hpp"
#include "../../Components//Custom/KeyDownTrigger.hpp"
#include "../../Components//Custom/KeyUpTrigger.hpp"

namespace Entities
{
    class Player : public Entities::Entity<Player>
    {
        CLASS_TYPE(Player);

    public:

        Player(void) { }

        static uint64_t Create(Components::World& world, std::string _cScriptPath)
        {
            auto entity = Entities::Actor::Create(world, _cScriptPath);

            // < Wire up our game logic events for each entity.
            Entities::Actor::BindKeyDown<&Player::KeyDown>(world, entity, "Player");
            Entities::Actor::BindKeyUp<&Player::KeyUp>(world, entity, "Player");

            return entity;
        }

        static void KeyDown(Components::World& world, Entities::Actor entity, Event_KeyDown* pEvent)
        {
            // < Check for any key presses from the keyboard. If any key is pressed
            // * we should look to move the camera.
            auto iter = entity.inputComponents->begin();
            while (iter != entity.inputComponents->end())
            {
                if (pEvent->Key() == Leadwerks::Key::Up) { (*iter).nMask |= INPUT_MOVE_FORWARD; }
                if (pEvent->Key() == Leadwerks::Key::Left) { (*iter).nMask |= INPUT_MOVE_LEFT; }
                if (pEvent->Key() == Leadwerks::Key::Down) { (*iter).nMask |= INPUT_MOVE_BACKWARD; }
                if (pEvent->Key() == Leadwerks::Key::Right) { (*iter).nMask |= INPUT_MOVE_RIGHT; }

                if (pEvent->Key() == Leadwerks::Key::X) { (*iter).nMask |= INPUT_ACTION_CROUCH; }
                if (pEvent->Key() == Leadwerks::Key::Z) { (*iter).nMask |= INPUT_ACTION_PRIMARY; }

                ++iter;
            }
        }

        static void KeyUp(Components::World& world, Entities::Actor entity, Event_KeyUp* pEvent)
        {
            // < Just like key press however, here we pop the movement bitmask to signal
            // * a key release.
            auto iter = entity.inputComponents->begin();
            while (iter != entity.inputComponents->end())
            {
                if (pEvent->Key() == Leadwerks::Key::Up) { (*iter).nMask &= ~INPUT_MOVE_FORWARD; }
                if (pEvent->Key() == Leadwerks::Key::Left) { (*iter).nMask &= ~INPUT_MOVE_LEFT; }
                if (pEvent->Key() == Leadwerks::Key::Down) { (*iter).nMask &= ~INPUT_MOVE_BACKWARD; }
                if (pEvent->Key() == Leadwerks::Key::Right) { (*iter).nMask &= ~INPUT_MOVE_RIGHT; }

                if (pEvent->Key() == Leadwerks::Key::X) { (*iter).nMask &= ~INPUT_ACTION_CROUCH; }
                if (pEvent->Key() == Leadwerks::Key::Z) { (*iter).nMask &= ~INPUT_ACTION_PRIMARY; }

                ++iter;
            }
        }

        static void Update(Components::World& world, uint64_t entity, float dt)
        {
            auto res = Components::World::Get<Entities::Actor>(world, entity);
            auto& input = res.inputComponents->front();
            auto& velocity = res.velocityComponents->front();
            auto& placement = res.placementComponents->front();
            auto& model = res.appearanceComponents->front().pModel;

            // < Perform any game logic here.
            // < ---
            uint64_t inputMask = input.nMask;

            // < Are we looking to move the camera?
            float vX = ((bool(inputMask & INPUT_MOVE_RIGHT)) - (bool(inputMask & INPUT_MOVE_LEFT)))		* dt * input.vMovSpeed.x;
            float vY = ((bool(inputMask & INPUT_MOVE_UP)) - (bool(inputMask & INPUT_MOVE_DOWN)))		* dt * input.vMovSpeed.y;
            float vZ = ((bool(inputMask & INPUT_MOVE_FORWARD)) - (bool(inputMask & INPUT_MOVE_BACKWARD))) * dt * input.vMovSpeed.z;

            velocity.vVel = Leadwerks::Vec3(vX, vY, vZ);

            if ( (bool(inputMask & INPUT_ACTION_CROUCH)) == 1 )
            {
                velocity.vVel = velocity.vVel.Multiply(Leadwerks::Vec3(0.5f, 0.5f, 0.5f));
            }

            static unsigned frame = 0;
            if ( (bool(inputMask & INPUT_ACTION_PRIMARY)) == 1)
            {
                // < Create, Load and Fire a bullet.
                auto bullet = Entities::Bullet::Create(world, "./Scripts/DefaultBullet.lua");
                Entities::Bullet::Load(world, bullet, entity, Leadwerks::Vec3(0.0f, 0.0f, 1.0f));
            }
            frame += 1;

            if (frame > 60)
            {
                frame = 0;
            }
            // < Set the models position.
            placement.vPos = placement.vPos.Add(velocity.vVel);

            model->SetPosition(placement.vPos, true);
        }

    }; // < end class.

} // < end namespace.

#endif _PLAYER_ENTITY_HPP_