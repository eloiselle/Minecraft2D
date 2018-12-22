/*****************************************************************************
File  : Delay.h
Author: Anthony Cote
Date  : 2018-05-05
Goal  : Memorize un moment futur pour pouvoir comparer si c'est pret
******************************************************************************/
#pragma once
#include "pch.h"

class Delay
{
protected:
    int _totalDelay;    // Temps total entre chaque
    int _readyAt;       // Moment que ça va etre pret

public:
    Delay(int now = 0, int delay = 0)
        : _readyAt(now), _totalDelay(delay) {}; // Constructor

    void delayInit(int now, int delay);         // Remet le delai courant au maximum

    bool delayIsReady(int now)const;            // Si pret
    void delayReset(int now);                   // Remet le delai courant au maximum
};