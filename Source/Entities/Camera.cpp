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
		world.Get(entity) = Entities::MASK_CAMERA_FREE;

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

template <> Entities::Camera TypeConverter::Convert<LuaTable, Entities::Camera>(LuaTable& source)
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

template <> void Components::World::Add<Entities::Camera>(Components::World& world, uint64_t entity, Entities::Camera& source)
{    
    
    // < Create the components required to form an Actor.       
    world.AddComponent(&world, entity, source.cameraHandle);    
    world.AddComponent(&world, entity, source.placement);
    world.AddComponent(&world, entity, source.input);
    world.AddComponent(&world, entity, source.velocity);	
}

template <> Entities::Input<Entities::Camera> Components::World::Get<Entities::Input<Entities::Camera>>(Components::World& world, uint64_t entity)
{
	Entities::Input<Entities::Camera> hndl;

    std::vector<Components::MouseMoveTrigger<Entities::Camera>>* onMouseMoveTriggers;
    std::vector<Components::MouseHitTrigger<Entities::Camera>>* onMouseHitTriggers;
    std::vector<Components::MouseDownTrigger<Entities::Camera>>* onMouseDownTriggers;
    std::vector<Components::MouseUpTrigger<Entities::Camera>>* onMouseUpTriggers;
    std::vector<Components::KeyHitTrigger<Entities::Camera>>* onKeyHitTriggers;
    std::vector<Components::KeyDownTrigger<Entities::Camera>>* onKeyDownTriggers;
    std::vector<Components::KeyUpTrigger<Entities::Camera>>* onKeyUpTriggers;

    // < Here we attempt to populate our object graph for camera inputs. The current
    // * implementation forces the world to throw an exception should a component
    // * not exist within the world's component map. Here, simply set the collection
    // * to a nullptr because we may not always want to register events for each
    // * possible event. 
    // * NOTE: need to find a better way to handle object graph population.
    try
    {
        onMouseMoveTriggers = world.GetComponents<Components::MouseMoveTrigger<Entities::Camera>>(&world, entity);
    }
    catch (std::exception& ex)
    {
        onMouseMoveTriggers = nullptr;
    }

    try
    {
        onMouseHitTriggers = world.GetComponents<Components::MouseHitTrigger<Entities::Camera>>(&world, entity);
    }
    catch (std::exception& ex)
    {
        onMouseHitTriggers = nullptr;
    }

    try 
    {
        onMouseDownTriggers = world.GetComponents<Components::MouseDownTrigger<Entities::Camera>>(&world, entity);
    }
    catch (std::exception& ex)
    {
        onMouseDownTriggers = nullptr;
    }

    try
    {
        onMouseUpTriggers = world.GetComponents<Components::MouseUpTrigger<Entities::Camera>>(&world, entity);
    }
    catch (std::exception& ex)
    {
        onMouseUpTriggers = nullptr;
    }

    try
    {
        onKeyHitTriggers = world.GetComponents<Components::KeyHitTrigger<Entities::Camera>>(&world, entity);
    }
    catch (std::exception& ex)
    {
        onKeyHitTriggers = nullptr;
    }

    try
    {
        onKeyDownTriggers = world.GetComponents<Components::KeyDownTrigger<Entities::Camera>>(&world, entity);
    }
    catch (std::exception& ex)
    {
        onKeyDownTriggers = nullptr;
    }

    try
    {
        onKeyUpTriggers = world.GetComponents<Components::KeyUpTrigger<Entities::Camera>>(&world, entity);
    }
    catch (std::exception& ex)
    {
        onKeyUpTriggers = nullptr;
    }

	hndl.mouseMoveTriggers = onMouseMoveTriggers;
	hndl.mouseHitTriggers = onMouseHitTriggers;
	hndl.mouseDownTriggers = onMouseDownTriggers;
	hndl.mouseUpTriggers = onMouseUpTriggers;

	hndl.keyHitTriggers = onKeyHitTriggers;
	hndl.keyDownTriggers = onKeyDownTriggers;
	hndl.keyUpTriggers = onKeyUpTriggers;

	return hndl;
}

template <> Entities::Camera Components::World::Get<Entities::Camera>(Components::World& world, uint64_t entity)
{    
    Entities::Camera hndl;
    
	static_cast<Entities::Input<Entities::Camera>&>(hndl) = Components::World::Get<Entities::Input<Entities::Camera>>(world, entity);

    auto cameraComponents = world.GetComponents<Components::Camera>(&world, entity);
    auto inputComponents = world.GetComponents<Components::Input<Entities::Camera>>(&world, entity);
    auto placementComponents = world.GetComponents<Components::Placement>(&world, entity);
    auto velocityComponents = world.GetComponents<Components::Velocity>(&world, entity);
    
    hndl.inputComponents = inputComponents;
    hndl.placementComponents = placementComponents;
    hndl.velocityComponents = velocityComponents;
    hndl.cameraHandles = cameraComponents;	

    hndl.component = Components::Component(inputComponents->front().cName);
    hndl.component.nId = entity;

    return hndl;
}

template <> std::vector<Entities::Camera> Components::World::GetAll<Entities::Camera>(Components::World& world)
{    
    std::vector<Entities::Camera> results;

    auto& entities = world.GetEntities(&world, Entities::MASK_CAMERA_FREE);

    auto iter = entities.begin();
    while (iter != entities.end())
    {
        results.push_back(Components::World::Get<Entities::Camera>(world, (*iter)));
        iter++;
    }

    return results;
}