#pragma once
#include "Component.hpp"

Component::Component(long _id) : HasId<long>(_id) {	}

Component::~Component(void) { }

void Component::Render(void) { }

void Component::Draw(void) { }