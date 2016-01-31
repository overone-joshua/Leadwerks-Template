#pragma once
#include "Manager.hpp"

Manager::Manager(void) {

	assert(s_instance != nullptr);
	s_instance = this;

}

Manager::~Manager(void) { }

void Manager::Render(void) { }

void Manager::Draw(void) { }