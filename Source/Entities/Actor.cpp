#pragma once
#include "Actor.hpp"

namespace Entities
{
	Actor::Actor(void)
		: inputComponents(nullptr), placementComponents(nullptr), velocityComponents(nullptr)
		, appearanceComponents(nullptr) { }

    uint64_t Actor::Create(Components::World& world, std::string cScriptPath)
    {
        // < Load the script containing our actor information.
        auto table = LuaTable::fromFile(cScriptPath.c_str());

        // < Convert our actor script into an actor handle.
        Actor hndl = TypeConverter::Convert<LuaTable, Actor>(table);

        // < Add the entity to the world.
		auto entity = world.CreateEntity(&world);
		world.Get(entity) = Entities::MASK_ACTOR;

        Components::World::Add(world, entity, hndl);

        return entity;
    }

    void Actor::Load(Components::World& world, uint64_t entity)
    {
        auto res = Components::World::Get<Actor>(world, entity);

		auto iter = res.appearanceComponents->begin();
		while (iter != res.appearanceComponents->end())
		{
			auto path = (*iter).cModelPath;
			auto vPos = res.placementComponents->front().vPos;
			auto vRot = res.placementComponents->front().vRot;
			auto vSca = res.placementComponents->front().vSca;

			// < Create the actor's model.
            if (path.compare("box") == 0 || path.compare("Box") == 0)
            {
                (*iter).pModel = Leadwerks::Model::Box(0.25f, 0.25f, 0.25f, nullptr);
            }
            else
            {
                (*iter).pModel = Leadwerks::Model::Load(path);
            }

            (*iter).pModel->SetScale(vSca);
            (*iter).pModel->SetRotation(vRot, false);
            (*iter).pModel->SetPosition(vPos, true);

			++iter;
		}
    }

    void Actor::Close(Components::World& world, uint64_t entity)
    {
		auto res = Components::World::Get<Actor>(world, entity);

        auto iter = res.appearanceComponents->begin();
        while (iter != res.appearanceComponents->end())
        {

            auto* model = (*iter).pModel;

            if (model != nullptr)
            {
                SAFE_RELEASE(model);
                SAFE_DELETE(model);
            }

            iter = res.appearanceComponents->erase(iter);
            if (iter != res.appearanceComponents->end())
            {
                ++iter;
            }
        }
    }

} // < end namespace.

// < Convert our lua Actor script into an Actor object.
template <> Entities::Actor TypeConverter::Convert<LuaTable, Entities::Actor>(LuaTable& source)
{
	Entities::Actor hndl;

	// < Extract all required actor information.
	auto name = source["name"].get<std::string>();
	auto vPos = source["pos"].get<Leadwerks::Vec3>();
	auto vRot = source["rot"].get<Leadwerks::Vec3>();
	auto vSca = source["sca"].get<Leadwerks::Vec3>();
    auto vMovSpeed = source["movSpeed"].get<Leadwerks::Vec3>();
    auto vRotSpeed = source["rotSpeed"].get<Leadwerks::Vec3>();
	auto path = source["modelPath"].get<std::string>();
	auto vVel = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);

	hndl.component = Components::Component(name);
	hndl.appearance = Components::Appearance(path, name);
	hndl.input = Components::Input<Entities::Actor>(vMovSpeed, vRotSpeed, name);
	hndl.placement = Components::Placement(vPos, vRot, vSca, name);
	hndl.velocity = Components::Velocity(vVel, name);

	return hndl;
}

// < Add our actor handle object to our world as its individual components.
template <> void Components::World::Add<Entities::Actor>(Components::World& world, uint64_t entity, Entities::Actor& source)
{
    // < Create the components required to form an Actor.
    world.AddComponent(&world, entity, source.appearance);
    world.AddComponent(&world, entity, source.input);
    world.AddComponent(&world, entity, source.placement);
    world.AddComponent(&world, entity, source.velocity);
}

template <>
Entities::Input<Entities::Actor> Components::World::Get<Entities::Input<Entities::Actor>>(Components::World& world, uint64_t entity)
{
	Entities::Input<Entities::Actor> hndl;

	hndl.mouseMoveTriggers = world.Fetch<Components::MouseMoveTrigger<Entities::Actor>>(&world, entity);
	hndl.mouseHitTriggers = world.Fetch<Components::MouseHitTrigger<Entities::Actor>>(&world, entity);
	hndl.mouseDownTriggers = world.Fetch<Components::MouseDownTrigger<Entities::Actor>>(&world, entity);
	hndl.mouseUpTriggers = world.Fetch<Components::MouseUpTrigger<Entities::Actor>>(&world, entity);
	hndl.keyHitTriggers = world.Fetch<Components::KeyHitTrigger<Entities::Actor>>(&world, entity);
	hndl.keyDownTriggers = world.Fetch<Components::KeyDownTrigger<Entities::Actor>>(&world, entity);
	hndl.keyUpTriggers = world.Fetch<Components::KeyUpTrigger<Entities::Actor>>(&world, entity);

	return hndl;
}

template <> Entities::Actor Components::World::Get<Entities::Actor>(Components::World& world, uint64_t entity)
{
    Entities::Actor hndl;

    static_cast<Entities::Input<Entities::Actor>&>(hndl) = Components::World::Get<Entities::Input<Entities::Actor>>(world, entity);

    hndl.appearanceComponents = world.Fetch<Components::Appearance>(&world, entity);
    hndl.inputComponents = world.Fetch<Components::Input<Entities::Actor>>(&world, entity);
    hndl.placementComponents = world.Fetch<Components::Placement>(&world, entity);
    hndl.velocityComponents = world.Fetch<Components::Velocity>(&world, entity);

    hndl.component = Components::Component("Actor");
    hndl.component.nId = entity;

    return hndl;
}

// < Get a reference to all actors from the world.
template <> std::vector<Entities::Actor> Components::World::GetAll<Entities::Actor>(Components::World& world)
{
    std::vector<Entities::Actor> results;

    auto entities = world.GetEntities(&world, Entities::MASK_ACTOR);

    auto iter = entities.begin();
    while (iter != entities.end())
    {
        results.push_back(Components::World::Get<Entities::Actor>(world, (*iter)));
        ++iter;
    }

    return results;
}