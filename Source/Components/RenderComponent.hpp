#ifndef _RENDER_COMPONENT_HPP_
	#define _RENDER_COMPONENT_HPP_
	
#pragma once
#include "Leadwerks.h"
#include "Component.hpp"

#include "../Utilities/Macros.hpp"

class RenderComponent : public Component {

	CLASS_TYPE(RenderComponent);

public:

	RenderComponent(void);
	~RenderComponent(void);

	Leadwerks::Model& getModel(void);
	void setModel(Leadwerks::Model* pModel);

protected:

	Leadwerks::Model* m_pModel;

}; // < end class.

Leadwerks::Model& RenderComponent::getModel(void) { return (*m_pModel); }

void RenderComponent::setModel(Leadwerks::Model* pModel) { m_pModel = pModel; }

RenderComponent::RenderComponent(void) : m_pModel(nullptr) { }

RenderComponent::~RenderComponent(void) { }

#endif _RENDER_COMPONENT_HPP_