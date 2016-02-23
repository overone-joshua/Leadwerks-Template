#ifndef _COMPONENT_MANAGER_HPP_
	#define _COMPONENT_MANAGER_HPP_

#pragma once
#include "../Services/ActorManager.hpp"
#include "Manager.hpp"

#include <vector>

template <typename T>
class ComponentManager : public Manager {
public:

	ComponentManager(const ActorManager* pActorManager);
	~ComponentManager(void);	

private:	

	const ActorManager* m_pActorManager;		

}; // end class.

template <typename T>
ComponentManager<T>::ComponentManager(const ActorManager* pActorManager)
	: m_pActorManager(pActorManager) { }

template <typename T>
ComponentManager<T>::~ComponentManager(void) { 

	m_pActorManager = nullptr; 

}

#endif _COMPONENT_MANAGER_HPP_