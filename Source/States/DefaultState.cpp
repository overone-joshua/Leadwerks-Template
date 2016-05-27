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
	m_pDatabaseController = pContainer->Resolve<IDatabaseController>();
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
    m_pWorld = new Components::World(m_pDatabaseController);

    // < Test sqlite component system.
    m_player = m_pWorld->CreateEntity("player_one");

    auto component = Components::Component("player_one_component");

    component = m_pWorld->AddComponent<Components::Component>(m_player, component);

    component.cName = "player_one_component_with_namechange";
    m_pWorld->UpdateComponent(m_player, component);

    auto where = std::vector<WhereClause>(1, std::make_tuple("Id", "=", std::to_string(component.nId)));
    component = m_pWorld->FetchComponents<Components::Component>(m_player, where, true).front();

    m_pWorld->DeleteComponent<Components::Component>(m_player, where);
}

void DefaultState::Close(void)
{
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