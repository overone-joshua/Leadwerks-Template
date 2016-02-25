#pragma once
#include "Leadwerks.h"
#include "App.h"

#include "Common.hpp"
#include "Utilities/Macros.hpp"

#include "Utilities/WindowHandle.hpp"
#include "Utilities/ContextHandle.hpp"
#include "Utilities/Container.hpp"
#include "Managers/EventManager.hpp"
#include "Managers/InputManager.hpp"

App::App(void) 
	: m_pEventManager(nullptr), m_pInputManager(nullptr) { }

App::~App(void) { }

void App::Configure(Container* pContainer) {

	m_pEventManager = pContainer->Register<EventManager, EventManager>( new EventManager());

	m_pInputManager = pContainer->Register<InputManager, InputManager>( new InputManager(
		pContainer->Resolve<WindowHandle>()->getInst(), 
		pContainer->Resolve<ContextHandle>()->getInst(),
		pContainer->Resolve<EventManager>()));

}

bool App::Start(void) {

	std::cout << "Application initialization completed successfully. \n";
	
	return true;
}

void App::Shutdown(void) { }

void App::preUpdate(void) { }

bool App::Update(float dt) { return true; }

void App::postUpdate(void) { }

void App::preRender(void) { }

void App::Render(void) { }

void App::postRender(void) { }

void App::preDraw(void) { }

void App::Draw(void) { }

void App::postDraw(void) { }