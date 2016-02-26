#pragma once
#include "StateManager.hpp"
#include "../Utilities/Container.hpp"

#include <cassert>

StateManager::StateManager(const Container* pContainer) 
	: m_bStateChangedThisFrame(false), m_pCurrentState(nullptr) , m_pContainer(pContainer) 
{
	assert(this->m_pContainer != nullptr);
}

StateManager::~StateManager(void) { 

	RemoveAllStates();

}

void StateManager::preUpdate(void)
{ 
	if (this->StateChangedThisFrame()) { return; }

	if (this->m_pCurrentState != nullptr) { m_pCurrentState->preUpdate(); }

}

void StateManager::Update(float dt) 
{
	if (this->StateChangedThisFrame()) { return; }

	if (this->m_pCurrentState != nullptr) { 
		
		this->m_bStateChangedThisFrame = !this->m_pCurrentState->Update(dt); 
	}

}

void StateManager::postUpdate(void)
{
	if (this->StateChangedThisFrame()) { return; }

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->postUpdate(); }

}

void StateManager::preRender(void)
{
	if (this->StateChangedThisFrame()) { return; }

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->preRender(); }

}

void StateManager::postRender(void) 
{ 
	if (this->StateChangedThisFrame()) { return; }

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->postRender(); }

}

void StateManager::Render(void)
{
	if (this->StateChangedThisFrame()) { return; }

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->Render(); }

}

void StateManager::preDraw(void) 
{
	if (this->StateChangedThisFrame()) { return; }

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->preDraw(); }

}

void StateManager::postDraw(void) 
{ 
	if (this->StateChangedThisFrame()) { return; }

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->postDraw(); }

}

void StateManager::Draw(void) {

	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->Draw(); }

	this->m_bStateChangedThisFrame = false;
}

void StateManager::CloseCurrentState(void) { 

	if (this->m_pCurrentState != nullptr) { 

		this->m_pCurrentState->Close(); 
		this->m_pCurrentState = nullptr;
	}

	this->m_bStateChangedThisFrame = false;

}

bool StateManager::StateChangedThisFrame(void) { return this->m_bStateChangedThisFrame; }

void StateManager::RemoveAllStates(void) {

	StateManager::StateMap states;

	if (this->m_pCurrentState != nullptr) { CloseCurrentState(); }

	auto iter = this->m_states.begin();
	while (iter != this->m_states.end()) {

		SAFE_DELETE(iter->second);

		iter++;

	}

	this->m_states.empty();

}
