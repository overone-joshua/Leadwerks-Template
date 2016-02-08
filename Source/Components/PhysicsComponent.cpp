#pragma once
#include "PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(void) 
	: m_vPosition(0.0f, 0.0f, 0.0f), m_vRotation(0.0f, 0.0f, 0.0f), m_vScale(1.0f, 1.0f, 1.0f) { }

PhysicsComponent::~PhysicsComponent(void) { }

Leadwerks::Vec3 PhysicsComponent::getPosition(void) {

	return m_vPosition;

}

Leadwerks::Vec3 PhysicsComponent::getRotation(void) {

	return m_vRotation;

}

Leadwerks::Vec3 PhysicsComponent::getScale(void) {
	
	return m_vScale;

}

void PhysicsComponent::setPosition(Leadwerks::Vec3 vPosition) {

	m_vPosition = vPosition;

}

void PhysicsComponent::setRotation(Leadwerks::Vec3 vRotation) {

	m_vRotation = vRotation;

}

void PhysicsComponent::setScale(Leadwerks::Vec3 vScale) {

	m_vScale = vScale;

}