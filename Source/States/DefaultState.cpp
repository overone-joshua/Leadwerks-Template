#pragma once
#include "DefaultState.hpp"

DefaultState::DefaultState(void) { }

void DefaultState::Configure(Container* pContainer)
{
    // < Here, we resolve some dependencies from the application container.
    m_pCameraHndl = pContainer->Resolve<CameraHandle>();
    m_pInputMgr = pContainer->Resolve<InputManager>();
}

void DefaultState::Load(void)
{
    // < Set the input manager to reset the mouse-position to the center of the
    // * screen every frame.
    m_pInputMgr->ToggleMouseCenter();

    // < Add a light to our sample scene.
    m_pSceneLight = Leadwerks::DirectionalLight::Create();
    m_pSceneLight->SetRotation(35.0f, -35.0f, 0.0f);    

    // < Create our component world.
    m_pWorld = new Components::World();

    // < Create our components.
    m_player = Entities::Actor::Create(*m_pWorld, "./Scripts/Player.lua");
    m_camera = Entities::SpectatorCamera::Create(*m_pWorld, "./Scripts/DefaultCamera.lua");
	
    // < Load all components.
    Entities::Actor::Load(*m_pWorld, m_player);
    Entities::Camera::Load(*m_pWorld, m_camera, m_pCameraHndl);               
}

void DefaultState::Close(void)
{
    // < Destroy all components loaded previously in load.
    Entities::Camera::Close(*m_pWorld, m_camera);
    Entities::Actor::Close(*m_pWorld, m_player);    

    // < Clean up our scene.
    SAFE_RELEASE(m_pSceneLight);

    SAFE_DELETE(m_pSceneLight);
    SAFE_DELETE(m_pWorld);

    m_pCameraHndl = nullptr;
    m_pInputMgr = nullptr;    

    // < Set the input manager to allow the mouse pointer to freely
    // * move about the window.
    m_pInputMgr->ToggleMouseCenter();
}

bool DefaultState::Update(float dt)
{
    // < Update our entities.
    Entities::Actor::Update(m_pInputMgr, *m_pWorld, m_player, dt);
    Entities::SpectatorCamera::Update(*m_pWorld, m_camera, dt);

    return true;
}

void DefaultState::OnKeyDown(Event_KeyDown* pEvent)
{    
    // < Propogate our key-down event to our entities.    
	Entities::Input<Entities::Camera>::OnKeyDown(*m_pWorld, m_camera, pEvent);    
}

void DefaultState::OnKeyUp(Event_KeyUp* pEvent)
{        
    // < propogate our key-up events to our entities.     
	Entities::Input<Entities::Camera>::OnKeyUp(*m_pWorld, m_camera, pEvent);
}

void DefaultState::OnMouseMove(Event_MouseMove* pEvent)
{
    // < Propogate our mouse-move event to our entities.   
	Entities::Input<Entities::Camera>::OnMouseMove(*m_pWorld, m_camera, pEvent);
}