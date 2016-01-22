#ifndef _COMPONENT_HPP_
	#define _COMPONENT_HPP_
	
#pragma once
#include "Leadwerks.h"
#include "IComponent.hpp"

class Component : public Leadwerks::Object, public virtual IComponent {
public:
	
	~Component(void);

	virtual void Update(float deltaTime) = 0;
	void Render(void);
	void Draw(void);

}; // < end class.

#endif _COMPONENT_HPP_