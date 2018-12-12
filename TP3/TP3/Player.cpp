#pragma once
#include "Player.h"

Player::Player()
{
	setUzi();
	_buildingEnabled = true;
	_weaponEnabled = false;
}

bool Player::getIsBuildingEnabled()
{
	return _buildingEnabled;
}

bool Player::getIsWeaponEnabled()
{
	return _weaponEnabled;
}

void Player::setBuildingEnabled()
{
	_buildingEnabled = true;
	_weaponEnabled = false;
}

void Player::setWeaponEnabled()
{
	_buildingEnabled = false;
	_weaponEnabled = true;
}