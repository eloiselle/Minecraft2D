/*****************************************************************************
File  : AngleDegree.h
Author: Anthony Cote
Date  : 2017-01-01
Goal  : Angle en degree modifiable
******************************************************************************/
#pragma once
#include "pch.h"

typedef float degree_t;
typedef float radian_t;

class AngleDegree
{
protected:
    degree_t _degree;                               // Direction en degree

public:
    AngleDegree() : _degree(0) {};                  // Constructeur
    degree_t getDirectionDegree()const;             // Retourne la direction en degree
    degree_t getDirectionRadian()const;             // Retourne la direction en radian
    virtual void setAngleDegree(degree_t degree);   // Change la direction en degree
    virtual void setAngleRadian(radian_t radian);   // Change la direction en radian
    virtual void rotate(degree_t rotation);         // Tourne l'angle dans la direction Clockwise

    // Static methods
    static degree_t toDegree(radian_t radian);      // Converti un radian en degree
    static degree_t toRadian(degree_t degree);      // Converti un degree en radian
};
