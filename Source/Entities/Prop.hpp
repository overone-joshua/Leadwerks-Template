/*-------------------------------------------------------
                <copyright>

    File: Prop.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for Prop System.

    Functions: 1. static inline uint64_t Create(Components::World* pWorld, std::string cScriptPath);

---------------------------------------------------------*/

#ifndef _PROP_ENTITY_HPP_
    #define _PROP_ENTITY_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Components/Component.hpp"
#include "../Components//ComponentDictionary.hpp"

#include "../Components/Appearance.hpp"
#include "../Components/Placement.hpp"
#include "../Components/World.hpp"

#include "../Utilities/luatables/luatables.h"

#include <string>

namespace Entities
{
    const unsigned MASK_PROP = COMPONENT_APPEARANCE | COMPONENT_PLACEMENT;

    class Prop
    {
    public:
        static inline uint64_t Create(Components::World* pWorld, std::string cScriptPath)
        {
            uint64_t entity = pWorld->CreateEntity(pWorld);            
            pWorld->Get(entity) = MASK_PROP;

            // < Load and read the given script.
            auto table = LuaTable::fromFile(cScriptPath.c_str());
            auto name = table["name"].get<std::string>();
			auto vPos = table["pos"].get<Leadwerks::Vec3>();
			auto vRot = table["rot"].get<Leadwerks::Vec3>();
			auto vSca = table["sca"].get<Leadwerks::Vec3>();
			auto path = table["modelPath"].get<std::string>();
			
            // < Create required components.
            pWorld->AddComponent<Components::Placement>(pWorld, entity, Components::Placement(vPos, vRot, vSca, name));
            pWorld->AddComponent<Components::Appearance>(pWorld, entity, Components::Appearance(path, name));
            
            // < Create associated model and initialize.
            auto pModel = Leadwerks::Model::Load(path);
            pModel->SetScale(vSca);
            pModel->SetRotation(vRot, false);
            pModel->SetPosition(vPos, true);

            return entity;
        }

    }; // < end class.

} // < end namespace.


#endif _PROP_ENTITY_HPP_