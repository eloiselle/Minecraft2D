/***********************************************************************
File  : Nameable.h
Author: Anthony Cote
Date  : 2018-12-01
Goal  : Classe pour contenir un utiliser un nom
***********************************************************************/
#pragma once
#include "pch.h"

using namespace std;

class Nameable
{
protected: 
    char *_name;        // Pointeur sur le nom
public:
    Nameable();
    ~Nameable();

    void clearName();                   // Vide le nom
    void setName(const char* name);     // Modifie le nom 
    const char* getName()const;         // Retourne le nom


};

