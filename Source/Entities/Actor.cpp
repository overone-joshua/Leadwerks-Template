#pragma once
#include "Actor.hpp"

// < Convert our lua Actor script into an ActorHandle object.
template <> ActorHandle TypeConverter::Convert<LuaTable, ActorHandle>(LuaTable& source)
{
	ActorHandle hndl;

	// < Extract all required actor information.
	auto name = source["name"].get<std::string>();
	auto vPos = source["pos"].get<Leadwerks::Vec3>();
	auto vRot = source["rot"].get<Leadwerks::Vec3>();
	auto vSca = source["sca"].get<Leadwerks::Vec3>();
	auto path = source["modelPath"].get<std::string>();
	auto vVel = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);

	hndl.component = Components::Component(name);
	hndl.appearance.push_back(Components::Appearance(path, name));
	hndl.input.push_back(Components::Input(name));
	hndl.placement.push_back(Components::Placement(vPos, vRot, vSca, name));
	hndl.velocity.push_back(Components::Velocity(vVel, name));

	return hndl;
}

// < Add our actor handle object to our world as its individual components.
template <> uint64_t Components::World::Add<ActorHandle>(Components::World& world, ActorHandle& source)
{
    using namespace Entities;

    // < Create a new entity of type Actor.
    auto entity = world.CreateEntity(&world);
    world.Get(entity) = MASK_ACTOR;

    // < Create the components required to form an Actor.                        
    world.AddComponent(&world, entity, source.appearance.front());
    world.AddComponent(&world, entity, source.input.front());
    world.AddComponent(&world, entity, source.placement.front());
    world.AddComponent(&world, entity, source.velocity.front());

    return entity;
}

// < Get a reference to all our entities components by getting the equivilent
// * ActorHandle from the world.
template <> ActorHandle Components::World::Get<ActorHandle>(Components::World& world, uint64_t entity)
{
    using namespace Entities;
    ActorHandle hndl;

    auto appearanceComponents = world.GetComponents<Components::Appearance>(&world, entity);
    auto inputComponents = world.GetComponents<Components::Input>(&world, entity);
    auto placementComponents = world.GetComponents<Components::Placement>(&world, entity);
    auto velocityComponents = world.GetComponents<Components::Velocity>(&world, entity);

    hndl.component = Components::Component();
    hndl.appearance = *appearanceComponents;
    hndl.input = *inputComponents;
    hndl.placement = *placementComponents;
    hndl.velocity = *velocityComponents;

    return hndl;
}

// < Get a reference to all actors from the world.
template <> std::vector<ActorHandle> Components::World::GetAll<ActorHandle>(Components::World& world)
{
    using namespace Entities;
    std::vector<ActorHandle> results;

    auto entities = world.GetEntities(&world, MASK_ACTOR);

    auto iter = entities.begin();
    while (iter != entities.end())
    {
        results.push_back(Components::World::Get<ActorHandle>(world, (*iter)));
        iter++;
    }

    return results;
}