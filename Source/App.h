#ifndef _APP_H_
	#define _APP_H_

#pragma once
#include "Leadwerks.h"

class Container;

class EventManager;
class InputManager;
class StateManager;

class App {
public:
					App			(void);
	virtual 		~App		(void);

	void			Configure(Container* pContainer);

	bool 			Start		(void);
	void			Shutdown	(void);

	void 			preUpdate	(void);
	void 			postUpdate	(void);
	bool 			Update		(float deltaTime);

	void 			preRender	(void);
	void 			postRender	(void);
	void 			Render		(void);

	void 			preDraw		(void);
	void 			postDraw	(void);
	void 			Draw		(void);

protected:

	void			Dispose		(void);

private:

	Leadwerks::Camera* m_pCamera;

	EventManager* m_pEventManager;
	InputManager* m_pInputManager;
	StateManager* m_pStateManager;

}; // end class.

#endif // _APP_H_