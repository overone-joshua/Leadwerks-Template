#ifndef _THIRD_PERSON_CAMERA_ENTITY_HPP_
	#define _THIRD_PERSON_CAMERA_ENTITY_HPP_

#pragma once
#include "../../Common.hpp"
#include "../../Utilities/Macros.hpp"

#include "../../Mapping/TypeConverter.hpp"

#include "../../Components/World.hpp"
#include "../../Components/Relationship.hpp"

#include "../Entity.hpp"
#include "../Actor.hpp"
#include "../Camera.hpp"

#include <vector>

namespace Entities
{
    const uint64_t MASK_CAMERA_THIRDPERSON = Entities::MASK_CAMERA | COMPONENT_RELATIONSHIP;

	class ThirdPersonCamera : public Entities::Entity<ThirdPersonCamera>, public Entities::Camera
	{
        CLASS_TYPE(ThirdPersonCamera);

	public:

		ThirdPersonCamera(void) { }

        std::vector<Components::Relationship>* relationshipComponents;

        Components::Relationship relationship;

        static uint64_t Create(Components::World& world, std::string _cScriptPath);

        static void Load(Components::World& world, uint64_t entity, uint64_t relatedEntity, CameraHandle* pCamHndl);

        static void Close(Components::World& world, uint64_t entity);

        static void Update(Components::World& world, uint64_t entity, float dt);

	}; // < end class.

} // < end namespace.

template <> Entities::ThirdPersonCamera TypeConverter::Convert<LuaTable, Entities::ThirdPersonCamera>(LuaTable& source);

template <> void Components::World::Add<Entities::ThirdPersonCamera>(Components::World& world, uint64_t entity, Entities::ThirdPersonCamera& source);

template <> Entities::ThirdPersonCamera Components::World::Get<Entities::ThirdPersonCamera>(Components::World& world, uint64_t entity);

#endif _THIRD_PERSON_CAMERA_ENTITY_HPP_