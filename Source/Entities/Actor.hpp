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

#include <string>
#include <vector>

namespace Entities
{
    const uint64_t MASK_ACTOR = COMPONENT_APPEARANCE | COMPONENT_PLACEMENT | COMPONENT_INPUT | COMPONENT_VELOCITY;           

    class Actor : public Entity<Actor>
    {            
    public:

        Components::Component                      component;
        std::vector<Components::Appearance>        appearanceComponents;
        std::vector<Components::Input<Actor>>       inputComponents;
        std::vector<Components::Placement>         placementComponents;
        std::vector<Components::Velocity>          velocityComponents;
        std::vector<Leadwerks::Model*>             models;

        static uint64_t Create(Components::World& world, std::string cScriptPath = "");
        
        static void Load(Components::World& world, uint64_t entity);
        static void LoadAll(Components::World& world);

        static void Close(Components::World& world, uint64_t entity);
        static void CloseAll(Components::World& world);

        static void Update(InputManager* pInputMgr, Components::World& world, uint64_t entity, float dt);
        
        static void OnKeyDown(Components::World& world, uint64_t entity, Event_KeyDown* pEvent);

        static void OnKeyUp(Components::World& world, uint64_t entity, Event_KeyUp* pEvent);

    protected:

        void OnKeyDown(Components::World& world, Event_KeyDown* pData);        

        void OnKeyUp(Components::World& world, Event_KeyUp* pData);

    }; // < end class.
    
} // < end namespace.

template <> Entities::Actor TypeConverter::Convert<LuaTable, Entities::Actor>(LuaTable& source);

template <> void Components::World::Add<Entities::Actor>(Components::World& world, uint64_t entity, Entities::Actor& source);

template <> Entities::Actor Components::World::Get<Entities::Actor>(Components::World& world, uint64_t entity);

template <> std::vector<Entities::Actor> Components::World::GetAll<Entities::Actor>(Components::World& world);

#endif _ACTOR_ENTITY_HPP_