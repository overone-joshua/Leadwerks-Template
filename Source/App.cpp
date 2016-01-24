#pragma once
#include "Leadwerks.h"
#include "App.h"

#include "Common.hpp"
#include "Utilities\Macros.hpp"
App::App(void) { }

App::~App(void) { }

bool App::Start(void) {
	
	std::cout << "Application initialization completed successfully. \n";
	
	return true;
}

void App::Shutdown(void) {	
}
void App::preUpdate(void) { }

bool App::Update(float dt) { return true; }

void App::postUpdate(void) { }

void App::preRender(void) { }

void App::Render(void) { }

void App::postRender(void) { }

void App::preDraw(void) { }

void App::Draw(void) { }

void App::postDraw(void) { }