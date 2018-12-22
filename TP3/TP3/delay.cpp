#pragma once
#include "Delay.h"

// Initializer
void Delay::init(int now, int delay)
{
    _totalDelay = delay;
    _readyAt = now + delay;
}

// Si c'est pret
bool Delay::isReady(int now)const
{
    return now >= _readyAt;
}

// Remet le "compteur" a zero
void Delay::reset(int now)
{
    _readyAt = now + _totalDelay;
}

int Delay::getTotalDelay()const { return _totalDelay; }

void Delay::setTotalDelay(int totalDelay) { _totalDelay = totalDelay; }
