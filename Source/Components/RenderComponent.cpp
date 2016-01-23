#pragma once
#include "Leadwerks.h"
#include "RenderComponent.hpp"

Leadwerks::Model& RenderComponent::getModel(void) { return (*m_pModel); }

void RenderComponent::setModel(Leadwerks::Model* pModel) { m_pModel = pModel; }

RenderComponent::RenderComponent(long _id) : Component(_id), m_pModel(nullptr) { }

RenderComponent::~RenderComponent(void) { }

void RenderComponent::Update(float dt) { }

void RenderComponent::Render(void) { }

void RenderComponent::Draw(void) { }