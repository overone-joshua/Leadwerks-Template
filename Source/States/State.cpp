#pragma once
#include "State.hpp"

Factory<State> gStateFactory;

State::State(void) { }

void State::Load(void) { }

void State::Close(void) { }

void State::preUpdate(void) { }

void State::postUpdate(void) { }

void State::preRender(void) { }

void State::Render(void) { }

void State::postRender(void) { }

void State::preDraw(void) { }

void State::Draw(void) { }

void State::postDraw(void) { }