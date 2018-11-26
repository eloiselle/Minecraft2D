/*****************************************************************************
File  : Position.cpp
Author: Anthony Cote
Date  : 2018-04-23
Goal  : Position X & Y et operations de base
******************************************************************************/

#pragma once
#include "pch.h"

class Position
{
public:
    Position(float x = 0, float y = 0) : _x(x), _y(y) {};
    Position(Position& c);
    ~Position();

    // Get
    float getX()const;
    float getY()const;

    // Set
    void setX(float x);
    void setY(float y);
    void setPosition(float x, float y);

    void move(float plusX, float plusY);    // Deplace les coordonnées
    void move(Position& pos);               // Deplace a partir des coordonnés d'une autre position

protected:
    float _x;
    float _y;
};
