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
private:
	int _damage;
	float _speed;

public:
	Bullet() {};                                    // Constructeur sans parametres
	Bullet(float x, float y, float speed = 1.f);    // Constructeur avec parametres

	void advance();          // Se deplace dans la direction du vecteur d'angle
	void aim(int x, int y, int accuracy);           // Change l'angle en fonction de coord et une donné pour rendre aléatoire
	void aim(MagnetPosition & mp);                  // Change l'angle an fonction de un objet

	void setSpeed(float);
	void setDamage(int);

	float getSpeed();
	int getDamage();
};
