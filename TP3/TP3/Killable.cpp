#pragma once
#include "Killable.h"

// Get
float Killable::getHp() { return _hp; }
float Killable::getHpMax() { return _hpMax; }
int Killable::getTimeOfDeath() { return _timeOfDeath; }

bool Killable::isAlive() { return _isAlive; }
bool Killable::isDead() { return !_isAlive; }

// Set
void Killable::setHp(int hp) { _hp = hp; }
void Killable::setHpMax(int hpMax) { _hpMax = hpMax; }
void Killable::isAlive(bool isAlive) { _isAlive = isAlive; }

void Killable::loseHp(int hpLost)
{
    _hp = MAX(0, _hp - hpLost);
}

// Fait mourir le personnage
void Killable::die(int timeOfDeath)
{
    if (_isAlive)
    {
        _isAlive = false;
        _timeOfDeath = timeOfDeath;
    }
}