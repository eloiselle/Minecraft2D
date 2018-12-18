#pragma once
#include "Killable.h"

// Get
int Killable::getHp() { return _hp; }
int Killable::getHpMax() { return _hpMax; }

bool Killable::isAlive() { return _hp > 0; }
bool Killable::isDead() { return _hp <= 0; }

// Set
void Killable::setHp(int hp) { _hp = hp; }
void Killable::setHpMax(int hpMax) { _hpMax = hpMax; }

// Methods
void Killable::loseHp(int hpLost) { _hp = MAX(0, _hp - hpLost); }
void Killable::die() { _hp = 0; }
void Killable::refillHp() { _hp = _hpMax; }