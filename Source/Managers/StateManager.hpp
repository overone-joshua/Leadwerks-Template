#ifndef _STATEMANAGER_H_
	#define _STATEMANAGER_H_

#pragma once
#include <list>

enum class AppState { MainMenu, LevelEditor, Game, Paused, Options, Default };
class State;
class StateManager;

class State {
public:
										State(AppState appState = AppState::Default) { m_state = appState; }

	virtual void						Load() {}
	virtual void						Close() {}

	virtual void						Update(float deltaTime) {}
	virtual void						Render() {}
	virtual void						Draw() {}


	AppState							Id() { return m_state; }

protected:

private:
	AppState							m_state;

}; //end class State.

class StateManager {
public:
										StateManager();											// StateManager constructor.
										~StateManager();										// StateManager destructor.

	void								PreUpdate(float deltaTime);								// Method for performing pre-update logic for the state-manager.
	bool								Update(float deltaTime);								// The main update loop for the state-manager, and the current state.
	void								Render();												// The main redner loop for the state-manager, and the current state.
	void								Draw();													// The main 2D-renderer loop for the atate-manager, and the current state.

	void								AddState(State* pState, bool bChange = false);			// Adds a state to the state-manager state-list.
	void								RemoveState(State* pState);								// Removes the given state from the state-list.
	void								ChangeState(AppState appState);							// Changes the current state-manager state to the given application-state.
	void								ChangeState(State* pState);								// Changes the current state-manager state to the given state.
	State*								FindState(AppState appState);							// Attempts to find a state of the given application-state type from the state-manager state-list.

	State*								CurrentState();											// Gets the applications current state.
	std::list<State*>					States();												// Gets a std::list object containing all states registered with the state-manager.
	bool								StateChangedThisFrame();								// Gets whether a state change has occured this frame.

protected:
	bool								Contains(State* pState);								// Indicates whether the given state already exists within the state-manager.
	bool								Contains(AppState appState);							// Indicates whether a state of the given type already exists within the state-manager.

	void								CloseCurrentState();									// Closes the current state, if it is valid.

private:
	State*								m_pCurrentState;										// The current state of the state-manager.
	std::list<State*>					m_pStates;												// A list of all states registered with the state-manager.

	bool								m_bStateChangedThisFrame;								// Indicates if there was a change in state, this frame.
};

#endif // _STATEMANAGER_H_