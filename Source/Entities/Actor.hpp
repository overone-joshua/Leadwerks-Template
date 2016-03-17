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
#include "../Utilities/Macros.hpp"
#include "../Managers/InputManager.hpp"
#include "../Mapping/TypeConverter.hpp"
#include "Entity.hpp"

#include "../Components/Component.hpp"
#include "../Components/ComponentDictionary.hpp"
#include "../Components/World.hpp"
#include "../Components/Appearance.hpp"
#include "../Components/Input.hpp"
#include "../Components/Placement.hpp"
#include "../Components/Velocity.hpp"

#include "../Utilities/luatables/luatables.h"

#include <string>
#include <vector>

typedef struct ActorHandle
{
	Components::Component                      component;
	std::vector<Components::Appearance>        appearance;
	std::vector<Components::Input>             input;
	std::vector<Components::Placement>         placement;
	std::vector<Components::Velocity>          velocity;
	std::vector<Leadwerks::Model*>              models;

} ActorHandle; // < end struct.

template <> ActorHandle TypeConverter::Convert<LuaTable, ActorHandle>(LuaTable& source);

template <> uint64_t Components::World::Add<ActorHandle>(Components::World& world, ActorHandle& source);
template <> ActorHandle Components::World::Get<ActorHandle>(Components::World& world, uint64_t entity);
template <> std::vector<ActorHandle> Components::World::GetAll<ActorHandle>(Components::World& world);


namespace Entities
{
    const uint64_t MASK_ACTOR = COMPONENT_APPEARANCE | COMPONENT_PLACEMENT | COMPONENT_INPUT | COMPONENT_VELOCITY;       

    class Actor
    {            
    public:

        static inline uint64_t Create(Components::World& world, std::string cScriptPath)
        {            
            // < Load the script containing our actor information.
            auto table = LuaTable::fromFile(cScriptPath.c_str());
            
            // < Convert our actor script into an actor handle.
            ActorHandle hndl = TypeConverter::Convert<LuaTable, ActorHandle>(table);                       

            // < Add the entity to the world.
            auto entity = Components::World::Add(world, hndl);                                   
            
            return entity;
        }
        
        static void Load(Components::World& world)
        {
            auto entities = Components::World::GetAll<ActorHandle>(world);
            auto iter = entities.begin();
            while (iter != entities.end())
            {
                auto hndl = (*iter);
                // < Perform initialization here.
                // * ---                                        

                // < Create the actor's model. 
                hndl.models.push_back(Leadwerks::Model::Load(hndl.appearance.front().cModelPath));
                hndl.models.front()->SetScale(hndl.placement.front().vSca);
                hndl.models.front()->SetRotation(hndl.placement.front().vRot, false);
                hndl.models.front()->SetPosition(hndl.placement.front().vPos, true);

                // < ---

                iter++;

            }

        }

        static void Close(Components::World& world)
        {
            auto entities = Components::World::GetAll<ActorHandle>(world);
            auto iter = entities.begin();
            while (iter != entities.end())
            {
                auto hndl = (*iter);

                auto it = hndl.models.begin();
                while (it != hndl.models.end())
                {
                    if ((*it) != nullptr)
                    {
                        auto model = (*it);
                        SAFE_RELEASE(model);
                        SAFE_DELETE(model);
                    }
                    
                    it++;
                }
                hndl.models.clear();

                iter++;

            }
            entities.clear();
        }

        static void Update(InputManager* pInputMgr, Components::World& world, float dt)
        {
            auto entities = Components::World::GetAll<ActorHandle>(world);
        }        
        
    }; // < end class.
    
} // < end namespace.

#endif _ACTOR_ENTITY_HPP_