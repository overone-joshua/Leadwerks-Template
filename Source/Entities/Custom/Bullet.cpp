#pragma once
#include "bullet.hpp"

namespace Entities
{
    Bullet::Bullet(void)
        : colliderComponents(nullptr), relationshipComponents(nullptr)
    {

    }

    uint64_t Bullet::Create(Components::World& world, std::string _cScriptPath)
    {
        auto table = LuaTable::fromFile(_cScriptPath.c_str());
        auto hndl = TypeConverter::Convert<LuaTable, Entities::Bullet>(table);

        auto entity = world.CreateEntity(&world);
        world.Get(entity) = Entities::MASK_BULLET;

        Components::World::Add(world, entity, hndl);

        return entity;
    }

    void Bullet::Load(Components::World& world, uint64_t entity, uint64_t relatedEntity, Leadwerks::Vec3 vDir)
    {
        Entities::Actor::Load(world, entity);
        auto rel = Components::World::Get<Entities::Actor>(world, relatedEntity);

        auto bullet = Components::World::Get<Entities::Bullet>(world, entity);
        auto& placement = bullet.placementComponents->front();
        auto& velocity = bullet.velocityComponents->front();
        auto& input = bullet.inputComponents->front();

        placement.vPos = rel.placementComponents->front().vPos;

        placement.vPos.x += Leadwerks::Math::Random(-1, 1);

        velocity.vVel = vDir.Multiply(input.vMovSpeed);
    }

    void Bullet::Close(Components::World& world, uint64_t entity)
    {
        Entities::Actor::Close(world, entity);
    }

    void Bullet::Update(Components::World& world, Entities::Bullet entity, Leadwerks::World* pWorld, float dt)
    {
        auto& placement = entity.placementComponents->front();
        auto& velocity = entity.velocityComponents->front();
        auto& input = entity.inputComponents->front();
        auto model = entity.appearanceComponents->front().pModel;

        auto& vPos = placement.vPos;
        auto& vVel = velocity.vVel;
        auto vSpeed = input.vMovSpeed;
        auto vEnd = vPos.Add(vVel);

        if (model != nullptr)
        {
            // < Move the bullet.
            vPos = vPos.Add(vVel);

            // < Move the model.
            model->SetPosition(vPos, true);
        }
    }

    void Bullet::UpdateAll(Components::World& world, Leadwerks::World* pWorld, float dt)
    {
        std::queue<uint64_t> deletionQueue;

        auto bullets = Components::World::GetAll<Entities::Bullet>(world);
        auto iter = bullets.begin();
        while (iter != bullets.end())
        {
            if ((*iter).placementComponents->front().vPos.z >= 100.0f)
            {
                deletionQueue.push((*iter).placementComponents->front().nId);
            }
            else
            {
                Entities::Bullet::Update(world, (*iter), pWorld, dt);
            }
            ++iter;
        }

        while (!deletionQueue.empty())
        {
            world.DestroyEntity(&world, deletionQueue.front());
            deletionQueue.pop();
        }

    }

} // < end namespace.

template <> Entities::Bullet TypeConverter::Convert<LuaTable, Entities::Bullet>(LuaTable& source)
{
    Entities::Bullet hndl;

    static_cast<Entities::Actor&>(hndl) = TypeConverter::Convert<LuaTable, Entities::Actor>(source);

    return hndl;
}

template <> void Components::World::Add<Entities::Bullet>(Components::World& world, uint64_t entity, Entities::Bullet& source)
{
    auto bullet = world.Get<Entities::Bullet>(world, entity);

    world.AddComponent(&world, entity, source.relationship);

    Components::World::Add<Entities::Actor>(world, entity, source);
}

template <> Entities::Bullet Components::World::Get<Entities::Bullet>(Components::World& world, uint64_t entity)
{
    Entities::Bullet hndl;

    static_cast<Entities::Actor&>(hndl) = Components::World::Get<Entities::Actor>(world, entity);

    hndl.relationshipComponents = world.Fetch<Components::Relationship>(&world, entity);

    return hndl;
}

template <> std::vector<Entities::Bullet> Components::World::GetAll<Entities::Bullet>(Components::World& world)
{
    std::vector<Entities::Bullet> results;

    auto entities = world.GetEntities(&world, Entities::MASK_BULLET);

    auto iter = entities.begin();
    while (iter != entities.end())
    {
        results.push_back(Components::World::Get<Entities::Bullet>(world, (*iter)));
        ++iter;
    }

    return results;
}
