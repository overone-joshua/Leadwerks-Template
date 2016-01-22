#pragma once
#include "Leadwerks.h"
#include "RenderComponent.hpp"

RenderComponent::RenderComponent(long _id) : Component(_id), m_pModel(nullptr) { }

RenderComponent::~RenderComponent(void) { }

void RenderComponent::Update(float dt) { }

void RenderComponent::Render(void) { }

void RenderComponent::Draw(void) { }