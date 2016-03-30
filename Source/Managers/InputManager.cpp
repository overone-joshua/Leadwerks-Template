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

float InputManager::PosZ() {
    return this->GetMousePosition().z;
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

float InputManager::OldPosZ() {
    auto val = this->GetFloat("oldMouseZ");
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

float InputManager::DeltaZ() {
    auto val = this->GetFloat("deltaZ");
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

float InputManager::CenterZ() {
    auto val = this->GetFloat("centerZ");
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

InputManager::InputManager(void)
	: m_pWindow(nullptr), m_pContext(nullptr), m_bCenterMouse(false), m_pEventManager(nullptr)
{

}

InputManager::InputManager(Leadwerks::Window* pWindow, Leadwerks::Context* pContext, EventManager* pEventManager)
	: m_pWindow(pWindow), m_pContext(pContext), m_bCenterMouse(false), m_pEventManager(pEventManager) {

	Initialize(pWindow, pContext, pEventManager);
}

InputManager::~InputManager()
{
    Dispose();
}

void InputManager::Dispose(void)
{
    UnRegisterInputEvents();

    this->m_pWindow = nullptr;
    this->m_pContext = nullptr;
}

void InputManager::Initialize(Leadwerks::Window* pWindow, Leadwerks::Context* pContext, EventManager* pEventManager)
{
	assert(this->m_pWindow != nullptr);
	assert(this->m_pContext != nullptr);

	RegisterInputEvents();

	Set("centerX", this->m_pWindow->GetWidth() * 0.5f);
	Set("centerY", this->m_pWindow->GetHeight() * 0.5f);
	this->m_pWindow->SetMousePosition(CenterX(), CenterY());

	/* Register input-properties */
	Set("currMouseX", this->GetMousePosition().x)->
		Set("currMouseY", this->GetMousePosition().y)->
        Set("currMouseZ", this->GetMousePosition().z)->
		Set("oldMouseX", this->GetMousePosition().x)->
		Set("oldMouseY", this->GetMousePosition().y)->
        Set("oldMouseZ", this->GetMousePosition().z)->
		Set("deltaX", 0.0f)->
		Set("deltaY", 0.0f)->
        Set("deltaZ", 0.0f);

    unsigned index = 0;
    while (index < 256) {

        m_currentKeyboardPressedState[index] = false;
        m_currentKeyboardState[index] = false;
        m_previousKeyboardState[index] = false;

        if (index < 6)
        {
            m_currentMousePressedState[index] = false;
            m_currentMouseState[index] = false;
            m_previousMouseState[index] = false;
        }

        index += 1;
    }

	this->Update(1.0f);
}

void InputManager::Update(float deltaTime) {
	GenerateInputEvents();

	this->Set("currMouseX", this->PosX());
	this->Set("currMouseY", this->PosY());
    this->Set("currMouseZ", this->PosZ());

	float deltaX = this->PosX() - this->OldPosX();
	float deltaY = this->PosY() - this->OldPosY();
    float deltaZ = this->PosZ() - this->OldPosZ();

	this->Set("deltaX", deltaX);
	this->Set("deltaY", deltaY);
    this->Set("deltaZ", deltaZ);
	if (this->DeltaX() == 0.0f && this->DeltaY() == 0.0f && this->DeltaZ() == 0.0f) { return; }

	if (this->m_bCenterMouse) { this->CenterMouse(); }
	else { this->UpdateMousePosition(); }

	this->Set("oldMouseX", PosX());
	this->Set("oldMouseY", PosY());
    this->Set("oldMouseZ", PosZ());
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
    REGISTER_EVENT((new FactoryMaker<Event_MouseMove, BaseEventData>));

	REGISTER_EVENT((new FactoryMaker<Event_MouseHit, BaseEventData>));
	REGISTER_EVENT((new FactoryMaker<Event_MouseDown, BaseEventData>));
	REGISTER_EVENT((new FactoryMaker<Event_MouseUp, BaseEventData>));

	REGISTER_EVENT((new FactoryMaker<Event_KeyHit, BaseEventData>));
	REGISTER_EVENT((new FactoryMaker<Event_KeyDown, BaseEventData>));
	REGISTER_EVENT((new FactoryMaker<Event_KeyUp, BaseEventData>));
}

void InputManager::UnRegisterInputEvents(void) {
    gEventFactory.Unregister("Event_MouseMove");

	gEventFactory.Unregister("Event_MouseHit");
	gEventFactory.Unregister("Event_MouseDown");
	gEventFactory.Unregister("Event_MouseUp");

	gEventFactory.Unregister("Event_KeyHit");
	gEventFactory.Unregister("Event_KeyDown");
	gEventFactory.Unregister("Event_KeyUp");
}

void InputManager::GenerateInputEvents(void) {
    auto dX = DeltaX();
    auto dY = DeltaY();
    auto dZ = DeltaZ();

    if (dX != 0 || dY != 0)
    {
        /* Create key-up Event. */
        auto mouseMove = (gEventFactory.Create("Event_MouseMove"));

        /* Set the required values for the event. */
        mouseMove->Set("vOriginal", Leadwerks::Vec3(OldPosX(), OldPosY(), OldPosZ()));
        mouseMove->Set("vCurrent", Leadwerks::Vec3(PosX(), PosY(), PosZ()));
        mouseMove->Set("vDelta", Leadwerks::Vec3(dX, dY, dZ));

        /* Queue the event for execution. */
        m_pEventManager->QueueEvent(*mouseMove);
    }

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