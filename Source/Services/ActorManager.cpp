#pragma once
#include "../Common.hpp"
#include "ActorManager.hpp"
#include "../Objects/Actor.hpp"
#include "../Components/Component.hpp"

#include <cassert>

ActorManager::ActorManager(const Factory<Component> pComponentFactory) 
	: m_nRunningIndex(0) , m_pComponentFactory(pComponentFactory) {	
}

ActorManager::~ActorManager(void) {

	auto iter = m_actors.begin();
	while (iter != m_actors.end()) {
		SAFE_DELETE(iter->second);
		iter++;
	}

	m_actors.empty();

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

const Actor* ActorManager::Fetch(uint64_t _id) {	
	
	auto it = m_actors.find(_id);
	if (it != m_actors.end()) { return it->second; }
	
	return nullptr;
}