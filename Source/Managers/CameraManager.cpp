#pragma once
#include "CameraManager.hpp"
#include "..\Objects\GameObject.hpp"
#include "..\App.h"
#include <cassert>


CamBehavior CameraManager::CameraBehavior() {
	return this->m_behavior;
}


Leadwerks::Camera* CameraManager::GetCamera() {
	return this->m_pCamera->Camera();
}


GameObject& CameraManager::Target() {
	return *this->m_pTarget;
}


void CameraManager::SetBehavior(CamBehavior behavior) {
	this->m_pCamera->SetRotation(0.0f, 0.0f, 0.0f, false);
	this->m_pCamera->SetRotation(0.0f, 0.0f, 0.0f, true);

	this->m_pCamera->SetCameraRotation(0.0f, 0.0f, 0.0f, false);
	this->m_pCamera->SetCameraRotation(0.0f, 0.0f, 0.0f, true);

	this->m_behavior = behavior;
}


void CameraManager::SetTarget(GameObject* pObject) {
	assert(pObject != nullptr);
	
	this->m_pTarget = pObject;
}


void CameraManager::SetWindow(Leadwerks::Window* pWindow) {
	assert(pWindow != nullptr);

	this->m_pWindow = pWindow;
}


void CameraManager::SetContext(Leadwerks::Context* pContext) {
	assert(pContext != nullptr);

	this->m_pContext = pContext;
}


void CameraManager::SetWorld(Leadwerks::World* pWorld) {
	assert(pWorld != nullptr);

	this->m_pWorld = pWorld;
}


void CameraManager::SetCamera(Leadwerks::Camera* pCamera) {
	assert(pCamera != nullptr);

	this->m_pCamera->SetCamera(pCamera);
}

void CameraManager::SetMoveSpeed(float nSpeed) {
	this->m_pCamera->SetMoveSpeed(nSpeed);
}

void CameraManager::SetStrafeSpeed(float nSpeed) {
	this->m_pCamera->SetStrafeSpeed(nSpeed);
}

void CameraManager::SetVertSpeed(float nSpeed) {
	this->m_pCamera->SetVertSpeed(nSpeed);
}

void CameraManager::SetMinOffset(Leadwerks::Vec3 vMin) {
	this->m_vMinOffset = vMin;
}

void CameraManager::SetMaxOffset(Leadwerks::Vec3 vMax) {
	this->m_vOffset = vMax;
}

void CameraManager::SetMinAngle(float nAngle) {
	this->m_nMinAngleClamp = nAngle;
}

void CameraManager::SetMaxAngle(float nAngle) {
	this->m_nMaxAngleClamp = nAngle;
}

Leadwerks::Vec3 CameraManager::MinOffset() {
	return this->m_vMinOffset;
}

Leadwerks::Vec3 CameraManager::MaxOffset() {
	return this->m_vOffset;
}

float CameraManager::MinAngle() {
	return this->m_nMinAngleClamp;
}

float CameraManager::MaxAngle() {
	return this->m_nMaxAngleClamp;
}

float CameraManager::MoveSpeed() {
	return this->m_pCamera->MoveSpeed();
}

float CameraManager::StrafeSpeed() {
	return this->m_pCamera->StrafeSpeed();
}

float CameraManager::VertSpeed() {
	return this->m_pCamera->VertSpeed();
}

float CameraManager::Pitch() {
	return this->m_pCamera->Pitch();
}

float CameraManager::Yaw() {
	return this->m_pCamera->Yaw();
}

Leadwerks::Vec3 CameraManager::Forward() {
	return this->m_pCamera->Forward();
}

Leadwerks::Vec3 CameraManager::Right() {
	return this->m_pCamera->Right();
}

Leadwerks::Vec3 CameraManager::Up() {
	return this->m_pCamera->Up();
}

Leadwerks::Vec3 CameraManager::Velocity() {
	return this->m_pCamera->Velocity();
}

Leadwerks::Window& CameraManager::GetWindow() {
	return *this->m_pWindow;
}

Leadwerks::Context& CameraManager::GetContext() {
	return *this->m_pContext;
}

Leadwerks::World& CameraManager::GetWorld() {
	return *this->m_pWorld;
}

CameraManager::CameraManager(Leadwerks::Window* pWindow, Leadwerks::Context* pContext, Leadwerks::World* pWorld, Leadwerks::Camera* pCamera) 
	: m_behavior(CamBehavior::CAMERA_NOT_INITIALIZED), m_pTarget(nullptr) ,
	  m_pCamera(new GameObject()), m_pWindow(pWindow), m_pContext(pContext), m_pWorld(pWorld),
	  m_vMinOffset(0.0f, 0.0f, -0.25f), m_vOffset(0.0f, 0.0f, -2.0f),
	  m_nMinAngleClamp(-82.0f), m_nMaxAngleClamp(68.0f), m_bClampViewingAngles(false) {

	m_pCamera->SetCamera(pCamera);

}


CameraManager::~CameraManager() {
	this->Shutdown();
}


void CameraManager::Update(float deltaTime) {
	this->m_pCamera->Update(deltaTime);

	float pitch = this->m_pCamera->Pitch();
	float yaw = this->m_pCamera->Yaw();
	float roll = this->m_pCamera->Roll();

	/* Clamp viewing angles */
	if (this->m_bClampViewingAngles) { pitch = Leadwerks::Math::Clamp(pitch + (gInputMgr->DeltaY() * 0.1f), this->m_nMinAngleClamp, this->m_nMaxAngleClamp); }
	else { pitch += (gInputMgr->DeltaY() * 0.1f); }	

	switch (this->m_behavior) {
	case CamBehavior::FIRST_PERSON: {
		if (this->m_pTarget == nullptr) { this->m_behavior = CamBehavior::FLIGHT; return; }
		this->m_pCamera->Camera()->SetRotation(pitch + this->m_pCamera->CameraPitch(), yaw + (gInputMgr->DeltaX() * 0.1f) + this->m_pCamera->CameraYaw(), roll + this->m_pCamera->CameraRoll(), false);
		this->m_pCamera->SetPosition(this->m_pTarget->Position());
		break;
	}
	case CamBehavior::THIRD_PERSON: {
		if (this->m_pTarget == nullptr) { this->m_behavior = CamBehavior::FLIGHT; return; }
		this->m_pCamera->Model()->SetRotation(pitch + this->m_pCamera->CameraPitch(), yaw + (gInputMgr->DeltaX() * 0.1f) + this->m_pCamera->CameraYaw(), roll + this->m_pCamera->Roll(), false);

		Leadwerks::Vec3 vRot = this->m_pCamera->Rotation();
		Leadwerks::Vec3 vPos = this->m_pTarget->Position();

		this->m_pCamera->SetRotation(this->m_pCamera->Rotation());
		this->m_pCamera->SetPosition(this->m_pTarget->Position());

		// Calculate the furthest offset.
		this->m_pCamera->Model()->Move(this->m_vOffset, false);

		Leadwerks::PickInfo pick;
		Leadwerks::World* world = this->m_pWorld;
		if (world->Pick(vPos, this->m_pCamera->Position(), pick, 0, true)) {
			Leadwerks::Vec3 distance = vPos.DistanceToPoint(pick.position);

			if (distance.x < m_vMinOffset.x || distance.y < m_vMinOffset.y || distance.z < m_vMinOffset.z)
				this->m_pCamera->SetPosition(vPos);
			else
				this->m_pCamera->SetPosition(pick.position + Leadwerks::Vec3(-0.25f, -0.25f, -0.25f));
		}
		else
		{
			this->m_pCamera->SetPosition(this->m_pCamera->Position());
		}

		break; 
	}
	case CamBehavior::FLIGHT: {
		this->m_pCamera->Model()->SetRotation(pitch, yaw + (gInputMgr->DeltaX() * 0.1f), roll, false);
		this->m_pCamera->Move(deltaTime);
		break;
	}
	default: {
		break;
	} }
}


void CameraManager::Render() {

}


void CameraManager::Draw() {

}


void CameraManager::Shutdown() {
	SAFE_DELETE(m_pCamera);
	this->m_pTarget = nullptr;

	this->m_pWindow = nullptr;
	this->m_pContext = nullptr;
	this->m_pWorld = nullptr;
	this->m_pCamera = nullptr;

	this->m_behavior = CamBehavior::CAMERA_NOT_INITIALIZED;
}