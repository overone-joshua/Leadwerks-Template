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

	void Update(float deltaTime);

protected:

	void FetchComponents(void);

	const T* m_components;

private:	

	const ActorManager* m_pActorManager;		

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

template <typename T>
void ComponentManager<T>::Update(float deltaTime) {

	FetchComponents();

}

#endif _COMPONENT_MANAGER_HPP_