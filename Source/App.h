#ifndef _APP_H_
	#define _APP_H_

#pragma once
#include "Leadwerks.h"

class App {
public:
	App(void);
	virtual ~App(void);

	bool Start(void);

	void preUpdate(void);
	void postUpdate(void);
	bool Update(float deltaTime);

	void preRender(void);
	void postRender(void);
	void Render(void);

	void preDraw(void);
	void postDraw(void);
	void Draw(void);

protected:

private:

}; // end class.

#endif // _APP_H_