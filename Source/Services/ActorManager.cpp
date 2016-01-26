#pragma once
#include "../Common.hpp"
#include "ActorManager.hpp"

ActorManager::ActorManager(void) : m_nRunningIndex(0) {	
}

ActorManager::~ActorManager(void) {
}

uint64_t ActorManager::GenerateId(void) {

	m_nRunningIndex += 1;

	return m_nRunningIndex;
}

Actor* ActorManager::Fetch(uint64_t _id) {	
	return nullptr;
}

Actor* ActorManager::Create(void) {	
	return nullptr;
}

void ActorManager::Delete(uint64_t _id) {	
}
