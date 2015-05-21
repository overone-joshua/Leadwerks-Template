#pragma once
#include "Game.hpp"
#include "..\App.h"

Leadwerks::Model* pModel;
void Game::Load() {
	pModel = Leadwerks::Model::Create();
	pModel = Leadwerks::Model::Box(1.0f, 1.0f, 1.0f, nullptr);
	pModel->SetColor(1.0f, 0.0f, 0.0f, 1.0f);

	gApp->GetCamera().Move(0.0f, 0.0f, -5.0f);
}

void Game::Close() {
	pModel->Release();
}

void Game::Update(float deltaTime) {

}

void Game::Render() {

}

void Game::Draw() {

}