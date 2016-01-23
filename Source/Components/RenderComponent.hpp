#ifndef _RENDER_COMPONENT_HPP_
	#define _RENDER_COMPONENT_HPP_
	
#pragma once
#include "Leadwerks.h"
#include "Component.hpp"

class RenderComponent : public Component {
public:

	RenderComponent(long _id);
	~RenderComponent(void);

	void Update(float deltaTime);
	void Render(void);
	void Draw(void);	

	Leadwerks::Model& getModel(void);
	void setModel(Leadwerks::Model* pModel);

protected:

	Leadwerks::Model* m_pModel;

}; // < end class.


#endif _RENDER_COMPONENT_HPP_