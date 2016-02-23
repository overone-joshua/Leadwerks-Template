#pragma once
#include "RenderComponent.hpp"
#include "Leadwerks.h"

Leadwerks::Model& RenderComponent::getModel(void) { return (*m_pModel); }

void RenderComponent::setModel(Leadwerks::Model* pModel) { m_pModel = pModel; }

RenderComponent::RenderComponent(void) : m_pModel(nullptr) { }

RenderComponent::~RenderComponent(void) { }