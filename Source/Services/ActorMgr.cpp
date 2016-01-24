#pragma once
#include "ActorMgr.hpp"
#include "../Utilities/Macros.hpp"

ActorMgr::ActorMgr(void) : m_nRunningIndex(0) {	
	m_pActorManager = new Manager<Actor>();
}

ActorMgr::~ActorMgr(void) {	
	SAFE_DELETE(m_pActorManager);
}

long ActorMgr::GenerateId(void) { 
	
	m_nRunningIndex += 1; 
	
	return m_nRunningIndex; 
}

Actor* ActorMgr::Fetch(long _id) {
	return m_pActorManager->Fetch(_id);
}

Actor* ActorMgr::Create(void) {
	return m_pActorManager->Create(GenerateId());
}

void ActorMgr::Delete(long _id) {
	m_pActorManager->Delete(_id);
}