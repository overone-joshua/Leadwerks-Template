#pragma once
#include "StateManager.hpp"

StateManager::StateManager(void) 
	: m_bStateChangedThisFrame(false), m_pCurrentState(nullptr) { }

StateManager::~StateManager(void) { }

void StateManager::preUpdate(void) { }

void StateManager::Update(float dt) { }

void StateManager::postUpdate(void) { }

void StateManager::preRender(void) { }

void StateManager::postRender(void) { }

void StateManager::Render(void) { }

void StateManager::preDraw(void) { }

void StateManager::postDraw(void) { }

void StateManager::Draw(void) { }

void StateManager::CloseCurrentState(void) { }

bool StateManager::StateChangedThisFrame(void) { }