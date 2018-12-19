/***********************************************************************
File  : Shield.h
Author: Emile Loiselle
Date  : 2018-12-18
Goal  : Classe pour representer le bouclier

***********************************************************************/

#pragma once
#include "Bullet.h"
#include "VectorAngle.h"

class Shield
{
private:
	list<Bullet> _shieldSphere;    // Tourne a l'entour de _player
	list<VectorAngle> _shieldVA;   // Distance entre _shieldSphere et _player
public:
};
