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

	Manager* s_instance;

}; // end class.

#endif _MANAGER_HPP_