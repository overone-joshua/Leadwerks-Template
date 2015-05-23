#pragma once
#include "Game.hpp"
#include "..\App.h"
#include "..\Objects\GameObject.hpp"

Leadwerks::Model* pModel;
void Game::Load() {
	this->m_pObject = new GameObject();
	this->m_pTarget = new GameObject();

	this->m_pObject->SetModel(Leadwerks::Model::Box(1.0f, 1.0f, 1.0f, nullptr));
	this->m_pTarget->SetModel(Leadwerks::Model::Sphere(8.0f, nullptr));

	this->m_pObject->Model()->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	this->m_pTarget->Model()->SetColor(0.0f, 1.0f, 0.0f, 1.0f);

	this->m_pObject->SetPosition(-1.0f, 0.0f, 0.0f, true);
	this->m_pTarget->SetPosition(1.0f, 0.0f, 0.0f, true);

	gCameraMgr->SetTarget(m_pTarget);

	m_pLight = Leadwerks::DirectionalLight::Create(nullptr);
	m_pLight->SetRotation(75.0f, 0.0f, -35.0f);

	this->m_pFloor = Leadwerks::Model::Box(5.0f, 1.0f, 3.0f, nullptr);
	this->m_pFloor->Move(0.0f, -2.0f, 0.0f, true);
}

void Game::Close() {
	SAFE_DELETE(this->m_pObject);
	SAFE_DELETE(this->m_pTarget);

	this->m_pFloor->Release();
	this->m_pLight->Release();
}

void Game::Update(float deltaTime) {
	if (gApp->GetWindow().KeyHit(Leadwerks::Key::D1)) {
		gCameraMgr->SetBehavior(CamBehavior::FLIGHT);

	} 
	else if (gApp->GetWindow().KeyHit(Leadwerks::Key::D2)) {
		gCameraMgr->SetBehavior(CamBehavior::FIRST_PERSON);
	}
	else if (gApp->GetWindow().KeyHit(Leadwerks::Key::D3)) {
		gCameraMgr->SetBehavior(CamBehavior::THIRD_PERSON);
	}
}

void Game::Render() {

}

void Game::Draw() {

}