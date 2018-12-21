/*****************************************************************************
File  : Weapon.h
Author: Anthony Cote
Date  : 2018-05-05
Goal  : Gere les armes et leurs proprietes
******************************************************************************/
#pragma once

#include "pch.h"

#include "Bullet.h"
#include "Delay.h"

const enum TOOL {
    BUILD = 0,      // Mode de construction et destruction de block
    UZI,            // Arme a repetition tres rapide mais imprecise
    ASSAULT,        // Arme a repetition rapide et precise
    SNIPER,         // Arme lente mais puissante
    SHOT_GUN,       // Arme qui lance plusieurs balles
    BULLET_HELL,    // Arme furieuse
    SLOW_MO,        // Ralenti les ennemis
    HOMING,         // Balle qui vise automatiquement le boss
    SPHERE_SHIELD,  // Bouclier de balles
    BOSS            //
    // Handgun      // Arme faible pour compenser le manque offensif de Slow-mo et Sphere shield
};         // Bullet de l'attaque sonique du boss
const string TOOL_NAMES[10] = {
    "Build", "Uzi", "Assault", "Sniper", "Shotgun",
    "BulletHell", "Slow-Mo", "Homing", "Sphere Shield", "Boss" };

class Weapon : public Delay
{
protected:

    bool _friendly = false;     // Alliee du joueur
    int _delayMultiplier = 1;	// Multiplicateur sur le délai
    int _nbBulletsFired;        // Nombres de balles lancee par l'arme
    int _inaccuracy;			// Détermine une variation dans _angle
    float _bulletSpeed;			// Vitesse des bullets
    float _damage;				// Degats occasionnee par l'arme

public:
    // Change weapon
    void setWeapon(TOOL tool, int _frameRun);
    void setNoWeapon(int _frameRun);
    void setHandGun(int _frameRun);
    void setUzi(int _frameRun);
    void setAssault(int _frameRun);
    void setSniper(int _frameRun);
    void setShotgun(int _framerun);
    void setBulletHell(int _frameRun);
    void setHoming(int _frameRun);
    void setWeaponBoss(int _frameRun);
    void setCustom(
        float inaccuracy, int rateOfFire, float bulletSpeed,
        float damageMultiplier, int frameRun);

    // Get property
    int getWeaponNbBulletsFired()const;
    int getWeaponAccuracy()const;
    int getWeaponRateOfFire()const;
    float getWeaponBulletSpeed()const;
    float getWeaponDamage()const;
    Bullet getBullet()const;

    // Set property
    void setWeaponNbBulletsFired(int);
    void setWeaponAccuracy(int);
    void setWeaponRateOfFire(int);
    void setWeaponBulletSpeed(float);
    void setWeaponDamage(float);

};
