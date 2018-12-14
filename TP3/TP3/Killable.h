/*****************************************************************************
File  : Killable.h
Author: Anthony Cote
Date  : 2018-05-05
Goal  : Permet d'etre tuable avec des hp
******************************************************************************/
#pragma once

#include "pch.h"

class Killable
{
protected:
    int _hp;
    int _hpMax;
    bool _isAlive;
    unsigned int _timeOfDeath;

public:
    Killable() : _hp(5), _hpMax(5), _isAlive(true), _timeOfDeath(0) {}; // Constructeur

    float getHp();                 // Retourne les HP
    float getHpMax();              // Retourne le nombre de HP Max
    int getTimeOfDeath();          // Retourne le moment de la mort

    void setHp(int hp);            // Change les HP
    void setHpMax(int hpMax);      // Change le nombre de HP max

    void loseHp(int hpLost);       // Fait perdre des HP
    void die(int timeOfDeath);     // Le personnage meurt

    bool isAlive();                // Retourne si est en vie
    bool isDead();                 // Retourne si est mort
};
