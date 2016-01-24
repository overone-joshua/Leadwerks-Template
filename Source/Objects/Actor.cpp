#pragma once
#include "Actor.hpp"
#include "../Utilities/HasId.hpp"

Actor::Actor(long _id) : HasId<long>(_id) { }

Actor::~Actor(void) { }