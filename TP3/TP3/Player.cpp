#pragma once
#include "Player.h"

Player::Player()
{
	setUzi();
	_buildingEnabled = true;
	_weaponEnabled = false;
}

void Player::changeMode()
{
	_buildingEnabled = !_buildingEnabled;
	_weaponEnabled = !_weaponEnabled;
}

bool Player::getIsBuildingEnabled()
{
	return _buildingEnabled;
}

bool Player::getIsWeaponEnabled()
{
	return _weaponEnabled;
}