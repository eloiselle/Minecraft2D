#pragma once
#include "Weapon.h"

void Weapon::setWeapon(TOOL tool, int _frameRun)
{
    switch (tool)
    {
    case BUILD:             setNoWeapon(_frameRun);         break;
    case UZI:               setUzi(_frameRun);              break;
    case ASSAULT:           setAssault(_frameRun);          break;
    case SNIPER:            setSniper(_frameRun);           break;
    case SHOT_GUN:          setShotgun(_frameRun);          break;
    case BULLET_HELL:       setBulletHell(_frameRun);       break;
    case SLOW_MO:           setNoWeapon(_frameRun);         break;
    case HOMING:			setHoming(_frameRun);			break;
    case SPHERE_SHIELD:     setNoWeapon(_frameRun);         break;
    default:
        break;
    }
}

void Weapon::setNoWeapon(int _frameRun)
{
    _nbBulletsFired = 0;
    _accuracy = 1;
    _totalDelay = 60 * _delayMultiplier;
    _bulletSpeed = 1;
    _damage = 1;
    delayInit(_frameRun, _totalDelay);
}

void Weapon::setUzi(int _frameRun)
{
    _nbBulletsFired = 1;
    _accuracy = 60;
    _totalDelay = 3 * _delayMultiplier;
    _bulletSpeed = 1;
    _damage = 1;
    delayInit(_frameRun, _totalDelay);
}

void Weapon::setAssault(int _frameRun)
{
    _nbBulletsFired = 1;
    _accuracy = 1;
    _totalDelay = 10 * _delayMultiplier;
    _bulletSpeed = 1.5;
    _damage = 2;
    delayInit(_frameRun, _totalDelay);
}

void Weapon::setSniper(int _frameRun)
{
    _nbBulletsFired = 1;
    _accuracy = 1;
    _totalDelay = 50 * _delayMultiplier;
    _bulletSpeed = 4;
    _damage = 4;
    delayInit(_frameRun, _totalDelay);
}

void Weapon::setShotgun(int _frameRun)
{
    _nbBulletsFired = 10;
    _accuracy = 60;
    _totalDelay = 30 * _delayMultiplier;
    _bulletSpeed = 1.5;
    _damage = 1;
    delayInit(_frameRun, _totalDelay);
}

void Weapon::setBulletHell(int _frameRun)
{
    _nbBulletsFired = 25;
    _accuracy = 360;
    _totalDelay = 1;
    _bulletSpeed = 1;
    _damage = 1;
    delayInit(_frameRun, _totalDelay);
}

void Weapon::setHoming(int _frameRun)
{
    _nbBulletsFired = 1;
    _accuracy = 60;
    _totalDelay = 3 * _delayMultiplier;
    _bulletSpeed = 1;
    _damage = 1;
    delayInit(_frameRun, _totalDelay);
}

void Weapon::setCustom(float accuracy, int rateOfFire, float bulletSpeed, float damageMultiplier, int _frameRun)
{
    _accuracy = accuracy;
    _totalDelay = rateOfFire * _delayMultiplier;
    _bulletSpeed = bulletSpeed;
    _damage = damageMultiplier;
    delayInit(_frameRun, _totalDelay);
}

//string Weapon::getWeaponName() { return _nameEquippedWeapon; }
int Weapon::getWeaponNbBulletsFired() { return _nbBulletsFired; }
int Weapon::getWeaponAccuracy() { return _accuracy; }
int Weapon::getWeaponRateOfFire() { return _totalDelay; }
float Weapon::getWeaponBulletSpeed() { return _bulletSpeed; }
float Weapon::getWeaponDamage() { return _damage; }

//void Weapon::setWeaponName(string name) { _nameEquippedWeapon = name; }
void Weapon::setWeaponNbBulletsFired(int nb) { _nbBulletsFired = nb; }
void Weapon::setWeaponAccuracy(int accuracy) { _accuracy = accuracy; }
void Weapon::setWeaponRateOfFire(int rateOfFire) { _totalDelay = rateOfFire; }
void Weapon::setWeaponBulletSpeed(float bulletSpeed) { _bulletSpeed = bulletSpeed; }
void Weapon::setWeaponDamage(float damageMultiplier) { _damage = damageMultiplier; }