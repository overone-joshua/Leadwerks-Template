#pragma once
#include "Component.hpp"

Factory<Component> gComponentFactory;

Component::Component(void) { }

Component::~Component(void) { }