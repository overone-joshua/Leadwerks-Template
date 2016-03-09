#pragma once
#include "StateManager.hpp"
#include "../Utilities/Container.hpp"

#include "../Utilities/Event.hpp"
#include "EventManager.hpp"

#include <cassert>

StateManager::StateManager(void)
	: m_bStateChangedThisFrame(false), m_pCurrentState(nullptr),
	m_pContainer(nullptr), m_pEventManager(nullptr)
{

}

StateManager::StateManager(Container* pContainer, EventManager* pEventManager) 
	: m_bStateChangedThisFrame(false), m_pCurrentState(nullptr),
	m_pContainer(pContainer), m_pEventManager(pEventManager)
{
	Initialize(pContainer, pEventManager);
}

StateManager::~StateManager(void) { 

	RemoveAllStates();

	m_pEventManager->Unbind<StateManager, &StateManager::OnMouseDown>(this, Event_MouseDown::ClassType());
	m_pEventManager->Unbind<StateManager, &StateManager::OnMouseUp>(this, Event_MouseUp::ClassType());
	m_pEventManager->Unbind<StateManager, &StateManager::OnMouseHit>(this, Event_MouseHit::ClassType());

	m_pEventManager->Unbind<StateManager, &StateManager::OnKeyDown>(this, Event_KeyDown::ClassType());
	m_pEventManager->Unbind<StateManager, &StateManager::OnKeyUp>(this, Event_KeyUp::ClassType());
	m_pEventManager->Unbind<StateManager, &StateManager::OnKeyHit>(this, Event_KeyHit::ClassType());

	this->m_pEventManager = nullptr;
}

void StateManager::Configure(Container* pContainer)
{
	m_pEventManager->Bind<StateManager, &StateManager::OnMouseDown>(this, Event_MouseDown::ClassType());
	m_pEventManager->Bind<StateManager, &StateManager::OnMouseUp>(this, Event_MouseUp::ClassType());
	m_pEventManager->Bind<StateManager, &StateManager::OnMouseHit>(this, Event_MouseHit::ClassType());

	m_pEventManager->Bind<StateManager, &StateManager::OnKeyDown>(this, Event_KeyDown::ClassType());
	m_pEventManager->Bind<StateManager, &StateManager::OnKeyUp>(this, Event_KeyUp::ClassType());
	m_pEventManager->Bind<StateManager, &StateManager::OnKeyHit>(this, Event_KeyHit::ClassType());
}

void StateManager::Initialize(Container* pContainer, EventManager* pEventManager)
{
	assert(this->m_pContainer != nullptr);
	this->Configure(pContainer);
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

void StateManager::OnMouseHit(BaseEventData* pData) 
{
	if (pData == nullptr || this->m_pCurrentState == nullptr) { return; }
	auto event = static_cast<Event_MouseHit*>(pData);

	this->m_pCurrentState->OnMouseHit(event);

}

void StateManager::OnMouseDown(BaseEventData* pData) 
{
	if (pData == nullptr || this->m_pCurrentState == nullptr) { return; }
	auto event = static_cast<Event_MouseDown*>(pData);

	this->m_pCurrentState->OnMouseDown(event);

}

void StateManager::OnMouseUp(BaseEventData* pData) 
{
	if (pData == nullptr || this->m_pCurrentState == nullptr) { return; }
	auto event = static_cast<Event_MouseUp*>(pData);

	this->m_pCurrentState->OnMouseUp(event);

}

void StateManager::OnKeyHit(BaseEventData* pData) 
{
	if (pData == nullptr || this->m_pCurrentState == nullptr) { return; }
	auto event = static_cast<Event_KeyHit*>(pData);

	this->m_pCurrentState->OnKeyHit(event);

}

void StateManager::OnKeyDown(BaseEventData* pData) 
{
	if (pData == nullptr || this->m_pCurrentState == nullptr) { return; }
	auto event = static_cast<Event_KeyDown*>(pData);

	this->m_pCurrentState->OnKeyDown(event);

}

void StateManager::OnKeyUp(BaseEventData* pData) 
{
	if (pData == nullptr || this->m_pCurrentState == nullptr) { return; }
	auto event = static_cast<Event_KeyUp*>(pData);

	this->m_pCurrentState->OnKeyUp(event);

}