/*****************************************************************************
File  : Boss.cpp
Author: Anthony Cote
Date  : 2018-12-17
Goal  : Defini les ennemis du joueur
******************************************************************************/

#pragma once
#include "pch.h"
#include "Crawler.h"

class Boss : public Crawler
{
public:
    Boss() {};               // Constructeur
    Boss(const Boss& boss);    // Copieur
};
