#ifndef _GAME_H_
	#define _GAME_H_

#pragma once
#include "Leadwerks.h"
#include "..\Managers\StateManager.hpp"

class GameObject;

class Game : public State {
public:
	Game() : State(AppState::Game) {}

	void Load();
	void Close();

	void Update(float deltaTime);
	void Render();
	void Draw();

protected:

private:
	GameObject* m_pObject;
	GameObject* m_pTarget;

	Leadwerks::Light* m_pLight;
	Leadwerks::Model* m_pFloor;
};

#endif // _GAME_H_