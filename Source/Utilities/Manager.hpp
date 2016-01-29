#ifndef _MANAGER_HPP_
	#define _MANAGER_HPP_

#pragma once
#include <cassert>

class Manager {
public:

	Manager(void);
	virtual ~Manager(void);

	virtual void Update(float deltaTime) = 0;
	virtual void Render(void);
	virtual void Draw(void);

private:

	static Manager* s_instance;

}; // end class.

Manager::Manager(void) {

	assert(s_instance == nullptr);
	s_instance = this;

}

Manager::~Manager(void) { }

void Manager::Render(void) { }

void Manager::Draw(void) { }

#endif _MANAGER_HPP_