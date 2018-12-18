#pragma once
#include "TopDownCharacter.h"

void TopDownCharacter::init()
{
    _direction = DOWN;
    _isWalking = false;
}

// Get
DIRECTION4 TopDownCharacter::getDirection() { return _direction; }
bool TopDownCharacter::isWalking()const { return _isWalking; }

// Set
void TopDownCharacter::setDirection(DIRECTION4 dir) { _direction = dir; }
void TopDownCharacter::isWalking(bool isWalking) { _isWalking = isWalking; }

// Se déplace automatiquement en fonction de la direction et de la vitesse
void TopDownCharacter::move()
{
    move(D4[_direction][X] * _speed, D4[_direction][Y] * _speed);
}

// Deplace dans une direction
void TopDownCharacter::move(DIRECTION4 dir)
{
    _direction = dir;
    move(D4[dir][X] * _speed, D4[dir][Y] * _speed);
}

// Change la position exacte et recalcule la position sur la grille
void TopDownCharacter::move(pixel_t plusX, pixel_t plusY)
{
    move(plusX * TILE_SIZE, plusY * TILE_SIZE);
    setPositionInGrid(
        getExactX() / TILE_SIZE,
        getExactY() / TILE_SIZE);
}