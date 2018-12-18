/*****************************************************************************
File  : Boss.cpp
Author: Anthony Cote
Date  : 2018-12-17
Goal  : Represente un ennemi qui peux attaquer
        La classe fait seulement heriter de deux classes
******************************************************************************/

#pragma once
#include "pch.h"
#include "Crawler.h"
#include "Weapon.h"

class Boss : public Crawler, public Weapon
{
public: // La classe fait seulement heriter de deux classes
};
