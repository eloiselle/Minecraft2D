#pragma once
#include "Entity.h"

Entity::Entity(const Entity& e)
{
    _hitBoxSize = e._hitBoxSize;
    _speed = e._speed;
}

float Entity::getSpeed()
{
    return _speed;
}

void Entity::setSpeed(float speed)
{
    _speed = speed;
}

float Entity::getHitBoxSize()
{
    return _hitBoxSize;
}

void Entity::setHitBoxSize(float size)
{
    _hitBoxSize = size;
}