#pragma once
#include "Actor.hpp"

namespace Entities
{

    uint64_t Actor::Create(Components::World& world, std::string cScriptPath)
    {
        // < Load the script containing our actor information.
        auto table = LuaTable::fromFile(cScriptPath.c_str());

        // < Convert our actor script into an actor handle.
        Actor hndl = TypeConverter::Convert<LuaTable, Actor>(table);

        // < Add the entity to the world.
        auto entity = Components::World::Add(world, hndl);

        return entity;
    }

    void Actor::Load(Components::World& world, uint64_t entity)
    {
        auto res = Components::World::Get<Actor>(world, entity);

        // < Create the actor's model. 
        res.models.push_back(Leadwerks::Model::Load(res.appearanceComponents.front().cModelPath));
        res.models.front()->SetScale(res.placementComponents.front().vSca);
        res.models.front()->SetRotation(res.placementComponents.front().vRot, false);
        res.models.front()->SetPosition(res.placementComponents.front().vPos, true);
    }

    void Actor::LoadAll(Components::World& world)
    {
        auto entities = Components::World::GetAll<Actor>(world);
        auto iter = entities.begin();
        while (iter != entities.end())
        {
            auto hndl = (*iter).models;
            // < Perform initialization here.
            // * ---                                        

            // < Create the actor's model. 
            hndl.push_back(Leadwerks::Model::Load((*iter).appearanceComponents.front().cModelPath));
            hndl.front()->SetScale((*iter).placementComponents.front().vSca);
            hndl.front()->SetRotation((*iter).placementComponents.front().vRot, false);
            hndl.front()->SetPosition((*iter).placementComponents.front().vPos, true);

            // < ---

            iter++;

        }
    }

    void Actor::Close(Components::World& world, uint64_t entity)
    {
        
    }

    void Actor::CloseAll(Components::World& world)
    {
        auto entities = Components::World::GetAll<Actor>(world);
        auto iter = entities.begin();
        while (iter != entities.end())
        {
            auto hndl = (*iter).models;

            auto it = hndl.begin();
            while (it != hndl.end())
            {
                if ((*it) != nullptr)
                {
                    auto model = (*it);
                    SAFE_RELEASE(model);
                    SAFE_DELETE(model);
                }

                it++;
            }
            hndl.clear();

            iter++;

        }
        entities.clear();
    }

    void Actor::Update(InputManager* pInputMgr, Components::World& world, uint64_t entity, float dt)
    {
        auto entities = Components::World::GetAll<Actor>(world);
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
	hndl.appearanceComponents.push_back(Components::Appearance(path, name));
	hndl.inputComponents.push_back(Components::Input<Entities::Actor>(vMovSpeed, vRotSpeed, name));
	hndl.placementComponents.push_back(Components::Placement(vPos, vRot, vSca, name));
	hndl.velocityComponents.push_back(Components::Velocity(vVel, name));

	return hndl;
}

// < Add our actor handle object to our world as its individual components.
template <> uint64_t Components::World::Add<Entities::Actor>(Components::World& world, Entities::Actor& source)
{    
    // < Create a new entity of type Actor.
    auto entity = world.CreateEntity(&world);
    world.Get(entity) = Entities::MASK_ACTOR;

    // < Create the components required to form an Actor.                        
    world.AddComponent(&world, entity, source.appearanceComponents.front());
    world.AddComponent(&world, entity, source.inputComponents.front());
    world.AddComponent(&world, entity, source.placementComponents.front());
    world.AddComponent(&world, entity, source.velocityComponents.front());

    return entity;
}

// < Get a reference to all our entities components by getting the equivilent
// * Actor from the world.
template <> Entities::Actor Components::World::Get<Entities::Actor>(Components::World& world, uint64_t entity)
{    
    Entities::Actor hndl;

    auto appearanceComponents = world.GetComponents<Components::Appearance>(&world, entity);
    auto inputComponents = world.GetComponents<Components::Input<Entities::Actor>>(&world, entity);
    auto placementComponents = world.GetComponents<Components::Placement>(&world, entity);
    auto velocityComponents = world.GetComponents<Components::Velocity>(&world, entity);
    
    hndl.appearanceComponents = *appearanceComponents;
    hndl.inputComponents = *inputComponents;
    hndl.placementComponents = *placementComponents;
    hndl.velocityComponents = *velocityComponents;

    hndl.component = Components::Component(appearanceComponents->front().cName);
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
        iter++;
    }

    return results;
}