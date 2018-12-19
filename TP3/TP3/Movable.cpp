#pragma once
#include "Movable.h"

Movable::Movable(const Movable& m) { _speed = m._speed; }

float Movable::getSpeed()const { return _speed; }

void Movable::setSpeed(float speed) { _speed = speed; }
