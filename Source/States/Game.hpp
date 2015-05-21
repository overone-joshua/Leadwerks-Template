#ifndef _GAME_H_
	#define _GAME_H_

#pragma once
#include "..\Managers\StateManager.hpp"

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

};

#endif // _GAME_H_