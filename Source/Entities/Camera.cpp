#pragma once 
#include "Camera.hpp"

namespace Entities
{
    Camera::Camera(void)
        : inputComponents(nullptr), placementComponents(nullptr), velocityComponents(nullptr)
        , cameraHandles(nullptr) { }

    uint64_t Camera::Create(Components::World& world, std::string cScriptPath)
    {        
        auto table = LuaTable::fromFile(cScriptPath.c_str());
        auto hndl = TypeConverter::Convert<LuaTable, Camera>(table);                

		auto entity = world.CreateEntity(&world);
		world.Get(entity) = Entities::MASK_CAMERA;

        Components::World::Add(world, entity, hndl);
        
		return entity;
    }

    void Camera::Load(Components::World& world, uint64_t entity, CameraHandle* pCamHndl)
    {
        auto res = Components::World::Get<Camera>(world, entity);
        auto& cameraHandles = res.cameraHandles;
        auto& camera = cameraHandles->front();
        
        camera.pCamHndl = pCamHndl;
    }

    void Camera::Close(Components::World& world, uint64_t entity)
    {
        auto res = Components::World::Get<Camera>(world, entity);
        auto& cameraHandles = res.cameraHandles;
        auto& camera = cameraHandles->front();

        camera.pCamHndl = nullptr;
    }     

} // < end namespace.

template <> 
Entities::Camera TypeConverter::Convert<LuaTable, Entities::Camera>(LuaTable& source)
{
    Entities::Camera hndl;

    // < Extract all required actor information.
    auto name = source["name"].get<std::string>();
    auto vPos = source["pos"].get<Leadwerks::Vec3>();
    auto vRot = source["rot"].get<Leadwerks::Vec3>();
    auto vSca = source["sca"].get<Leadwerks::Vec3>();
    auto vMovSpeed = source["movSpeed"].get<Leadwerks::Vec3>();
    auto vRotSpeed = source["rotSpeed"].get<Leadwerks::Vec3>();
    auto vVel = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);

    hndl.component = Components::Component(name);    
    hndl.cameraHandle = Components::Camera(nullptr, name);
    hndl.input = Components::Input<Entities::Camera>(vMovSpeed, vRotSpeed, name);
    hndl.placement = Components::Placement(vPos, vRot, vSca, name);
    hndl.velocity = Components::Velocity(vVel, name);

    return hndl;
}

template <> 
void Components::World::Add<Entities::Camera>(Components::World& world, uint64_t entity, Entities::Camera& source)
{        
    // < Create the components required to form an Actor.       
    world.AddComponent(&world, entity, source.cameraHandle);    
    world.AddComponent(&world, entity, source.placement);
    world.AddComponent(&world, entity, source.input);
    world.AddComponent(&world, entity, source.velocity);	
}

template <> 
Entities::Input<Entities::Camera> Components::World::Get<Entities::Input<Entities::Camera>>(Components::World& world, uint64_t entity)
{
	Entities::Input<Entities::Camera> hndl;

    hndl.mouseMoveTriggers = world.Fetch<Components::MouseMoveTrigger<Entities::Camera>>(&world, entity);
    hndl.mouseHitTriggers = world.Fetch<Components::MouseHitTrigger<Entities::Camera>>(&world, entity);
    hndl.mouseDownTriggers = world.Fetch<Components::MouseDownTrigger<Entities::Camera>>(&world, entity);
    hndl.mouseUpTriggers = world.Fetch<Components::MouseUpTrigger<Entities::Camera>>(&world, entity);
    hndl.keyHitTriggers = world.Fetch<Components::KeyHitTrigger<Entities::Camera>>(&world, entity);
    hndl.keyDownTriggers = world.Fetch<Components::KeyDownTrigger<Entities::Camera>>(&world, entity);
    hndl.keyUpTriggers = world.Fetch<Components::KeyUpTrigger<Entities::Camera>>(&world, entity);

	return hndl;
}

template <> 
Entities::Camera Components::World::Get<Entities::Camera>(Components::World& world, uint64_t entity)
{    
    Entities::Camera hndl;
    
	static_cast<Entities::Input<Entities::Camera>&>(hndl) = Components::World::Get<Entities::Input<Entities::Camera>>(world, entity);
    
	hndl.inputComponents = world.GetComponents<Components::Input<Entities::Camera>>(&world, entity);
	hndl.placementComponents = world.GetComponents<Components::Placement>(&world, entity);
	hndl.velocityComponents = world.GetComponents<Components::Velocity>(&world, entity);
	hndl.cameraHandles = world.GetComponents<Components::Camera>(&world, entity);

    hndl.component = Components::Component(hndl.inputComponents->front().cName);
    hndl.component.nId = entity;

    return hndl;
}

template <> 
std::vector<Entities::Camera> Components::World::GetAll<Entities::Camera>(Components::World& world)
{    
    std::vector<Entities::Camera> results;

    auto entities = world.GetEntities(&world, Entities::MASK_CAMERA);

    auto iter = entities.begin();
    while (iter != entities.end())
    {
        results.push_back(Components::World::Get<Entities::Camera>(world, (*iter)));
        ++iter;
    }

    return results;
}