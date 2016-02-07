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

	void FetchComponents(void);

	const ActorManager* m_pActorManager;	

	const T* m_components;

}; // end class.

template <typename T>
ComponentManager<T>::ComponentManager(const ActorManager* pActorManager)
	: m_pActorManager(pActorManager) { }

template <typename T>
ComponentManager<T>::~ComponentManager(void) { 

	m_components.empty();
	m_pActorManager = nullptr; 

}

template <typename T>
void ComponentManager<T>::FetchComponents(void) {

	m_components = m_pActorManager->FetchAllComponentsOf<T>();

}

#endif _COMPONENT_MANAGER_HPP_