#pragma once
#include "GameObject.hpp"
#include "Leadwerks.h"
#include "..\App.h"

Leadwerks::Vec3 GameObject::Position() {
	return this->m_pModel->GetPosition();
}

Leadwerks::Vec3 GameObject::Rotation() {
	return this->m_pModel->GetRotation();
}

Leadwerks::Vec3 GameObject::Scale() {
	return this->m_pModel->GetScale();
}

Leadwerks::Vec3 GameObject::CameraPosition() {
	return this->m_pCamera->GetPosition();
}

Leadwerks::Vec3 GameObject::CameraRotation() {
	return this->m_pCamera->GetRotation();
}

Leadwerks::Vec3 GameObject::Forward() {
	return this->m_vForward;
}

Leadwerks::Vec3 GameObject::Right() {
	return this->m_vRight;
}

Leadwerks::Vec3 GameObject::Up() {
	return this->m_vUp;
}

Leadwerks::Vec3 GameObject::Velocity() {
	return this->m_vVelocity;
}

Leadwerks::Vec3 GameObject::CameraForward() {
	return this->m_vCameraForward;
}

Leadwerks::Vec3 GameObject::CameraRight() {
	return this->m_vCameraRight;
}

Leadwerks::Vec3 GameObject::CameraUp() {
	return this->m_vCameraUp;
}

float GameObject::Pitch() {
	return this->Rotation().x;
}

float GameObject::Yaw() {
	return this->Rotation().y;
}

float GameObject::Roll() {
	return this->Rotation().z;
}

float GameObject::CameraPitch() {
	return this->CameraRotation().x;
}

float GameObject::CameraYaw() {
	return this->CameraRotation().y;
}

float GameObject::CameraRoll() {
	return this->CameraRotation().z;
}

float GameObject::MoveSpeed() {
	return this->m_nMoveSpeed;
}

float GameObject::StrafeSpeed() {
	return this->m_nStrafeMoveSpeed;
}

float GameObject::VertSpeed() {
	return this->m_nVertMoveSpeed;
}

Leadwerks::Camera* GameObject::Camera() {
	return this->m_pCamera;
}

Leadwerks::Model* GameObject::Model() {
	return this->m_pModel;
}

void GameObject::SetMoveSpeed(float nSpeed) {
	this->m_nMoveSpeed = nSpeed;
}

void GameObject::SetStrafeSpeed(float nSpeed) {
	this->m_nStrafeMoveSpeed = nSpeed;
}

void GameObject::SetVertSpeed(float nSpeed) {
	this->m_nVertMoveSpeed = nSpeed;
}

void GameObject::SetCamera(Leadwerks::Camera* pCamera) {
	this->m_pCamera = pCamera;
	this->m_pCamera->SetParent(this->m_pModel);
}

void GameObject::SetModel(Leadwerks::Model* pModel) {
	if (this->m_pModel != nullptr) { this->m_pModel->Release(); }

	if (this->m_pModel == nullptr) { 
		this->m_pModel = Leadwerks::Model::Create();
		return;
	}

	this->m_pModel = pModel;
}

GameObject::GameObject() 
	: m_pModel(Leadwerks::Model::Create()), m_pCamera(nullptr), m_nMoveSpeed(0.25f),
	  m_nStrafeMoveSpeed(0.25f), m_nVertMoveSpeed(0.25f), m_vVelocity(0.0f, 0.0f, 0.0f),
	  m_vForward(0.0f, 0.0f, 1.0f), m_vRight(1.0f, 0.0f, 0.0f), m_vUp(0.0f, 1.0f, 0.0f),
	  m_vCameraForward(0.0f, 0.0f, 1.0f), m_vCameraRight(1.0f, 0.0f, 0.0f), 
	  m_vCameraUp(0.0f, 1.0f, 0.0f) {

}

GameObject::~GameObject() {
	if (this->m_pModel != nullptr) { this->m_pModel->Release(); }
	
}

void GameObject::Update(float deltaTime) {
	this->m_vForward = CalcForwardVector(this->Pitch(), this->Yaw());
	this-> m_vRight = CalcRightVector(this->Pitch(), this->Yaw());
	this->m_vUp = CalcUpVector(this->Pitch(), this->Yaw());

	this->m_vCameraForward = CalcForwardVector(this->CameraPitch(), this->CameraYaw());
	this->m_vCameraRight = CalcRightVector(this->CameraPitch(), this->CameraYaw());
	this->m_vCameraUp = CalcUpVector(this->CameraPitch(), this->CameraYaw());

	CalcVelocity();
}

void GameObject::Render() {

}

void GameObject::Draw() {

}

void GameObject::Move(float deltaTime) {
	this->m_pModel->Move(Leadwerks::Vec3(Velocity().x * (deltaTime), Velocity().y * (deltaTime), Velocity().z * (deltaTime)), false);
}

void GameObject::SetRotation(float x, float y, float z, bool bGlobal) {
	this->SetRotation(Leadwerks::Vec3(x, y, z), bGlobal);
}

void GameObject::SetRotation(Leadwerks::Vec3 vRotation, bool bGlobal) {
	this->m_pModel->SetRotation(vRotation, bGlobal);
}

void GameObject::SetPosition(float x, float y, float z, bool bGlobal) {
	this->SetPosition(Leadwerks::Vec3(x, y, z), bGlobal);
}

void GameObject::SetPosition(Leadwerks::Vec3 vPosition, bool bGlobal) {
	this->m_pModel->SetPosition(vPosition, bGlobal);
}

void GameObject::SetCameraRotation(float x, float y, float z, bool bGlobal) {
	this->SetCameraRotation(Leadwerks::Vec3(x, y, z), bGlobal);
}

void GameObject::SetCameraRotation(Leadwerks::Vec3 vRotation, bool bGlobal) {
	this->m_pCamera->SetRotation(vRotation, bGlobal);
}

void GameObject::SetCameraPosition(float x, float y, float z, bool bGlobal) {
	this->SetCameraPosition(Leadwerks::Vec3(x, y, z), bGlobal);
}

void GameObject::SetCameraPosition(Leadwerks::Vec3 vPosition, bool bGlobal) {
	this->m_pCamera->SetPosition(vPosition, bGlobal);
}

void GameObject::SetCameraPitch(float nPitch, bool bGlobal) {
	this->m_pCamera->Turn(nPitch, 0.0f, 0.0f, bGlobal);
}

void GameObject::SetCameraYaw(float nYaw, bool bGlobal) {
	this->m_pCamera->Turn(0.0f, nYaw, 0.0f, bGlobal);
}

void GameObject::SetCameraRoll(float nRoll, bool bGlobal) {
	this->m_pCamera->Turn(0.0f, 0.0f, nRoll, bGlobal);
}

void GameObject::SetModelPitch(float nPitch, bool bGlobal) {
	this->m_pModel->Turn(nPitch, 0.0f, 0.0f, bGlobal);
}

void GameObject::SetModelYaw(float nYaw, bool bGlobal) {
	this->m_pModel->Turn(0.0f, nYaw, 0.0f, bGlobal);
}

void GameObject::SetModelRoll(float nRoll, bool bGlobal) {
	this->m_pModel->Turn(0.0f, 0.0f, nRoll, bGlobal);
}

Leadwerks::Vec3 GameObject::CalcForwardVector(float pitch, float yaw) {
	float fx = Leadwerks::Math::Cos(pitch) * Leadwerks::Math::Sin(yaw);
	float fy = -Leadwerks::Math::Sin(pitch);
	float fz = Leadwerks::Math::Cos(pitch) * Leadwerks::Math::Cos(yaw);
	return Leadwerks::Vec3(fx, fy, fz).Normalize();
}


Leadwerks::Vec3 GameObject::CalcRightVector(float pitch, float yaw) {
	float fx = Leadwerks::Math::Cos(pitch) * Leadwerks::Math::Sin(yaw + 90);
	float fy = 0;
	float fz = Leadwerks::Math::Cos(pitch) * Leadwerks::Math::Cos(yaw + 90);
	return Leadwerks::Vec3(fx, fy, fz).Normalize();
}


Leadwerks::Vec3 GameObject::CalcUpVector(float pitch, float yaw) {
	float fx = Leadwerks::Math::Cos(pitch + 90) * Leadwerks::Math::Sin(yaw);
	float fy = Leadwerks::Math::Sin(pitch + 90);
	float fz = Leadwerks::Math::Cos(pitch + 90) * Leadwerks::Math::Cos(yaw);
	return Leadwerks::Vec3(fx, fy, fz).Normalize();
}

void GameObject::CalcVelocity() {
	Leadwerks::Window& window = gApp->GetWindow();
	this->m_vVelocity =  Leadwerks::Vec3(
		(window.KeyDown(Leadwerks::Key::D) - window.KeyDown(Leadwerks::Key::A)) * this->m_nStrafeMoveSpeed,
		(window.KeyDown(Leadwerks::Key::E) - window.KeyDown(Leadwerks::Key::Q)) * this->m_nVertMoveSpeed,
		(window.KeyDown(Leadwerks::Key::W) - window.KeyDown(Leadwerks::Key::S)) * this->m_nMoveSpeed);
}