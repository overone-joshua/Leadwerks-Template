/*-------------------------------------------------------
                    <copyright>

    File: Actor.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for Actor System.

    Functions:
---------------------------------------------------------*/

#ifndef _ACTOR_ENTITY_HPP_
    #define _ACTOR_ENTITY_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Managers/InputManager.hpp"

#include "../Common.hpp"
#include "../Utilities/Macros.hpp"
#include "../Utilities/Event.hpp"
#include "../Utilities/luatables/luatables.h"

#include "../Mapping/TypeConverter.hpp"

#include "../Components/Component.hpp"
#include "../Components/ComponentDictionary.hpp"
#include "../Components/World.hpp"
#include "../Components/Appearance.hpp"
#include "../Components/Input.hpp"
#include "../Components/Placement.hpp"
#include "../Components/Velocity.hpp"

#include "Entity.hpp"
#include "Input.hpp"

#include <string>
#include <vector>

namespace Entities
{
    const uint64_t MASK_ACTOR = COMPONENT_APPEARANCE | COMPONENT_INPUT | COMPONENT_PLACEMENT | COMPONENT_TRIGGER | COMPONENT_VELOCITY;

    class Actor : public Entity<Actor>, public Input<Actor>
    {
    public:
		Actor(void);

        Components::Component                   component;
        std::vector<Components::Appearance>*    appearanceComponents;
        std::vector<Components::Input>*  inputComponents;
        std::vector<Components::Placement>*     placementComponents;
        std::vector<Components::Velocity>*      velocityComponents;

		Components::Appearance		appearance;
		Components::Input	input;
		Components::Placement		placement;
		Components::Velocity		velocity;

        static uint64_t Create(Components::World& world, std::string cScriptPath = "");

        static void Load(Components::World& world, uint64_t entity);

        static void Close(Components::World& world, uint64_t entity);

    }; // < end class.

} // < end namespace.

template <> Entities::Actor TypeConverter::Convert<LuaTable, Entities::Actor>(LuaTable& source);

template <> void Components::World::Add<Entities::Actor>(Components::World& world, uint64_t entity, Entities::Actor& source);

template <> Entities::Actor Components::World::Get<Entities::Actor>(Components::World& world, uint64_t entity);
template <> Entities::Input<Entities::Actor> Components::World::Get<Entities::Input<Entities::Actor>>(Components::World& world, uint64_t entity);

template <> std::vector<Entities::Actor> Components::World::GetAll<Entities::Actor>(Components::World& world);

#endif _ACTOR_ENTITY_HPP_