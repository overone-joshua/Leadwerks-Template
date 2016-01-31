#pragma once
#include "StateManager.hpp"

StateManager::StateManager(void) 
	: m_bStateChangedThisFrame(false), m_pCurrentState(nullptr) { }

StateManager::~StateManager(void) { 

	RemoveAllStates();

}

void StateManager::preUpdate(void) { 

	if (this->StateChangedThisFrame()) { CloseCurrentState(); }

	if (this->m_pCurrentState != nullptr) { m_pCurrentState->preUpdate(); }

}

void StateManager::Update(float dt) { 	

	if (this->m_pCurrentState != nullptr) { 
		
		this->m_bStateChangedThisFrame = !this->m_pCurrentState->Update(dt); 
	}

}

void StateManager::postUpdate(void) {

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->postUpdate(); }

}

void StateManager::preRender(void) {

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->preRender(); }

}

void StateManager::postRender(void) { 

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->postRender(); }

}

void StateManager::Render(void) {

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->Render(); }

}

void StateManager::preDraw(void) {

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->preDraw(); }

}

void StateManager::postDraw(void) { 

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->postDraw(); }

}

void StateManager::Draw(void) {

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->Draw(); }

}

void StateManager::CloseCurrentState(void) { 

	if (this->m_pCurrentState != nullptr) { 

		m_pCurrentState->Close(); 
		m_pCurrentState = nullptr;
	}

	m_bStateChangedThisFrame = false;

}

bool StateManager::StateChangedThisFrame(void) { return this->m_bStateChangedThisFrame; }

void StateManager::RemoveAllStates(void) {

	StateManager::StateMap states;

	if (m_pCurrentState != nullptr) { CloseCurrentState(); }

	auto iter = m_states.begin();
	while (iter != m_states.end()) {

		SAFE_DELETE(iter->second);

		iter++;

	}

	m_states.empty();

}
