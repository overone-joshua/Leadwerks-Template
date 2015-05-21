#pragma once
#include "StateManager.hpp"
#include "..\App.h"
#include <cassert>
#include <list>

State* StateManager::CurrentState() {
	return m_pCurrentState;
}

std::list<State*> StateManager::States() {
	return m_pStates;
}

StateManager::StateManager() 
	: m_pCurrentState(nullptr) {

}

StateManager::~StateManager() {
	/* Clear all states that were registered with the state-manager */
	this->CloseCurrentState();

	this->m_pStates.clear();

}

void StateManager::PreUpdate(float deltaTime) {
	this->m_bStateChangedThisFrame = false;
}

bool StateManager::Update(float deltaTime) {
	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->Update(deltaTime); }

	if (this->m_bStateChangedThisFrame) { return false; }

	return true;
}

void StateManager::Render() {
	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->Render(); }
}

void StateManager::Draw() {
	if (this->m_pCurrentState != nullptr) { this->m_pCurrentState->Draw(); }
}

void StateManager::AddState(State* pState, bool bChange) {
	assert(pState != nullptr);

	if (this->Contains(pState)) { return; }

	this->m_pStates.push_back(pState);
	if (!bChange) { return; }

	CloseCurrentState();

	this->m_pCurrentState = this->m_pStates.back();
	this->m_pCurrentState->Load();
}

void StateManager::RemoveState(State* pState) {
	assert(pState != nullptr);
	if (!this->Contains(pState)) { return; }

	CloseCurrentState();
	this->m_pStates.remove(pState);
}

void StateManager::ChangeState(AppState appState) {
	/*std::list<State*>::reverse_iterator rIter = this->m_pStates.rend();
	while (rIter != this->m_pStates.rbegin()) {
		if ((*rIter)->Id() == appState) {
			CloseCurrentState();

			this->m_pCurrentState = (*rIter);
			this->m_pCurrentState->Load();

			this->m_bStateChangedThisFrame = true;
			break;			
		}

		rIter--;
	}*/

	State* pState = this->FindState(appState);
	assert(pState != nullptr);

	CloseCurrentState();
	this->m_pCurrentState = pState;
	this->m_pCurrentState->Load();
}

void StateManager::ChangeState(State* pState) {
	assert(pState != nullptr);
	assert(this->Contains(pState));
	
	CloseCurrentState();

	this->m_pCurrentState = pState;
	this->m_pCurrentState->Load();

	this->m_bStateChangedThisFrame = true;

}

State* StateManager::FindState(AppState appState) {
	std::list<State*>::iterator iter = this->m_pStates.begin();
	while (iter != this->m_pStates.end()) {
		if ((*iter)->Id() == appState)
			return (*iter);
		else
			iter++;
	}

	return nullptr;
}

bool StateManager::Contains(State* pState) {
	assert(pState != nullptr);

	return this->Contains(pState->Id());
}

bool StateManager::Contains(AppState appState) {
	if (this->FindState(appState) == nullptr) { return false; }

	return true;
}

void StateManager::CloseCurrentState() {
	if (this->m_pCurrentState != nullptr) { 
		this->m_pCurrentState->Close(); 
		this->m_pCurrentState = nullptr; 
	}
}