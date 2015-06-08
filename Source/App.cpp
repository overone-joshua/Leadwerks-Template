#pragma once
#include "App.h"
#include "Leadwerks.h"
#include "Helpers\Event.hpp"
#include "Managers\EventManager.hpp"
#include "Managers\StateManager.hpp"
#include "Managers\InputManager.hpp"
#include "Managers\CameraManager.hpp"
#include "States\Game.hpp"
#include "Objects\GameObject.hpp"
#include <iostream>

/* Externals From App.h */
App* gApp;
EventManager* gEventMgr;
StateManager* gStateMgr;
InputManager* gInputMgr;
CameraManager* gCameraMgr;

// -----

std::string App::Name() {
	return this->m_name;
}

unsigned App::ScreenWidth() {
	return this->m_nScreenWidth;
}

unsigned App::ScreenHeight() {
	return m_nScreenHeight;
}

bool App::Fullscreen() {
	return this->m_bFullscreen;
}

bool App::Paused() {
	return this->m_bPaused;
}

void App::setName(std::string name) {
	this->m_name = name;
}

void App::setScreenWidth(unsigned width) {
	this->m_nScreenWidth = width;
}

void App::setScreenHeight(unsigned height) {
	this->m_nScreenHeight = height;
}

void App::ToggleFullscreen() {
	this->m_bFullscreen = !this->m_bFullscreen;
}

void App::Pause() {
	this->m_bPaused = true;
}

void App::UnPause() {
	this->m_bPaused = false;
}

Leadwerks::Window& App::GetWindow() {
	return *this->m_pWindow;
}

Leadwerks::Context& App::GetContext() {
	return *this->m_pContext;
}

Leadwerks::World& App::GetWorld() {
	return *this->m_pWorld;
}

Leadwerks::Camera& App::GetCamera() {
	return *this->m_pCamera;
}

int App::CreateWindow(const int flags) {
	if (this->m_pWindow != nullptr) { this->m_pWindow->Release(); }
	this->m_pWindow = Leadwerks::Window::Create(this->m_name, 0, 0, this->m_nScreenWidth, this->m_nScreenHeight, flags);
	if (this->m_pWindow == nullptr) { std::cout << "Window creation was unsuccessful. \n"; return WINDOW_CREATION_ERROR; }
	return 0;
}

int App::CreateContext(const int flags) {
	if (this->m_pContext != nullptr) { this->m_pContext->Release(); }
	this->m_pContext = Leadwerks::Context::Create(this->m_pWindow, flags);
	if (this->m_pContext == nullptr) { std::cout << "Context creation was unsuccessful. \n"; return CONTEXT_CREATION_ERROR; }
	return 0;
}

int App::CreateWorld() {
	if (this->m_pWorld != nullptr) { this->m_pWorld->Release(); }
	this->m_pWorld = Leadwerks::World::Create();
	if (this->m_pWorld == nullptr) { std::cout << "World creation was unsuccessful. \n"; return WORLD_CREATION_ERROR; }
	return 0;
}

int App::CreateCamera(Leadwerks::Entity* pParent) {
	if (this->m_pCamera != nullptr) { this->m_pCamera->Release(); }
	this->m_pCamera = Leadwerks::Camera::Create(pParent);
	if (this->m_pCamera == nullptr) { std::cout << "Camera creation was unsiccessful. \n"; return CAMERA_CREATION_ERROR; }
	return 0;
}

int App::Initialize() {
	int initResults = 0;
	/* Window */
	initResults |= (this->m_bFullscreen) ? this->CreateWindow(Leadwerks::Window::FullScreen) : this->CreateWindow(Leadwerks::Window::Titlebar | Leadwerks::Window::Center);

	/* Context */
	initResults |= this->CreateContext();

	/* World */
	initResults |= this->CreateWorld();

	/* Camera */
	initResults |= this->CreateCamera(nullptr);

	/* Create a new instance of the LeadwerksInitialized event */
	auto pLeadwerksInitialized = gEventFactory.Create("EventData_LeadwerksInitialized");

	/* Create the delegate that will be binded to the application's OnLeadwerksInitialized class method */
	EventListenerDelegate leadwerksInitializedDelegate;
	leadwerksInitializedDelegate.Bind<App, &App::OnLeadwerksInitialized>(this);

	/* Add a new listener to the LeadwerksInitialized event, and queue the event to be fired during the 
	   - event manager's processing loop */
	gEventMgr->AddListener(leadwerksInitializedDelegate, pLeadwerksInitialized->ObjectType());
	gEventMgr->QueueEvent(*pLeadwerksInitialized);

	this->m_bSettingsChangedThisFrame = false;
	return initResults;
}

void App::Shutdown() {
	/* Perform any component-shutdown logic */
	SAFE_DELETE(gStateMgr);
	SAFE_DELETE(gInputMgr);
	SAFE_DELETE(gCameraMgr);
	SAFE_DELETE(gEventMgr);
}

App::App()
	: m_pWindow(nullptr), m_pContext(nullptr), m_pWorld(nullptr), m_pCamera(nullptr) {

	gApp = this;

	this->m_nScreenWidth = 1024.0f;
	this->m_nScreenHeight = 768.0f;
	
	this->m_bFullscreen = false;
	this->m_bPaused = false;
	this->m_bSettingsChangedThisFrame = true;
	this->m_bStateChangedThisFrame = true;
}

App::~App() { 
	this->Shutdown();

	SAFE_DELETE(this->m_pWorld); 
	SAFE_DELETE(this->m_pWindow);
}

bool App::RegisterApplicationEvents() {
	REGISTER_EVENT((new FactoryMaker < EventData_LeadwerksInitialized, BaseEventData >));

	return true;
}

void App::OnLeadwerksInitialized(BaseEventData* pData) {
	/* Simply write out notification that Leadwerks has been intitialized. 
	   - This indicates the out event manager is actually working, when 
	   - this method is called */
	std::cout << "Leadwerks Initialization Complete! \n";
}

bool App::Start()
{
	/* Initialize the application event manager */
	gEventMgr = new EventManager();

	/* Register all application-specific events */
	if (!this->RegisterApplicationEvents()) { return false; }

	//Initialize Steamworks (optional)
	/*if (!Steamworks::Initialize())
	{
		System::Print("Error: Failed to initialize Steam.");
		return false;
	}*/

	/* Initialize the application */
	if (this->Initialize() != 0) { return false; }

	/* Initialize the application input manager */
	gInputMgr = new InputManager(this->m_pWindow, this->m_pContext);
	gInputMgr->ToggleMouseCenter();

	/* Populate the new camera with default values */
	Leadwerks::Vec3 vZero = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);
	this->m_pCamera->SetRotation(vZero, false);
	this->m_pCamera->SetRotation(vZero, true);
	this->m_pCamera->SetPosition(vZero, false);
	this->m_pCamera->SetPosition(vZero, true);	

	/* Initialize the application camera manager */
	gCameraMgr = new CameraManager(this->m_pWindow, this->m_pContext, this->m_pWorld, this->m_pCamera);
	gCameraMgr->SetBehavior(CamBehavior::FLIGHT);

	/* Initialize the application state manager */
	gStateMgr = new StateManager();
	gStateMgr->AddState(new Game(), true);

	return true;
}

bool App::Loop()
{
	/* Update the application's event-management */
	gEventMgr->Update(20);	// Allow 20ms for event-queue processing.

	/* If the window is closed, for any reason, end the application */
	if (this->m_pWindow->Closed()) { return false; }

	/* Update the application's game-time, at 60fps */
	Leadwerks::Time::Update(60);
	gInputMgr->Update(Leadwerks::Time::GetSpeed());
	gCameraMgr->Update(Leadwerks::Time::GetSpeed());

	/* If the application's display settings changes this frame, re-initialize the application */
	if (this->m_bSettingsChangedThisFrame) {
		this->Initialize();
		return true;
	}

	gStateMgr->PreUpdate(Leadwerks::Time::GetSpeed());
	
	if (!this->m_bPaused) {
		/* Perform game-loop updates here */
		if (gStateMgr->Update(Leadwerks::Time::GetSpeed()) == false) { return true; }

		if (this->m_pWorld != nullptr) { this->m_pWorld->Update(); }		
	}

	/* Perform any 3D-rendering here */
	if (this->m_pWorld != nullptr) { this->m_pWorld->Render(); }
	gStateMgr->Render();

	this->m_pContext->SetBlendMode(Leadwerks::Blend::Alpha);
	/* Perform any 2D-rendering here.*/
	gStateMgr->Draw();

	this->m_pContext->SetBlendMode(Leadwerks::Blend::Solid);

	this->m_pContext->Sync(false);
	return true;
}
