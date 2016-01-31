#pragma once
#include "../Common.hpp"
#include "ActorManager.hpp"
#include "../Objects/Actor.hpp"
#include "../Components/Component.hpp"

#include <cassert>
#include <vector>

ActorManager::ActorManager(const Factory<Component> pComponentFactory) 
	: m_nRunningIndex(0) , m_pComponentFactory(pComponentFactory) {	
}

ActorManager::~ActorManager(void) {

	RemoveAllComponents();

	DeleteAllActors();

}

uint64_t ActorManager::GetNextId(void) {

	m_nRunningIndex += 1;

	return m_nRunningIndex;
}


uint64_t ActorManager::Create(void) {	

	uint64_t index = this->GetNextId();	
	Actor* actor = new Actor();
	actor->setId(index);

	auto newActor = std::pair<uint64_t, Actor*>(index, actor);

	m_actors.insert(newActor);
	return index;

}

void ActorManager::Delete(uint64_t _id) {

	auto it = m_actors.find(_id);
	if (it != m_actors.end()) { 
		SAFE_DELETE(it->second);
		m_actors.erase(it); 
	}

}

void ActorManager::RemoveAllComponentsFor(uint64_t _id) {

	std::vector<ActorComponentMap::iterator> components;

	auto actor = this->Fetch(_id);
	assert(actor != nullptr);

	auto iter = m_actorComponents.begin();
	while (iter != m_actorComponents.end()) {
		auto it = (iter)->first.first;

		if (it == _id) { 
			SAFE_DELETE(iter->second);
			iter = m_actorComponents.erase(iter);
		}

		if (iter != m_actorComponents.end()) { iter++; }
	}	

}

const Actor* ActorManager::Fetch(uint64_t _id) {	
	
	auto it = m_actors.find(_id);
	if (it != m_actors.end()) { return it->second; }
	
	return nullptr;
}

std::vector<const Component*> ActorManager::FetchAllComponentsFor(uint64_t _id) {

	std::vector<const Component*> components;

	auto actor = this->Fetch(_id);
	assert(actor != nullptr);

	auto iter = m_actorComponents.begin();
	while (iter != m_actorComponents.end()) {
		auto it = (iter)->first.first;

		if (it == _id) { components.push_back(iter->second); }

		iter++;
	}

	return components;
}

void ActorManager::DeleteAllActors(void) {

	auto iter = m_actors.begin();
	while (iter != m_actors.end()) {
		SAFE_DELETE(iter->second);
		iter++;
	}

	m_actors.empty();

}

void ActorManager::RemoveAllComponents(void) {

	auto iter = m_actorComponents.begin();
	while (iter != m_actorComponents.end()) {
		SAFE_DELETE(iter->second);
		iter++;
	}

	m_actorComponents.empty();

}