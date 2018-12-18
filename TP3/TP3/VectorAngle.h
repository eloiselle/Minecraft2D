/*****************************************************************************
File  : VectorAngle.hpp
Author: Anthony Cote
Date  : 2017-01-01
Goal  : Defini un vecteur d'angle, qui est un angle avec une longueur, ou une ligne
******************************************************************************/
#pragma once
#include "pch.h"

#include "AngleDegree.h"
#include "MagnetPosition.h"

// Vector d'angle avec une position de base (0,0)
class VectorAngle : public AngleDegree
{
protected:
    float _normalizedX, _normalizedY;   // Distance cardinale entre [-1,1] du vecteur
    float _length;                      // Longueur du vecteur (multiplicateur)

public:
    void init(float length = 1, float normalX = 1, float normalY = 0);  // Constructeur

    float getNormalizedX()const;                            // Retourne la position normalized x
    float getNormalizedY()const;                            // Retourne la position normalized y
    float getX()const;                                      // Retourne la position x
    float getY()const;                                      // Retourne la position y
    virtual float getLength()const;                         // Retourne la longuer du vecteur

    virtual void setLength(float length);                   // Change la longueur
    virtual void setLength(float x, float y);               // Change la longueur selon des coords
    void setAngleDegree(degree_t degree)override;           // Change la direction en degree
    void setAngleRadian(radian_t radian)override;           // Change la direction en radian
    void setAngleFromXY(float x, float y);                  // Change l'angle a partir de coordonnees
    void rotate(degree_t rotation)override;                 // Tourne l'angle dans la direction Clockwise

    void setXY(float x, float y);                           // Change l'angle et normalize

    // Static
    static float lengthOfOffset(float x, float y);          // Retourne la longueur de hypotenuse
    static float pythagore(float deltaX, float deltaY);     // Retourne la longueur de hypotenuse
    static float radianFromXY(float x, float y);            // Trouve l'angle Radian a partir de coord
    static float degreeFromXY(float x, float y);            // Trouve l'angle Degree a partir de coord
};
