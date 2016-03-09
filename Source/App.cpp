#pragma once
#include "Leadwerks.h"
#include "App.h"

#include "Common.hpp"
#include "Utilities/Macros.hpp"

#include "Utilities/Container.hpp"

#include "Utilities/WindowHandle.hpp"
#include "Utilities/ContextHandle.hpp"
#include "Utilities/WorldHandle.hpp"
#include "Utilities/CameraHandle.hpp"

#include "Managers/EventManager.hpp"
#include "Managers/InputManager.hpp"
#include "Managers/StateManager.hpp"

#include "Components/Components.hpp"
#include "Entities/Entities.hpp"
#include "States/DefaultState.hpp"

App::App(void) : m_pEventManager(nullptr), m_pInputManager(nullptr) { }

App::~App(void) { }

void App::Configure(Container* pContainer) {

	/* EventManager */
	m_pEventManager = pContainer->Register<EventManager, EventManager>( new EventManager());

	/* StateManager */
	m_pStateManager = pContainer->Register<StateManager, StateManager>(new StateManager(
		pContainer,
		pContainer->Resolve<EventManager>()));

	/* Input Manager */
	m_pInputManager = pContainer->Register<InputManager, InputManager>( new InputManager(
		pContainer->Resolve<WindowHandle>()->getInst(), 
		pContainer->Resolve<ContextHandle>()->getInst(),
		pContainer->Resolve<EventManager>()));

	// < Register any states that are going to be used by our application.
	// * In order for a state to be added through the StateManager,
	// * the state MUST be registered with the StateFactory first.
	gStateFactory.Register(new FactoryMaker<DefaultState, State>);	

	Components::Bind();
    Entities::Bind();
}

bool App::Start(void) {

	// < Add our default state and immediately make it active.
	m_pStateManager->AddState<DefaultState>(true);

	std::cout << "Application initialization completed successfully. \n";
	
	return true;

}

void App::Shutdown(void) 
{
	Dispose(); 

}

void App::Dispose(void) 
{
	m_pEventManager = nullptr;
	m_pInputManager = nullptr;
	m_pStateManager = nullptr;

	// < Unregister any states that were registered during this
	// * applications configure method. Order doesnt really
	// * matter here.
	gStateFactory.Unregister(DefaultState::ClassType());

}

void App::preUpdate(void) 
{ 
	// < Call the StateManager's preUpdate.
	if (m_pStateManager != nullptr) { m_pStateManager->preUpdate(); }

}

bool App::Update(float dt) 
{ 
	// < Call EventManager's update. We allow it to process events 
	// * for 200ms a frame.
	if (m_pEventManager != nullptr) { m_pEventManager->Update(200); }
	
	// < Call the InputManager's update.
	if (m_pInputManager != nullptr) { m_pInputManager->Update(dt); } 

	// < Call the StateManager's Update.
	if (m_pStateManager != nullptr) { m_pStateManager->Update(dt); }	

	return true; 

}

void App::postUpdate(void) 
{ 
	// < Call the InputManager's postUpdate.
	if (m_pStateManager != nullptr) { m_pStateManager->postUpdate(); }	

}

void App::preRender(void) 
{
	// < Call the StateManager's preRender.
	if (m_pStateManager != nullptr) { m_pStateManager->preRender(); } 

}

void App::Render(void)
{
	// < Perform all 3D-Rendering here.
	// < ---

	// < Call the StateManager's Render.
	if (m_pStateManager != nullptr) { m_pStateManager->Render(); }	

	// < ---

}

void App::postRender(void) 
{
	// < Call the StateManager's postRender.
	if (m_pStateManager != nullptr) { m_pStateManager->postRender(); }

}

void App::preDraw(void) 
{
	// < Call the StateManager's preDraw.
	if (m_pStateManager != nullptr) { m_pStateManager->preDraw(); }
	
}

void App::Draw(void) 
{
	// < Perform all 2D-Rendering here.
	// < ---

	// < Call the StateManager's Draw.
	if (m_pStateManager != nullptr) { m_pStateManager->Draw(); }	

	// < ---

}

void App::postDraw(void) 
{
	// < Call the StateManager's postDraw.
	if (m_pStateManager != nullptr) { m_pStateManager->postDraw(); }	

}