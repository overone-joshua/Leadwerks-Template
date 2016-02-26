#ifndef _STATE_MANAGER_HPP_
	#define _STATE_MANAGER_HPP_
	
#pragma once
#include "../Utilities/Manager.hpp"
#include "../Utilities/Macros.hpp"
#include "../States/State.hpp"

#include <cassert>
#include <map>

class StateManager : public Manager {

	CLASS_TYPE(StateManager);

	typedef std::map<std::string,  State*> StateMap;

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
	void AddState(bool bChange = false);
	
	template <typename T>
	void RemoveState(void);

	void RemoveAllStates(void);
	
	template <typename T>
	void ChangeState(void);
	
	template <typename T>
	State* FetchState(void);
	
	template <typename T>
	bool IsStatePresent(void);
	
	void CloseCurrentState(void);
	
	bool StateChangedThisFrame(void);

protected:

	template <typename T>
	StateMap::iterator FetchStateInternal(void);


private:
	bool m_bStateChangedThisFrame;
	
	State* m_pCurrentState;

	StateMap m_states;

}; // < end class.
	
template <typename T>
void StateManager::AddState(bool bChange) {

	std::string type = T::ClassType();

	T* newState = (T*)(gStateFactory.Create(type));

	auto key = std::make_pair(type, newState);

	auto it = this->m_states.insert(key);

	if (bChange) { ChangeState<T>(); }

}

template <typename T>
void StateManager::RemoveState(void) {

	auto it = FetchStateInternal<T>();
	if (it == this->m_states.end()) { return; }
	
	SAFE_DELETE(it->second);

	this->m_states.erase(it);

}

template <typename T>
void StateManager::ChangeState(void) {

	if (this->m_pCurrentState != nullptr) 
	{
		CloseCurrentState();
	}

	this->m_pCurrentState = FetchState<T>();
	assert(this->m_pCurrentState != nullptr);

	this->m_pCurrentState->Load();

	this->m_bStateChangedThisFrame = true;
}

template <typename T>
 State* StateManager::FetchState(void) { 

	auto iter = FetchStateInternal<T>();
	if (iter == this->m_states.end()) { return nullptr; }

	return (iter)->second;

}

template <typename T>
StateManager::StateMap::iterator StateManager::FetchStateInternal(void) {

	std::string type = T::ClassType();
	
	auto iter = this->m_states.find(type);
	
	return iter;

}

template <typename T>
bool StateManager::IsStatePresent(void) {

	auto it = FetchStateInternal<T>();
	return it != this->m_states.end();

}

#endif _STATE_MANAGER_HPP_