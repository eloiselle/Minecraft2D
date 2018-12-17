#pragma once
#include "VectorAngle.h"

void VectorAngle::init(float length, float normalX, float normalY)
{
    _length = length;
    _normalizedX = normalX;
    _normalizedY = normalY;
}

float VectorAngle::getLength()const { return _length; }
float VectorAngle::getX()const { return _normalizedX * _length; }
float VectorAngle::getY()const { return _normalizedY * _length; }
float VectorAngle::getNormalizedX() const { return _normalizedX; }
float VectorAngle::getNormalizedY() const { return _normalizedY; }

void VectorAngle::setLength(float length) { _length = length; }

void VectorAngle::setLength(float x, float y)
{
    _length = sqrt(pow(x, 2) + pow(y, 2));
}

void VectorAngle::setAngleDegree(degree_t degree)
{
    while (degree >= 360)
        degree -= 360;

    while (degree < 0)
        degree += 360;

    _degree = degree;

    _normalizedX = cos(degree * PI / 180.0);
    _normalizedY = sin(degree * PI / 180.0);
}


void VectorAngle::setAngleRadian(radian_t radian)
{
    _degree = toDegree(radian);
    _normalizedX = cos(_degree * PI / 180.0);
    _normalizedY = sin(_degree * PI / 180.0);
}

void VectorAngle::setAngleFromXY(float x, float y)
{
    setAngleDegree(degreeFromXY(x, y));

}

void VectorAngle::rotate(degree_t rotation)
{
    setAngleDegree(_degree + rotation);
}

void VectorAngle::setXY(float x, float y)
{
    _length = lengthOfOffset(abs(x), abs(y));
    _normalizedX = x / _length;
    _normalizedY = y / _length;
}

// Retourne le longueur de l'hypothenuse d'un triangle a partir des dimensions
float VectorAngle::lengthOfOffset(float deltaX, float deltaY)
{
    return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

// Retourne le longueur de l'hypothenuse d'un triangle a partir des dimensions
float VectorAngle::pythagore(float deltaX, float deltaY)
{
    return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

float VectorAngle::degreeFromXY(float x, float y)
{
    float degree = toDegree(atan2(y, x)) / 2;

    while (degree >= 360) // Ne pas essayer d'utiliser modulo sur un float
        degree -= 360;

    while (degree < 0)
        degree += 360;

    return degree;
}

float VectorAngle::radianFromXY(float x, float y)
{
    return toRadian(degreeFromXY(x, y));
}