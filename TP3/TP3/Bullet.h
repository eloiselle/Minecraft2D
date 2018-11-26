/*****************************************************************************
File  : Bullet.cpp
Author: Anthony Cote
Date  : 2017-01-01
Goal  : Projectiles
******************************************************************************/

#pragma once
#include "pch.h"

#include "Entity.h"
#include "Position.h"
#include "VectorAngle.h"

class Bullet : public Entity, public VectorAngle
{
public:
    Bullet() {};                                    // Constructeur sans parametres
    Bullet(float x, float y, float speed = 3.f);    // Constructeur avec parametres

    void advance(float multiplicator = 1);          // Se deplace dans la direction du vecteur d'angle
    void aim(int x, int y);                         // Change l'angle en fonction de coord
    void aim(MagnetPosition & mp);                  // Change l'angle an fonction de un objet
};
