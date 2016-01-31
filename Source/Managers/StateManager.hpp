#ifndef _STATE_MANAGER_HPP_
	#define _STATE_MANAGER_HPP_
	
#pragma once
#include "../Utilities/Manager.hpp"

#include <list>

class State;

class StateManager : public Manager {
public:

	StateManager(void);
	~StateManager(void);

	void preUpdate(void);
	void postUpdate(void);
	void Update(float deltaTime);

	void preRender(void);
	void postRender(void);
	void Render(void);
	
	void preDraw(void);
	void postDraw(void);
	void Draw(void);

	template <typename T>
	void AddState(void);
	
	template <typename T>
	void RemoveState(void);
	
	template <typename T>
	void ChangeState(void);
	
	template <typename T>
	const State* FetchState(void);
	
	template <typename T>
	bool IsStatePresent(void);
	
	void CloseCurrentState(void);
	
	bool StateChangedThisFrame(void);

private:
	bool m_bStateChangedThisFrame;
	const State* m_pCurrentState;

	std::list<const State*> m_states;

}; // < end class.
	
template <typename T>
void StateManager::AddState(void) { }

template <typename T>
void StateManager::RemoveState(void) { }

template <typename T>
void StateManager::ChangeState(void) { }

template <typename T>
const State* StateManager::FetchState(void) { }

template <typename T>
bool StateManager::IsStatePresent(void) { }

#endif _STATE_MANAGER_HPP_