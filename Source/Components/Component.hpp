#ifndef _COMPONENT_HPP_
	#define _COMPONENT_HPP_
	
#pragma once
#include "IComponent.hpp"
#include "..\Utilities\HasId.hpp"

class Component : public HasId<long>, public virtual IComponent {
public:	

	Component(long id);
	virtual ~Component(void);

	virtual void Update(float deltaTime) = 0;
	virtual void Render(void);
	virtual void Draw(void);

}; // < end class.

#endif _COMPONENT_HPP_