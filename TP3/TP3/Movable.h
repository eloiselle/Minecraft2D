/*****************************************************************************
File  : Movable.h
Author: Anthony Cote
Date  : 2017-01-01
Goal  : Classe parent de haut niveau
        pour tout les objet sont manipuler de facon individuelles
******************************************************************************/

#pragma once
#include "pch.h"

#include "MagnetPosition.h"

class Movable : public MagnetPosition
{
protected:
    float _speed;       // Vitesse de deplacement

public:
    Movable() : _speed(1.f) {}; // Constructeur
    Movable(const Movable & e); // Copieur

    float getSpeed()const;      // Retourne la vitesse

    void setSpeed(float speed); // Change la vitesse
};
