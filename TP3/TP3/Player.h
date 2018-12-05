/*****************************************************************************
File  : Player.cpp
Author: Anthony Cote
Date  : 2017-01-01
Goal  : Avatar du joueur controllable avec le clavier/souris
******************************************************************************/

#pragma once
#include "pch.h"

#include "Weapon.h"
#include "SidewayCharacter.h"

using namespace sf;

class Player : public SidewayCharacter, public Weapon
{
protected:

	bool _isBuilding;
	bool _isWeapon;

public:

	Player();

	void changeMode();
	bool getIsBuildingEquipped();
	bool getIsWeaponEquipped();
};
