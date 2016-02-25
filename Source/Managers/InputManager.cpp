#pragma once
#include "..\Common.hpp"
#include "InputManager.hpp"
#include "..\Utilities\Event.hpp"
#include "EventManager.hpp"
#include "..\Utilities\ParameterMap.hpp"
#include <cassert>

float InputManager::PosX() {
	return this->GetMousePosition().x;
}

float InputManager::PosY() {
	return this->GetMousePosition().y;
}

float InputManager::OldPosX() {
	auto val = this->GetFloat("oldMouseX");
	if (val != this->GetFloatMap().end()) { return val->second; }
	else { return this->GetMousePosition().x; }
}

float InputManager::OldPosY() {
	auto val = this->GetFloat("oldMouseY");
	if (val != this->GetFloatMap().end()) { return val->second; }
	else { return this->GetMousePosition().y; }
}

float InputManager::DeltaX() {
	auto val = this->GetFloat("deltaX");
	if (val != this->GetFloatMap().end()) { return val->second; }
	else { return 0.0f; }
}

float InputManager::DeltaY() {
	auto val = this->GetFloat("deltaY");
	if (val != this->GetFloatMap().end()) { return val->second; }
	else { return 0.0f; }
}

float InputManager::CenterX() {
	auto val = this->GetFloat("centerX");
	if (val != this->GetFloatMap().end()) { return val->second; }
	else { return this->GetWindowCenter().x; }
}

float InputManager::CenterY() {
	auto val = this->GetFloat("centerY");
	if (val != this->GetFloatMap().end()) { return val->second; }
	else { return this->GetWindowCenter().y; }
}

void InputManager::ToggleMouseCenter() {
	this->m_bCenterMouse = !this->m_bCenterMouse;
}

void InputManager::CenterMouse(void) { 
	this->m_pWindow->SetMousePosition(CenterX(), CenterY()); 
}

void InputManager::UpdateMousePosition(void) { 
	this->m_pWindow->SetMousePosition(PosX(), PosY());
}

Leadwerks::Vec3 InputManager::GetMousePosition() {
	return this->m_pWindow->GetMousePosition();
}

Leadwerks::Vec3 InputManager::GetWindowCenter() {
	return Leadwerks::Vec3(
		this->m_pWindow->GetWidth() * 0.5f,		// Half-width
		this->m_pWindow->GetHeight() * 0.5f,	// Half-height
		0.0f);
}

void InputManager::SetWindow(Leadwerks::Window* pWindow) {
	assert(pWindow != nullptr);

	this->m_pWindow = pWindow;
}

void InputManager::SetContext(Leadwerks::Context* pContext) {
	assert(pContext != nullptr);

	this->m_pContext = pContext;
}

InputManager::InputManager(Leadwerks::Window* pWindow, Leadwerks::Context* pContext, EventManager* pEventManager) 
	: m_pWindow(pWindow), m_pContext(pContext), m_bCenterMouse(false), m_pEventManager(pEventManager) {

	assert(this->m_pWindow != nullptr);
	assert(this->m_pContext != nullptr);

	RegisterInputEvents();

	Set("centerX", this->m_pWindow->GetWidth() * 0.5f);
	Set("centerY", this->m_pWindow->GetHeight() * 0.5f);
	this->m_pWindow->SetMousePosition(CenterX(), CenterY());

	/* Register input-properties */
	Set("currMouseX", this->GetMousePosition().x)->
	Set("currMouseY", this->GetMousePosition().y)->
	Set("oldMouseX", this->GetMousePosition().x)->
	Set("oldMouseY", this->GetMousePosition().y)->
	Set("deltaX", 0.0f)->
	Set("deltaY", 0.0f);

	this->Update(1.0f);
}

InputManager::~InputManager() {
	UnRegisterInputEvents();

	this->m_pWindow = nullptr;
	this->m_pContext = nullptr;
}

void InputManager::Update(float deltaTime) {
	GenerateInputEvents();

	this->Set("currMouseX", this->PosX());
	this->Set("currMouseY", this->PosY());

	float deltaX = this->PosX() - this->OldPosX();
	float deltaY = this->PosY() - this->OldPosY();

	this->Set("deltaX", deltaX);
	this->Set("deltaY", deltaY);
	if (this->DeltaX() == 0.0f && this->DeltaY() == 0.0f) { return; }

	if (this->m_bCenterMouse) { this->CenterMouse(); }
	else { this->UpdateMousePosition(); }

	this->Set("oldMouseX", PosX());
	this->Set("oldMouseY", PosY());
}

void InputManager::CheckMouseInput(int button) {
	Leadwerks::Vec3 vMousePosition = GetMousePosition();	

	/* Snag the current and previous mouse-button's state. */
	bool bCurrent = m_currentMouseState[button] = m_pWindow->mousedownstate[button];
	bool bCurrentPressedState = m_currentMousePressedState[button];
	bool bPrevious = m_previousMouseState[button];	
	
	/* Was the button hit? */
	if (bCurrent && !bPrevious) {
		/* Create LeftMouseButton Hit Event. */
		auto buttonHit = (gEventFactory.Create("Event_MouseHit"));

		/* Set the required values for the event. */
		buttonHit->Set("vMousePosition", vMousePosition);
		buttonHit->Set("nMouseButton", button);

		/* Queue the event for execution. */
		m_pEventManager->QueueEvent(*buttonHit);
	}
	/* Is the button pressed? */
	else if (!bCurrentPressedState) {
		if (bCurrent && bPrevious) {
			/* Create LeftMouseButton Pressed Event. */
			auto buttonPressed = (gEventFactory.Create("Event_MouseDown"));

			/* Set the required values for the event. */
			buttonPressed->Set("vMousePosition", vMousePosition);
			buttonPressed->Set("nMouseButton", button);

			/* Queue the event for execution. */
			m_pEventManager->QueueEvent(*buttonPressed);

			m_currentMousePressedState[button] = true;
		}
	}
	/* Was the button released? */
	else if (!bCurrent && bPrevious) {
		/* Create LeftMouseButton Released Event. */
		auto buttonUp = (gEventFactory.Create("Event_MouseUp"));

		/* Set the required values for the event. */
		buttonUp->Set("vMousePosition", vMousePosition);
		buttonUp->Set("nMouseButton", button);

		/* Queue the event for execution. */
		m_pEventManager->QueueEvent(*buttonUp);

		m_currentMousePressedState[button] = false;
	}

	/* Store the current down state for the left mouse button so we 
	 * - can check it next frame. */
	m_previousMouseState[button] = bCurrent;	
}

void InputManager::CheckKeyboardInput(int key) {
	/* Snag the current and previous mouse-button's state. */
	bool bCurrent = m_currentKeyboardState[key] = m_pWindow->keydownstate[key];
	bool bCurrentPressedState = m_currentKeyboardPressedState[key];
	bool bPrevious = m_previousKeyboardState[key];

	/* Was the key hit? */
	if (bCurrent && !bPrevious) {
		/* Create key-hit Event. */
		auto keyHit = (gEventFactory.Create("Event_KeyHit"));

		/* Set the required values for the event. */		
		keyHit->Set("nKey", key);

		/* Queue the event for execution. */
		m_pEventManager->QueueEvent(*keyHit);
	}
	/* Is the key pressed? */
	else if (!bCurrentPressedState) {
		if (bCurrent && bPrevious) {
			/* Create key-pressed Event. */
			auto keyPressed = (gEventFactory.Create("Event_KeyDown"));

			/* Set the required values for the event. */			
			keyPressed->Set("nKey", key);

			/* Queue the event for execution. */
			m_pEventManager->QueueEvent(*keyPressed);

			m_currentKeyboardPressedState[key] = true;
		}
	}
	/* Was the key released? */
	else if (!bCurrent && bPrevious) {
		/* Create key-up Event. */
		auto keyUp = (gEventFactory.Create("Event_KeyUp"));

		/* Set the required values for the event. */		
		keyUp->Set("nKey", key);

		/* Queue the event for execution. */
		m_pEventManager->QueueEvent(*keyUp);

		m_currentKeyboardPressedState[key] = false;
	}

	/* Store the current down state for the left mouse button so we
	* - can check it next frame. */
	m_previousKeyboardState[key] = bCurrent;
}

void InputManager::RegisterInputEvents(void) {
	REGISTER_EVENT((new FactoryMaker<Event_MouseHit, BaseEventData>));
	REGISTER_EVENT((new FactoryMaker<Event_MouseDown, BaseEventData>));
	REGISTER_EVENT((new FactoryMaker<Event_MouseUp, BaseEventData>));

	REGISTER_EVENT((new FactoryMaker<Event_KeyHit, BaseEventData>));
	REGISTER_EVENT((new FactoryMaker<Event_KeyDown, BaseEventData>));
	REGISTER_EVENT((new FactoryMaker<Event_KeyUp, BaseEventData>));
}

void InputManager::UnRegisterInputEvents(void) {	
	gEventFactory.Unregister("Event_MouseHit");
	gEventFactory.Unregister("Event_MouseDown");
	gEventFactory.Unregister("Event_MouseUp");

	gEventFactory.Unregister("Event_KeyHit");
	gEventFactory.Unregister("Event_KeyDown");
	gEventFactory.Unregister("Event_KeyUp");
}

void InputManager::GenerateInputEvents(void) {
	unsigned index = 0;
	while (index < 256) {
		/* Keyboard has 256 keys so for each iteration, check
		 * - the current input for the key. */
		CheckKeyboardInput(index);

		/* Mouse only has 6 buttons so rather than have a 
		 * - seperate loop. just check button state
		 * - where appropriate. */
		if (index < 6) { CheckMouseInput(index); }

		index += 1;
	}	
}