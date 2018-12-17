#pragma once
#include "Delay.h"

// Initializer
void Delay::delayInit(int now, int delay)
{
	_readyAt = now + delay;
}

// Si c'est pret
bool Delay::delayIsReady(int now)
{
	return _readyAt < now;
}

// Remet le "compteur" a zero
void Delay::delayReset(int now)
{
	_readyAt = now + _totalDelay;
}