#pragma once
#include "App.h"
#include "Leadwerks.h"

#include <iostream>

/* Externals From App.h */
App* gApp;

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

	this->m_bSettingsChangedThisFrame = false;
	return initResults;
}

void App::Shutdown() {
	/* Perform any component-shutdown logic */

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

bool App::Start()
{
	//Initialize Steamworks (optional)
	/*if (!Steamworks::Initialize())
	{
		System::Print("Error: Failed to initialize Steam.");
		return false;
	}*/

	/* Initialize the application */
	if (this->Initialize() != 0) { return false; }

	/* Center and, or Hide Mouse */
	//this->m_pWindow->HideMouse();
	float mX = this->m_pWindow->GetWidth() * 0.5f; float mY = this->m_pWindow->GetHeight() * 0.5f;
	this->m_pWindow->SetMousePosition(mX, mY);

	/* Populate the new camera with default values */
	Leadwerks::Vec3 vZero = Leadwerks::Vec3(0.0f, 0.0f, 0.0f);
	this->m_pCamera->SetRotation(vZero, false);
	this->m_pCamera->SetRotation(vZero, true);
	this->m_pCamera->SetPosition(vZero, false);
	this->m_pCamera->SetPosition(vZero, true);

	/* Move camera back 5.0f meters */
	this->m_pCamera->Move(0.0f, 0.0f, -5.0f, true);

	return true;
}

bool App::Loop()
{
	/* If the window is closed, for any reason, end the application */
	if (this->m_pWindow->Closed()) { return false; }

	/* Update the application's game-time, at 60fps */
	Leadwerks::Time::Update(60);

	/* If the application's display settings changes this frame, re-initialize the application */
	if (this->m_bSettingsChangedThisFrame) {
		this->Initialize();
		return true;
	}

	if (!this->m_bPaused) {
		/* Perform game-loop updates here */
		if (this->m_pWorld != nullptr) { this->m_pWorld->Update(); }
		
	}

	/* Perform any 3D-rendering here */
	if (this->m_pWorld != nullptr) { this->m_pWorld->Render(); }

	this->m_pContext->SetBlendMode(Leadwerks::Blend::Alpha);
	/* Perform any 2D-rendering here.*/
	this->m_pContext->SetBlendMode(Leadwerks::Blend::Solid);

	this->m_pContext->Sync(false);
	return true;
}
