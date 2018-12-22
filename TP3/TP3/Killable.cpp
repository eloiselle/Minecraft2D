#pragma once
#include "Killable.h"

// Get
int Killable::getHp()const { return _hp; }
int Killable::getHpMax()const { return _hpMax; }

bool Killable::isAlive()const { return _hp > 0; }
bool Killable::isDead()const { return _hp <= 0; }

bool Killable::isVulnerable(int now) const
{
    return _vulnerability.isReady(now);
}

// Set
void Killable::setHp(int hp) { _hp = hp; }
void Killable::setHpMax(int hpMax) { _hpMax = hpMax; }

// Methods
void Killable::loseHp(int hpLost) { _hp = MAX(0, _hp - hpLost); }
void Killable::becomeInvulnerable(int now) { _vulnerability.reset(now); }
void Killable::die() { _hp = 0; }
void Killable::refillHp() { _hp = _hpMax; }