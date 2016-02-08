#ifndef _RENDER_COMPONENT_MANAGER_HPP_
	#define _RENDER_COMPONENT_MANAGER_HPP_

#pragma once
#include "../Utilities/ComponentManager.hpp"
#include "../Services/ActorManager.hpp"
#include "../Components/RenderComponent.hpp"

class RenderComponentManager : public ComponentManager<RenderComponent> {
public:

	RenderComponentManager(const ActorManager* pActorManager);	

	void Update(float deltaTime);

}; // end class.

#endif _RENDER_COMPONENT_MANAGER_HPP_