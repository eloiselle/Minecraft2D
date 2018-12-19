#pragma once
#include "Bullet.h"

Bullet::Bullet(float x, float y, float speed)
{
    _hitBoxSize = 1;
    _length = speed;
    setPositionExact(x, y);
}

// Deplace en fonction de la direction et de la vitesse
void Bullet::advance()
{
    move(getX() * _length, getY() * _length);
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

void Bullet::setSpeed(float speed) { _length = speed; }
void Bullet::setDamage(int damage) { _damage = damage; }
void Bullet::setFriendly(bool friendly) { _friendly = friendly; }
void Bullet::setHoming(bool isHoming) { _isHoming = isHoming; }

float Bullet::getSpeed()const { return _length; }
int Bullet::getDamage()const { return _damage; }
bool Bullet::isHoming()const { return _isHoming; }
bool Bullet::isFriendly()const { return _friendly; }

void Bullet::play(sf::SoundBuffer & buff)
{
    //_buffer.loadFromFile("pew.wav");
    _sound.setBuffer(buff);
    _sound.play();
}