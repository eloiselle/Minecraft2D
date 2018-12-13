#pragma once
#include "Weapon.h"

void Weapon::setUzi(int _frameRun)
{
    //_nameEquippedWeapon = "Uzi";
    _nbBulletsFired = 1;
    _accuracy = 60;
    _totalDelay = 3 * _delayMultiplier;
    _bulletSpeed = 1;
    _damage = 1;
    delayInit(_frameRun, _totalDelay);
}

void Weapon::setAssault(int _frameRun)
{
    //_nameEquippedWeapon = "Assault";
    _nbBulletsFired = 1;
    _accuracy = 1;
    _totalDelay = 10 * _delayMultiplier;
    _bulletSpeed = 1.5;
    _damage = 2;
    delayInit(_frameRun, _totalDelay);
}

void Weapon::setSniper(int _frameRun)
{
    //_nameEquippedWeapon = "Sniper";
    _nbBulletsFired = 1;
    _accuracy = 1;
    _totalDelay = 50 * _delayMultiplier;
    _bulletSpeed = 4;
    _damage = 4;
    delayInit(_frameRun, _totalDelay);
}

void Weapon::setShotgun(int _frameRun)
{
    //_nameEquippedWeapon = "Shotgun";
    _nbBulletsFired = 10;
    _accuracy = 60;
    _totalDelay = 30 * _delayMultiplier;
    _bulletSpeed = 1.5;
    _damage = 1;
    delayInit(_frameRun, _totalDelay);
}

void Weapon::setDestroyer(int _frameRun)
{
    //_nameEquippedWeapon = "What is this";
    _nbBulletsFired = 25;
    _accuracy = 90;
    _totalDelay = 1;
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