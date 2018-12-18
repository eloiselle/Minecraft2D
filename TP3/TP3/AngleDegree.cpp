#pragma once
#include "AngleDegree.h"

// Retourne la direction
degree_t AngleDegree::getDirectionDegree()const
{
    return _degree;
}

// Retourne la direction
degree_t AngleDegree::getDirectionRadian()const
{
    return toRadian(_degree);
}

// Set la direction a partir de degree
void AngleDegree::setAngleDegree(degree_t degree)
{
    while (degree >= 360)
        degree -= 360;

    while (degree < 0)
        degree += 360;

    _degree = degree;
}

// set la direction a partir de radian
void AngleDegree::setAngleRadian(radian_t radian)
{
    _degree = toDegree(radian);
}

// Modify l'angle en fonction de l'agle actuel
void AngleDegree::rotate(degree_t rotation)
{
    setAngleDegree(_degree + rotation);
}

// Converti un angle en radian vers un angle en degree
degree_t AngleDegree::toDegree(radian_t radian)
{
    return radian * 360 / PI;
}

// Converti un angle en degree vers un angle en radian
degree_t AngleDegree::toRadian(degree_t degree)
{
    return tan(degree * PI / 180.0);
}