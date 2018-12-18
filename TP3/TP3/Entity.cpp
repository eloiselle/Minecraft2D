#pragma once
#include "Entity.h"

Entity::Entity(const Entity& e)
{
    _hitBoxSize = e._hitBoxSize;
    _speed = e._speed;
}

float Entity::getSpeed()const { return _speed; }
float Entity::getHitBoxSize()const { return _hitBoxSize; }

void Entity::setSpeed(float speed) { _speed = speed; }
void Entity::setHitBoxSize(float size) { _hitBoxSize = size; }