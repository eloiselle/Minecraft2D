/*****************************************************************************
File  : Entity.cpp
Author: Anthony Cote
Date  : 2017-01-01
Goal  : Classe parent de haut niveau
        pour tout les objet sont manipuler de facon individuelles
******************************************************************************/

#pragma once
#include "pch.h"

#include "Position.h"
#include "MagnetPosition.h"
#include "Killable.h"

using namespace std;

class Entity : public MagnetPosition
{
protected:
    float _hitBoxSize;  // Distance a avoir pour entrer en contact
    float _speed;       // Vitesse de deplacement

public:
    Entity() : _speed(1.f), _hitBoxSize(1) {}; // Constructeur
    Entity(const Entity & e);               // Copieur

    float getSpeed();                       // Retourne la vitesse
    float getHitBoxSize();                  // Retourne le rayon du hit box

    void setSpeed(float speed);             // Change la vitesse
    void setHitBoxSize(float size);         // Change le rayon du hitbox
};
