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
	setAngleFromXY((x - _exactX) - (accuracy / 2) + (rand() % accuracy), (y - _exactY) - (accuracy / 2) + (rand() % accuracy));
}

// Change l'angle en fonction d'un objet
void Bullet::aim(Character& ch)
{
	setAngleFromXY(
		ch.getExactX() - _exactX,
		ch.getExactY() - _exactY);
}

void Bullet::setSpeed(float speed) { _speed = speed; }
void Bullet::setDamage(int damage) { _damage = damage; }
void Bullet::setTarget(Character * ch) { _target = ch; }

float Bullet::getSpeed() { return _speed; }
int Bullet::getDamage() { return _damage; }
Character& Bullet::getTarget() { return *_target; }
bool Bullet::getHoming() { return _target != nullptr; }

void Bullet::play(sf::SoundBuffer & buff)
{
	//_buffer.loadFromFile("pew.wav");
	_sound.setBuffer(buff);
	_sound.play();
}