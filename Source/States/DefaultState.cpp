#pragma once
#include "DefaultState.hpp"

#include "../Components/Component.hpp"
#include "../Systems/PlacementSystem.hpp"
#include "../Systems/PlayerSystem.hpp"
#include "../Utilities/StringExtensions.hpp"

#include <sqlite-persistence/DbConnection.hpp>

#include <memory>

using namespace Systems;

DefaultState::DefaultState(void) 
    : pModel(nullptr), placement(0, "-1-1-1") { }

void DefaultState::Configure(Container* pContainer)
{
    // < Here, we resolve some dependencies from the application container.
    m_pCameraHndl = pContainer->Resolve<CameraHandle>();
    m_pContextHndl = pContainer->Resolve<ContextHandle>();
    m_pInputMgr = pContainer->Resolve<InputManager>();
    m_pWorldHndl = pContainer->Resolve<WorldHandle>();
	m_pConnection = pContainer->Resolve<IDbConnection>();
}

void DefaultState::Load(void)
{
    // < Set the input manager to reset the mouse-position to the center of the
    // * screen every frame.
    //m_pInputMgr->ToggleMouseCenter();

	// < Move the camera back a little bit.
	m_pCameraHndl->getInst()->Move(0.0f, 3.0f, -10.0f, true);

    // < Add a light to our sample scene.
    m_pSceneLight = Leadwerks::DirectionalLight::Create();
    m_pSceneLight->SetRotation(35.0f, -35.0f, 0.0f);

    // < Create our component world.
    m_pWorld = new Components::World(m_pConnection, 0, "Primary");

    // < Initlaize the gameplay systems we will need for this state.
    if (PlacementSystem::Init() + PlayerSystem::Init() != 0)
    {
        std::cerr << "System initialization failed!";
        this->Close();
    }

    // < Test sqlite component system.
    m_player = m_pWorld->CreateEntity("player_one");

    // < Lets test CRUD operations on the base component.
    placement = Components::Placement(m_player, "Player Placement Component");
    placement = PlacementSystem::Save(m_player, placement);

    placement = PlacementSystem::AddSpin(m_player, Leadwerks::Vec3(0.0f, 0.0f, 0.25f));

    pModel = Leadwerks::Model::Box();
	pModel->SetPosition(placement.vTranslation, true);
}

void DefaultState::Close(void)
{
    // < Clean up our scene.
    SAFE_RELEASE(m_pSceneLight);
    SAFE_DELETE(m_pSceneLight);

    // < Shutdown the systems we initialized in Load.
    PlayerSystem::Shutdown();
    PlacementSystem::Shutdown();

	m_pWorld->DeleteEntity(m_player);
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

	placement = PlacementSystem::Update(m_player, dt, false);

	pModel->SetRotation(placement.vRotation);

    return true;
}

void DefaultState::Draw(void)
{
    auto ctx = this->m_pContextHndl->getInst();

    auto fps = std::string("FPS: {fps}");
    Replace("{fps}", std::to_string(Leadwerks::Time::GetSpeed()), fps);

    ctx->DrawText(fps, 10.0f, 10.0f);
}

void DefaultState::OnKeyDown(Event_KeyDown* pEvent)
{
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

}

void DefaultState::OnMouseMove(Event_MouseMove* pEvent)
{

}