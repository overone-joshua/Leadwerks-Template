#pragma once
#include "DefaultState.hpp"

DefaultState::DefaultState(void) { }

Leadwerks::Model* pModel;

void DefaultState::Configure(Container* pContainer)
{
    // < Here, we resolve some dependencies from the application container.
    m_pCameraHndl = pContainer->Resolve<CameraHandle>();
    m_pInputMgr = pContainer->Resolve<InputManager>();
    m_pWorldHndl = pContainer->Resolve<WorldHandle>();
}

void DefaultState::Load(void)
{
    // < Set the input manager to reset the mouse-position to the center of the
    // * screen every frame.
    //m_pInputMgr->ToggleMouseCenter();

    // < Add a light to our sample scene.
    m_pSceneLight = Leadwerks::DirectionalLight::Create();
    m_pSceneLight->SetRotation(35.0f, -35.0f, 0.0f);

    // < Create our component world.
    m_pWorld = new Components::World();

    // < Create our components.
    m_player = Entities::Player::Create(*m_pWorld, "./Scripts/Player.lua");
    m_camera = Entities::ThirdPersonCamera::Create(*m_pWorld, "./Scripts/DefaultThirdPersonCamera.lua");

    pModel = Leadwerks::Model::Box();

    // < Load all components.
    Entities::Actor::Load(*m_pWorld, m_player);
    Entities::ThirdPersonCamera::Load(*m_pWorld, m_camera, m_player, m_pCameraHndl);
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

    SAFE_RELEASE(pModel);
    SAFE_DELETE(pModel);

    // < Set the input manager to allow the mouse pointer to freely
    // * move about the window.
    //m_pInputMgr->ToggleMouseCenter();
}

bool DefaultState::Update(float dt)
{
    auto world = m_pWorldHndl->getInst();
    // < Update our entities.
    Entities::Bullet::UpdateAll(*m_pWorld, world, dt);
    Entities::Player::Update(*m_pWorld, m_player, dt);
    Entities::ThirdPersonCamera::Update(*m_pWorld, m_camera, dt);

    return true;
}

void DefaultState::OnKeyDown(Event_KeyDown* pEvent)
{
    // < Propogate our key-down event to our entities.
    Entities::Actor::TriggerKeyDown(*m_pWorld, m_player, pEvent);
    Entities::Camera::TriggerKeyDown(*m_pWorld, m_camera, pEvent);
}

void DefaultState::OnKeyUp(Event_KeyUp* pEvent)
{
#ifdef DEBUG
    // < Reload the state.
    if (pEvent->Key() == Leadwerks::Key::R)
    {
        this->Close();
        this->Load();
    }
#endif

    // < propogate our key-up events to our entities.
    Entities::Actor::TriggerKeyUp(*m_pWorld, m_player, pEvent);
    Entities::Camera::TriggerKeyUp(*m_pWorld, m_camera, pEvent);
}

void DefaultState::OnMouseMove(Event_MouseMove* pEvent)
{
    // < Propogate our mouse-move event to our entities.
    Entities::Actor::TriggerMouseMove(*m_pWorld, m_player, pEvent);
    Entities::Camera::TriggerMouseMove(*m_pWorld, m_camera, pEvent);
}