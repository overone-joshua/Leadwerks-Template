#pragma once
#include "RenderComponentManager.hpp"
#include "../Utilities/ComponentManager.hpp"
#include "../Services/ActorManager.hpp"

RenderComponentManager::RenderComponentManager(const ActorManager* pActorManager)
	: ComponentManager(pActorManager) {

}

void RenderComponentManager::Update(float dt) {	

}