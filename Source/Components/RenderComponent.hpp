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


#endif _RENDER_COMPONENT_HPP_