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
    case SLOW_MO:           setHandGun(_frameRun);         break;
    case HOMING:			setHoming(_frameRun);			break;
    case SPHERE_SHIELD:     setHandGun(_frameRun);         break;
    default:
        break;
    }
}

void Weapon::setNoWeapon(int _frameRun)
{
    _nbBulletsFired = 0;
    _inaccuracy = 1;
    int totalDelay = 999999999999 * _delayMultiplier;
    _bulletSpeed = 999999999999;
    _damage = 0;
    _bulletSize = 0;
    _delay.init(_frameRun, totalDelay);
}

void Weapon::setHandGun(int _frameRun)
{
    _nbBulletsFired = 1;
    _inaccuracy = 20;
    int totalDelay = 30 * _delayMultiplier;
    _bulletSpeed = 3;
    _damage = 4;
    _bulletSize = 4;
    _delay.init(_frameRun, totalDelay);
}


void Weapon::setUzi(int _frameRun)
{
    _nbBulletsFired = 1;
    _inaccuracy = 60;
    int totalDelay = 1 * _delayMultiplier;
    _bulletSpeed = 3;
    _damage = 2;
    _bulletSize = 2;
    _delay.init(_frameRun, totalDelay);
}

void Weapon::setAssault(int _frameRun)
{
    _nbBulletsFired = 1;
    _inaccuracy = 1;
    int totalDelay = 10 * _delayMultiplier;
    _bulletSpeed = 3;
    _damage = 20;
    _bulletSize = 20;
    _delay.init(_frameRun, totalDelay);
}

void Weapon::setSniper(int _frameRun)
{
    _nbBulletsFired = 1;
    _inaccuracy = 1;
    int totalDelay = 50 * _delayMultiplier;
    _bulletSpeed = 5;
    _damage = 40;
    _bulletSize = 40;
    _delay.init(_frameRun, totalDelay);
}

void Weapon::setShotgun(int _frameRun)
{
    _nbBulletsFired = 10;
    _inaccuracy = 300;
    int totalDelay = 30 * _delayMultiplier;
    _bulletSpeed = 3;
    _damage = 10;
    _bulletSize = 10;
    _delay.init(_frameRun, totalDelay);
}

void Weapon::setBulletHell(int _frameRun)
{
    _nbBulletsFired = 25;
    _inaccuracy = 360;
    int totalDelay = 1;
    _bulletSpeed = 4;
    _damage = 1;
    _bulletSize = 1;
    _delay.init(_frameRun, totalDelay);
}

void Weapon::setHoming(int _frameRun)
{
    _nbBulletsFired = 1;
    _inaccuracy = 1;
    int totalDelay = 150 * _delayMultiplier;
    _bulletSpeed = 2;
    _damage = 50;
    _bulletSize = 50;
    _delay.init(_frameRun, totalDelay);
}

void Weapon::setWeaponBoss(int _frameRun)
{
    _friendly = false;
    _nbBulletsFired = 1;
    _inaccuracy = 1;
    int totalDelay = 300 * _delayMultiplier;
    _bulletSpeed = 2;
    _damage = 1;
    _bulletSize = 2;
    _delay.init(_frameRun, totalDelay);
}

void Weapon::setCustom(float accuracy, int rateOfFire, float bulletSpeed, float damageMultiplier, int _frameRun)
{
    // TODO : gerer tous les parametres possibles
    _inaccuracy = accuracy;
    int totalDelay = rateOfFire * _delayMultiplier;
    _bulletSpeed = bulletSpeed;
    _damage = damageMultiplier;
    _delay.init(_frameRun, totalDelay);
}


// Property
int Weapon::getWeaponNbBulletsFired()const { return _nbBulletsFired; }
int Weapon::getWeaponInaccuracy()const { return _inaccuracy; }
int Weapon::getWeaponRateOfFire()const { return _delay.getTotalDelay(); }
float Weapon::getWeaponBulletSpeed()const { return _bulletSpeed; }
float Weapon::getWeaponDamage()const { return _damage; }
int Weapon::getBulletSize()const { return _bulletSize; };
Delay Weapon::getDelay()const { return _delay; }

Bullet Weapon::getBullet()const
{
    Bullet b;
    b.setFriendly(_friendly);
    b.setDamage(_damage);
    b.setSpeed(_bulletSpeed);
    b.setFriendly(_friendly);
    b.setHitBoxSize(_bulletSize);
    return b;
}

void Weapon::setWeaponNbBulletsFired(int nb) { _nbBulletsFired = nb; }
void Weapon::setWeaponInaccuracy(int accuracy) { _inaccuracy = accuracy; }
void Weapon::setWeaponRateOfFire(int rateOfFire) { _delay.setTotalDelay(rateOfFire); }
void Weapon::setWeaponBulletSpeed(float bulletSpeed) { _bulletSpeed = bulletSpeed; }
void Weapon::setWeaponDamage(float damageMultiplier) { _damage = damageMultiplier; }
void Weapon::setBulletSize(int size) { _bulletSize = size; }
void Weapon::setDelay(Delay & delay) { _delay = delay; }

void Weapon::resetDelay(int now) { _delay.reset(now); }
bool Weapon::delayIsReady(int now) const { return _delay.isReady(now); }
