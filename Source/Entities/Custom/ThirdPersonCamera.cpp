#pragma once
#include "ThirdPersonCamera.hpp"

namespace Entities
{
    uint64_t ThirdPersonCamera::Create(Components::World& world, std::string _cScriptPath)
    {
        auto table = LuaTable::fromFile(_cScriptPath.c_str());
        auto hndl = TypeConverter::Convert<LuaTable, ThirdPersonCamera>(table);

        auto entity = world.CreateEntity(&world);
        world.Get(entity) = Entities::MASK_CAMERA_THIRDPERSON;

        Components::World::Add(world, entity, hndl);

        return entity;
    }

    void ThirdPersonCamera::Load(Components::World& world, uint64_t entity, uint64_t relatedEntity, CameraHandle* pCamHndl)
    {
        // < Fetch all placement components for the related entity.
        auto res = world.Fetch<Components::Placement>(&world, relatedEntity);
        if (res == nullptr) { return; }

        // < Get the base camera entity for our third-person camera.
        auto camera = Components::World::Get<Entities::ThirdPersonCamera>(world, entity);
        auto& comp = camera.placementComponents->front();

        // < Set the default position of the third-person camera using the first
        // * placement component, relative to our relatedEntity's world placement.
        comp.vRot = Leadwerks::Vec3(90.0f, 0.0f, 0.0f);
        comp.vPos = comp.vPos.Add(res->front().vPos);

        // < Load the camera inst of our third-person camera.
        Entities::Camera::Load(world, entity, pCamHndl);
    }

    void ThirdPersonCamera::Close(Components::World& world, uint64_t entity)
    {
        Entities::Camera::Close(world, entity);
    }

    void ThirdPersonCamera::Update(Components::World& world, uint64_t entity, float dt)
    {

        // < Perform game logic here.
        // < ---

        auto baseCam = Components::World::Get<Entities::Camera>(world, entity);
        auto& camHndl = baseCam.cameraHandles->front().pCamHndl;
        if (camHndl != nullptr)
        {
            auto cam = camHndl->getInst();

            auto camera = Components::World::Get<Entities::ThirdPersonCamera>(world, entity);
            auto res = world.Fetch<Components::Placement>(&world, camera.relationshipComponents->front().related);
            if (res == nullptr) { return; }

            auto vPos = res->front().vPos + camera.placementComponents->front().vPos;
            auto& relationship = camera.relationshipComponents->front();

            cam->SetPosition(vPos, true);
        }

        // < ---
    }

} // < end namespace.

template <> Entities::ThirdPersonCamera TypeConverter::Convert<LuaTable, Entities::ThirdPersonCamera>(LuaTable& source)
{
    Entities::ThirdPersonCamera hndl;

    static_cast<Entities::Camera&>(hndl) = TypeConverter::Convert<LuaTable, Entities::Camera>(source);

    // < Extract all required third-person camera information.
    auto vOff = source["offset"].get<Leadwerks::Vec3>();

    hndl.placement.vPos += vOff;

    return hndl;
}

template <>
void Components::World::Add<Entities::ThirdPersonCamera>(Components::World& world, uint64_t entity, Entities::ThirdPersonCamera& source)
{
    auto camera = world.Get<Entities::Camera>(world, entity);

    world.AddComponent(&world, entity, source.relationship);

    Components::World::Add<Entities::Camera>(world, entity, source);
}

template <>
Entities::ThirdPersonCamera Components::World::Get<Entities::ThirdPersonCamera>(Components::World& world, uint64_t entity)
{
    Entities::ThirdPersonCamera hndl;

    static_cast<Entities::Camera&>(hndl) = Components::World::Get<Entities::Camera>(world, entity);

    hndl.relationshipComponents = world.Fetch<Components::Relationship>(&world, entity);

    return hndl;
}
