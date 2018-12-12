#pragma once
#include "Delay.h"

// Initializer
void Delay::init(int now, int delay)
{
	_readyAt = now + delay;
}

// Si c'est pret
bool Delay::isReady(int now)
{
	return _readyAt < now;
}

// Remet le "compteur" a zero
void Delay::reset(int now)
{
	_readyAt = now + _totalDelay;
}