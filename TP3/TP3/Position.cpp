#pragma once
#include "Position.h"

// Copieur
Position::Position(Position & c)
{
    _x = c._x;
    _y = c._y;
}

float Position::getX()const { return _x; }
float Position::getY()const { return _y; }

void Position::setX(float x) { _x = x; }
void Position::setY(float y) { _y = y; }

// Modifi la position
void Position::setPosition(float x, float y)
{
    _x = x;
    _y = y;
}

// Deplace les coordonnées
void Position::move(float plusX, float plusY)
{
    _x += plusX;
    _y += plusY;
}

// Déplace les coordonnées a partir d'une autre position
void Position::move(Position& pos)
{
    _x += pos._x;
    _y += pos._y;
}