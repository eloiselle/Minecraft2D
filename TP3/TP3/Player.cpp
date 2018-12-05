#pragma once
#include "Player.h"

Player::Player()
{
	setUzi();
	_isBuilding = true;
	_isWeapon = false;
}

void Player::changeMode()
{
	_isBuilding = !_isBuilding;
	_isWeapon = !_isWeapon;
}

bool Player::getIsBuildingEquipped()
{
	return _isBuilding;
}

bool Player::getIsWeaponEquipped()
{
	return _isWeapon;
}