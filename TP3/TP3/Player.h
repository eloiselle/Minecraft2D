/*****************************************************************************
File  : Player.cpp
Author: Anthony Cote
Date  : 2018-12-01
Goal  : Avatar du joueur controllable avec le clavier/souris
        La classe sert seulement a hériter de deux autres classes
******************************************************************************/

#pragma once
#include "pch.h"

#include "Weapon.h"
#include "SidewayCharacter.h"

using namespace sf;

class Player : public SidewayCharacter, public Weapon
{
protected:

public:
    Player() {};    // Constructeur
};
