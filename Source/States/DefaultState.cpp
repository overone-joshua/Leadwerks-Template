#pragma once
#include "DefaultState.hpp"

#include "../Components/Component.hpp"
#include "../Components/Level.hpp"
#include "../Components/LevelEditor.hpp"
#include "../Components/Placement.hpp"
#include "../Components/Player.hpp"
#include "../Components/World.hpp"

#include "../Systems/LevelSystem.hpp"
#include "../Systems/LevelEditorSystem.hpp"
#include "../Systems/PlacementSystem.hpp"
#include "../Systems/PlayerSystem.hpp"

#include "../Utilities/StringExtensions.hpp"

#include <sqlite-persistence/DbConnection.hpp>

#include <memory>

using namespace Systems;

DefaultState::DefaultState(void) 
    : pModel(nullptr), m_pLevel(nullptr), m_pCamera(nullptr)
    , m_pPlayerEditor(nullptr) { }

void DefaultState::Configure(Container* pContainer)
{
    // < Here, we resolve some dependencies from the application container.
    m_pCameraHndl = pContainer->Resolve<CameraHandle>();
    m_pContextHndl = pContainer->Resolve<ContextHandle>();
    m_pInputMgr = pContainer->Resolve<InputManager>();
    m_pWorldHndl = pContainer->Resolve<WorldHandle>();
	m_pConnection = pContainer->Resolve<IDbConnection>();
}

/// <summary>
/// Loads this instance.
/// </summary>
void DefaultState::Load(void)
{
    // < Initlaize the gameplay systems we will need for this state.
    if (LevelSystem::Init() + LevelEditorSystem::Init() +
        PlacementSystem::Init() + PlayerSystem::Init() != 0)
    {
        std::cerr << "System initialization failed!";
        this->Close();
        return;
    }

    // < Set the input manager to reset the mouse-position to the center of the
    // * screen every frame.
    m_pInputMgr->ToggleMouseCenter();

	// < Move the camera back a little bit.
	m_pCameraHndl->getInst()->Move(0.0f, 5.0f, -5.0f, true);

    // < Add a light to our sample scene.
    m_pSceneLight = Leadwerks::DirectionalLight::Create();
    m_pSceneLight->SetRotation(35.0f, -35.0f, 0.0f);

    pModel = Leadwerks::Model::Box();
    pModel->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	pModel->SetPosition(-3.0f, 0.0f, 0.0f, true);    // < Spatial ref box.

    // < Create our component world.
    m_pWorld = new Components::World(m_pConnection, 0, "Primary");
    m_level = m_pWorld->CreateEntity("Primary_Level");
    m_levelEditor = m_pWorld->CreateEntity("Level_Editor");
    m_camera = m_pWorld->CreateEntity("Editor_Camera");

    // < Create our level.
    m_pLevel = LevelSystem::Create(m_level, "Level_One", 2, 2, 2, 1.0f);

    auto config = EditorConfig(m_pInputMgr, m_pCameraHndl->getInst(), m_pWorldHndl->getInst(), m_pLevel, m_levelEditor, "Level_Editor");
    m_pLevelEditor = LevelEditorSystem::Create(config, m_levelEditor, "Level_One_Editor");

    m_pCamera = PlacementSystem::Create(m_camera, "Editor_Camera_Placement");
    *m_pCamera = PlacementSystem::Save(m_camera, *m_pCamera);

    m_pPlayerEditor = PlayerSystem::Create(m_camera, "Editor_Camera_Player");
}

void DefaultState::Close(void)
{
    // < Clean up our scene.
    SAFE_RELEASE(m_pSceneLight);
    SAFE_DELETE(m_pSceneLight);

    PlayerSystem::Destroy(m_pPlayerEditor);
    PlacementSystem::Destroy(m_pCamera);
    LevelSystem::Destroy(m_pLevel);
    LevelEditorSystem::Destroy(m_pLevelEditor);

    m_pWorld->DeleteEntity(m_camera);
    m_pWorld->DeleteEntity(m_levelEditor);
    m_pWorld->DeleteEntity(m_level);
    SAFE_DELETE(m_pWorld);

    SAFE_RELEASE(pModel);
    SAFE_DELETE(pModel);

    // < Set the input manager to allow the mouse pointer to freely
    // * move about the window.
    m_pInputMgr->ToggleMouseCenter();

    // < Shutdown the systems we initialized in Load.
    PlayerSystem::Shutdown();
    PlacementSystem::Shutdown();
    LevelEditorSystem::Shutdown();
    LevelSystem::Shutdown();
}

bool DefaultState::Update(float dt)
{
    auto camera = m_pCameraHndl->getInst();
    auto world = m_pWorldHndl->getInst();

    *m_pCamera = PlacementSystem::Update(*m_pCamera, dt, true);
    //*m_pCamera = PlacementSystem::Save(m_camera, *m_pCamera);

    *m_pPlayerEditor = PlayerSystem::Update(*m_pPlayerEditor, *m_pCamera, dt, true);
    *m_pPlayerEditor = PlayerSystem::MouseLook(*m_pPlayerEditor, *m_pCamera, m_pInputMgr->GetMousePosition().x, m_pInputMgr->GetMousePosition().y);

    camera->SetRotation(m_pCamera->vRotation);
    camera->SetPosition(m_pCamera->vTranslation, true);

    LevelSystem::Update(m_pLevel, dt);
    LevelEditorSystem::Update(m_pLevelEditor, dt);

    return true;
}

void DefaultState::Draw(void)
{
    std::string pos = "Position: {pos}";
    Replace("{pos}", m_pCameraHndl->getInst()->GetPosition(true).ToString(), pos);

    m_pContextHndl->getInst()->DrawText(pos, 10, 10);
}

void DefaultState::OnKeyDown(Event_KeyDown* pEvent)
{
    if (pEvent->Key() == Leadwerks::Key::W) { m_pCamera->nInputMask.AddStatus(INPUT_MOVE_FORWARD); }
    if (pEvent->Key() == Leadwerks::Key::A) { m_pCamera->nInputMask.AddStatus(INPUT_MOVE_LEFT); }
    if (pEvent->Key() == Leadwerks::Key::S) { m_pCamera->nInputMask.AddStatus(INPUT_MOVE_BACKWARD); }
    if (pEvent->Key() == Leadwerks::Key::D) { m_pCamera->nInputMask.AddStatus(INPUT_MOVE_RIGHT); }
    if (pEvent->Key() == Leadwerks::Key::Q) { m_pCamera->nInputMask.AddStatus(INPUT_MOVE_DOWN); }
    if (pEvent->Key() == Leadwerks::Key::E) { m_pCamera->nInputMask.AddStatus(INPUT_MOVE_UP); }
    auto pCamera = m_pCameraHndl->getInst();
    *m_pCamera = PlacementSystem::Save(m_camera, *m_pCamera);
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

   if (pEvent->Key() == Leadwerks::Key::W) { m_pCamera->nInputMask.RemoveStatus(INPUT_MOVE_FORWARD); }
    if (pEvent->Key() == Leadwerks::Key::A) { m_pCamera->nInputMask.RemoveStatus(INPUT_MOVE_LEFT); }
    if (pEvent->Key() == Leadwerks::Key::S) { m_pCamera->nInputMask.RemoveStatus(INPUT_MOVE_BACKWARD); }
    if (pEvent->Key() == Leadwerks::Key::D) { m_pCamera->nInputMask.RemoveStatus(INPUT_MOVE_RIGHT); }
    if (pEvent->Key() == Leadwerks::Key::Q) { m_pCamera->nInputMask.RemoveStatus(INPUT_MOVE_DOWN); }
    if (pEvent->Key() == Leadwerks::Key::E) { m_pCamera->nInputMask.RemoveStatus(INPUT_MOVE_UP); }

    *m_pCamera = PlacementSystem::Save(m_camera, *m_pCamera);
}

void DefaultState::OnMouseHit(Event_MouseHit* pEvent)
{
    if (pEvent->MouseButton() == 1) { m_pLevelEditor->inputMask.AddStatus(EDITOR_ACTION_ADD_VOXEL); }
    if (pEvent->MouseButton() == 2) { m_pLevelEditor->inputMask.AddStatus(EDITOR_ACTION_REMOVE_VOXEL); }
}

void DefaultState::OnMouseUp(Event_MouseUp* pEvent)
{
    if (pEvent->MouseButton() == 1) { m_pLevelEditor->inputMask.RemoveStatus(EDITOR_ACTION_ADD_VOXEL); }
    if (pEvent->MouseButton() == 2) { m_pLevelEditor->inputMask.RemoveStatus(EDITOR_ACTION_REMOVE_VOXEL); }
}

void DefaultState::OnMouseMove(Event_MouseMove* pEvent)
{
    
}