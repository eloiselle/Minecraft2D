/*****************************************************************************
File  : Killable.h
Author: Anthony Cote
Date  : 2018-05-05
Goal  : Permet d'etre tuable avec des hp
******************************************************************************/
#pragma once

#include "pch.h"
#include "Delay.h"

constexpr int DEFAULT_SUPER_ARMOR_FRAME = 60;

class Killable
{
protected:
    int _hp;    // Nombre de points de vie actuel
    int _hpMax; // Nombre de points de vie maximum
    Delay _vulnerability;

public:
    Killable() : _hp(5), _hpMax(5), _vulnerability(0, DEFAULT_SUPER_ARMOR_FRAME) {};  // Constructeur

    int getHp()const;                   // Retourne les HP
    int getHpMax()const;                // Retourne le nombre de HP Max
    bool isAlive()const;                // Retourne si est en vie
    bool isDead()const;                 // Retourne si est mort
    bool isVulnerable(int now)const;    // Retourne si est mort

    void setHp(int hp);                 // Change les HP
    void setHpMax(int hpMax);           // Change le nombre de HP max

    void loseHp(int hpLost);            // Fait perdre des HP
    void becomeInvulnerable(int now);   // Fait perdre des HP
    void die();                         // Le personnage meurt
    void refillHp();                    // Remet les hp au maximum
};
