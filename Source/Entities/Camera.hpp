/*-------------------------------------------------------
                    <copyright>
    
    File: Camera.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Camera System.

    Functions: 
---------------------------------------------------------*/

#ifndef _CAMERA_ENTITY_HPP_
    #define _CAMERA_ENTITY_HPP_
    
#pragma once
#include "Leadwerks.h"
#include "../Common.hpp"
#include "../Managers/InputManager.hpp"

#include "../Utilities/CameraHandle.hpp"
#include "../Utilities/Event.hpp"
#include "../Utilities/Macros.hpp"
#include "../Utilities/Event.hpp"
#include "../Utilities/luatables/luatables.h"

#include "../Mapping/TypeConverter.hpp"

#include "../Components/Component.hpp"
#include "../Components/Camera.hpp"
#include "../Components/ComponentDictionary.hpp"
#include "../Components/Input.hpp"
#include "../Components/Placement.hpp"
#include "../Components/Trigger.hpp"
#include "../Components/Velocity.hpp"
#include "../Components/World.hpp"

#include "../Entities/Entity.hpp"
#include "../Entities/Input.hpp"

#include <exception>
#include <string>
#include <vector>

namespace Entities
{    
    const uint64_t MASK_CAMERA_STATIC = COMPONENT_PLACEMENT;
    const uint64_t MASK_CAMERA_DYNAMIC = COMPONENT_PLACEMENT | COMPONENT_VELOCITY;
    const uint64_t MASK_CAMERA_FREE = COMPONENT_INPUT | COMPONENT_PLACEMENT | COMPONENT_VELOCITY;

    const uint64_t MASK_CAMERA_TOPDOWN = MASK_CAMERA_DYNAMIC | COMPONENT_RELATIONSHIP;    

    class Camera : public Entities::Entity<Camera>, public Entities::Input<Camera>
    {
		CLASS_TYPE(Camera);

    public:               

        Camera(void);

		Components::Component					 component;
        std::vector<Components::Input<Camera>>*  inputComponents;
        std::vector<Components::Placement>*      placementComponents;
        std::vector<Components::Velocity>*       velocityComponents;
        std::vector<Components::Camera>*         cameraHandles;		

        Components::Input<Camera>   input;
        Components::Placement       placement;
        Components::Velocity        velocity;
        Components::Camera          cameraHandle;		

        static uint64_t Create(Components::World& world, std::string scriptPath = "");        

        static void Load(Components::World& pWorld, uint64_t entity, CameraHandle* pCamHndl);        

        static void Close(Components::World& world, uint64_t entity);        

        static void Update(InputManager* pInputMgr, Components::World& world, uint64_t entity, float deltaTime);        

    protected:        

    }; // < end class.

} // < end namespace.

template <> Entities::Camera TypeConverter::Convert<LuaTable, Entities::Camera>(LuaTable& source);

template <> void Components::World::Add<Entities::Camera>(Components::World& world, uint64_t entity, Entities::Camera& source);

template <> Entities::Camera Components::World::Get<Entities::Camera>(Components::World& world, uint64_t);

template <> std::vector<Entities::Camera> Components::World::GetAll<Entities::Camera>(Components::World& world);

#endif _CAMERA_ENTITY_HPP_