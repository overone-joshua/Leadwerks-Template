#pragma once
#include "InputManager.hpp"
#include "Leadwerks.h"
#include <cassert>

float InputManager::PosX() {
	return this->m_pWindow->GetMousePosition().x;
}

float InputManager::PosY() {
	return this->m_pWindow->GetMousePosition().y;
}

float InputManager::OldPosX() {
	return this->m_nOldPosX;
}

float InputManager::OldPosY() {
	return this->m_nOldPosY;
}

float InputManager::DeltaX() {
	return this->m_nDeltaX;
}

float InputManager::DeltaY() {
	return this->m_nDeltaY;
}

float InputManager::CenterX() {
	return this->m_pWindow->GetWidth() * 0.5f;
}

float InputManager::CenterY() {
	return this->m_pWindow->GetHeight() * 0.5f;
}

void InputManager::ToggleMouseCenter() {
	this->m_bCenterMouse = !this->m_bCenterMouse;
}

void InputManager::SetWindow(Leadwerks::Window* pWindow) {
	assert(pWindow != nullptr);

	this->m_pWindow = pWindow;
}

void InputManager::SetContext(Leadwerks::Context* pContext) {
	assert(pContext != nullptr);

	this->m_pContext = pContext;
}

InputManager::InputManager(Leadwerks::Window* pWindow, Leadwerks::Context* pContext) 
	: m_pWindow(pWindow), m_pContext(pContext), m_bCenterMouse(false), m_nOldPosX(0.0f),
	  m_nOldPosY(0.0f), m_nDeltaX(0.0f), m_nDeltaY(0.0f) {

	assert(this->m_pWindow != nullptr);
	assert(this->m_pContext != nullptr);

	this->m_pWindow->SetMousePosition(CenterX(), CenterY());
	this->Update(1.0f);
}

InputManager::~InputManager() {
	this->m_pWindow = nullptr;
	this->m_pContext = nullptr;
}

void InputManager::Update(float deltaTime) {
	this->m_nDeltaX = PosX() - this->m_nOldPosX;
	this->m_nDeltaY = PosY() - this->m_nOldPosY;

	if (DeltaX() == 0.0f && DeltaY() == 0.0f) { return; }

	if (this->m_bCenterMouse) { this->m_pWindow->SetMousePosition(CenterX(), CenterY()); }
	else { this->m_pWindow->SetMousePosition(PosX(), PosY()); }

	this->m_nOldPosX = PosX();
	this->m_nOldPosY = PosY();
}