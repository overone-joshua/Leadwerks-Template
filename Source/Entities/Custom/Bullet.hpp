#ifndef _BULLET_ENTITY_HPP_
	#define _BULLET_ENTITY_HPP_

#pragma once
#include "../../Common.hpp"
#include "../../Utilities/Macros.hpp"
#include "../../Utilities/luatables/luatables.h"

#include "../../Mapping/TypeConverter.hpp"

#include "../../Components/World.hpp"
#include"../../Components/Collider.hpp"
#include "../../Components/Relationship.hpp"

#include "../Entity.hpp"
#include "../Actor.hpp"

#include <vector>
#include <queue>

namespace Entities
{
    const uint64_t MASK_BULLET = COMPONENT_APPEARANCE | COMPONENT_COLLIDER | COMPONENT_PLACEMENT | COMPONENT_RELATIONSHIP | COMPONENT_VELOCITY;

	class Bullet: public Entities::Entity<Bullet>, public Entities::Actor
	{
        CLASS_TYPE(Bullet);

	public:

        Bullet(void);

        std::vector<Components::Collider>*       colliderComponents;
        std::vector<Components::Relationship>*  relationshipComponents;

        Components::Collider                     collider;
        Components::Relationship                relationship;

        static uint64_t Create(Components::World& world, std::string _cScriptPath);

        static void Load(Components::World& world, uint64_t entity, uint64_t relatedEntity, Leadwerks::Vec3 vDir);

        static void Close(Components::World& world, uint64_t entity);

        static void Update(Components::World& world, Entities::Bullet entity, Leadwerks::World* pWorld, float dt);

        static void UpdateAll(Components::World& world, Leadwerks::World* pWorld, float dt);

	}; // < end class.

} // < end namespace.

template <> Entities::Bullet TypeConverter::Convert<LuaTable, Entities::Bullet>(LuaTable& source);

template <> void Components::World::Add<Entities::Bullet>(Components::World& world, uint64_t entity, Entities::Bullet& source);

template <> Entities::Bullet Components::World::Get<Entities::Bullet>(Components::World& world, uint64_t entity);

template <> std::vector<Entities::Bullet> Components::World::GetAll<Entities::Bullet>(Components::World& world);

#endif _BULLET_ENTITY_HPP_