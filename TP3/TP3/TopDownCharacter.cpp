#include "TopDownCharacter.h"

void TopDownCharacter::init()
{
    _direction = D4_DOWN;
    _isWalking = false;
}

// Get
DIRECTION4 TopDownCharacter::getDirection() { return _direction; }
//float TopDownCharacter::getLength() { return _length; }
bool TopDownCharacter::isWalking() { return _isWalking; }
void TopDownCharacter::stayThere() { move(0, 0); }

// Set
//void TopDownCharacter::setDirection(int dir) { _direction = dir; } TODO casting
void TopDownCharacter::setDirection(DIRECTION4 dir) { _direction = dir; }
void TopDownCharacter::isWalking(bool isWalking) { _isWalking = isWalking; }

// Se déplace automatiquement en fonction de la direction et de la vitesse
void TopDownCharacter::move()
{
    move(D4_x[_direction] * _speed, D4_y[_direction] * _speed);
}

// Deplace dans une direction
void TopDownCharacter::move(DIRECTION4 dir)
{
    _direction = dir;
    move(D4_x[dir] * _speed, D4_y[dir] * _speed);
}

// Change la position exacte et recalcule la position sur la grille
void TopDownCharacter::move(pixel_t plusX, pixel_t plusY)
{
    move(plusX * TILE_SIZE, plusY * TILE_SIZE);
    setPositionInGrid(
        getExactX() / TILE_SIZE,
        getExactY() / TILE_SIZE);
}