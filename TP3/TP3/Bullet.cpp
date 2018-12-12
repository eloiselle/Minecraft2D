#pragma once
#include "Bullet.h"

Bullet::Bullet(float x, float y, float speed)
{
	_hitBoxSize = 1;
	_speed = speed;
	setPositionExact(x, y);
}

// Deplace en fonction de la direction et de la vitesse
void Bullet::advance()
{
	move(getX() * _speed, getY() * _speed);
}

// Change l'angle en fonction de coords
void Bullet::aim(int x, int y, int accuracy)
{
	setAngleFromXY((x - _exactX) + (rand() % accuracy), (y - _exactY) + (rand() % accuracy));
}

// Change l'angle en fonction d'un objet
void Bullet::aim(MagnetPosition& mp)
{
	setAngleFromXY(
		mp.getExactX() - _exactX,
		mp.getExactY() - _exactY);
}

void Bullet::setSpeed(float speed)
{
	_speed = speed;
}

void Bullet::setDamage(int damage)
{
	_damage = damage;
}

float Bullet::getSpeed()
{
	return _speed;
}

int Bullet::getDamage()
{
	return _damage;
}