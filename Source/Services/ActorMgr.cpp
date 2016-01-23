#pragma once
#include "ActorMgr.hpp"

ActorMgr::ActorMgr(void) { }

ActorMgr::~ActorMgr(void) { }

long ActorMgr::GenerateId(void) { 
	
	m_nRunningIndex += 1; 
	
	return m_nRunningIndex; 
}