#pragma once
#include "DefaultState.hpp"

#include "../Components/Component.hpp"
#include "../Repositories/AppearanceRepository.hpp"
#include "../Repositories/ComponentRepository.hpp"
#include "../Repositories/PlacementRepository.hpp"
#include "../Systems/PlacementSystem.hpp"

#include <sqlite-persistence/DbConnection.hpp>

#include <memory>

DefaultState::DefaultState(void) { }

Leadwerks::Model* pModel;
Components::Placement placement;

void DefaultState::Configure(Container* pContainer)
{
    // < Here, we resolve some dependencies from the application container.
    m_pCameraHndl = pContainer->Resolve<CameraHandle>();
    m_pInputMgr = pContainer->Resolve<InputManager>();
    m_pWorldHndl = pContainer->Resolve<WorldHandle>();
	m_pConnection = pContainer->Resolve<IDbConnection>();
    m_pAppearanceRepository = pContainer->Resolve<AppearanceRepository>();
    m_pComponentRepository = pContainer->Resolve<ComponentRepository>();
    m_pPlacementRepository = pContainer->Resolve<PlacementRepository>();
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

    // < Test sqlite component system.
    m_player = m_pWorld->CreateEntity("player_one");

    // < Lets test CRUD operations on the base component.
    placement = Components::Placement(m_player, "Player Placement Component");
    placement = m_pPlacementRepository->Save(placement);

    placement.cName = "Player Placement component with updated name";
    placement = m_pPlacementRepository->Save(placement);

    pModel = Leadwerks::Model::Box();
	pModel->SetPosition(placement.vTranslation, true);
}

void DefaultState::Close(void)
{
    // < Clean up our scene.
    SAFE_RELEASE(m_pSceneLight);
    SAFE_DELETE(m_pSceneLight);

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

	Systems::PlacementSystem::AddSpin(this->m_pPlacementRepository, m_player, Leadwerks::Vec3(0.2f, 0.0f, 0.0f));
	Systems::PlacementSystem::Update(this->m_pPlacementRepository, m_player, dt, false);

    placement = this->m_pPlacementRepository->FindById(placement.nId);

	pModel->SetRotation(placement.vRotation);

    return true;
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