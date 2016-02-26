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

#include "States/DefaultState.hpp"

App::App(void) 
	: m_pEventManager(nullptr), m_pInputManager(nullptr) { }

App::~App(void) { }

void App::Configure(Container* pContainer) {

	/* StateManager */
	m_pStateManager = pContainer->Register<StateManager, StateManager>( new StateManager(pContainer));

	/* EventManager */
	m_pEventManager = pContainer->Register<EventManager, EventManager>( new EventManager());

	/* Input Manager */
	m_pInputManager = pContainer->Register<InputManager, InputManager>( new InputManager(
		pContainer->Resolve<WindowHandle>()->getInst(), 
		pContainer->Resolve<ContextHandle>()->getInst(),
		pContainer->Resolve<EventManager>()));

	gStateFactory.Register(new FactoryMaker<DefaultState, State>);
}

bool App::Start(void) {

	// < Add our default state and immediately make it active.
	m_pStateManager->AddState<DefaultState>(true);

	std::cout << "Application initialization completed successfully. \n";
	
	return true;
}

void App::Shutdown(void) { Dispose(); }

void App::Dispose(void) 
{
	gStateFactory.Unregister(DefaultState::ClassType());
}

void App::preUpdate(void) 
{ 
	// < Call the StateManager's preUpdate.
	m_pStateManager->preUpdate();

}

bool App::Update(float dt) 
{ 
	// < Call EventManager's update. We allow it to process events 
	// * for 200ms a frame.
	m_pEventManager->Update(200);
	
	// < Call the InputManager's update.
	m_pInputManager->Update(dt);

	// < Call the StateManager's Update.
	m_pStateManager->Update(dt);

	return true; 

}

void App::postUpdate(void) 
{ 
	// < Call the InputManager's postUpdate.
	m_pStateManager->postUpdate();

}

void App::preRender(void) 
{
	// < Call the StateManager's preRender.
	m_pStateManager->preRender();

}

void App::Render(void)
{
	// < Perform all 3D-Rendering here.
	// < ---

	// < Call the StateManager's Render.
	m_pStateManager->Render();

	// < ---

}

void App::postRender(void) 
{
	// < Call the StateManager's postRender.
	m_pStateManager->postRender();

}

void App::preDraw(void) 
{
	// < Call the StateManager's preDraw.
	m_pStateManager->preDraw();

}

void App::Draw(void) 
{
	// < Perform all 2D-Rendering here.
	// < ---

	// < Call the StateManager's Draw.
	m_pStateManager->Draw();

	// < ---

}

void App::postDraw(void) 
{
	// < Call the StateManager's postDraw.
	m_pStateManager->postDraw();

}