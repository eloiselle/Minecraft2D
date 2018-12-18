#pragma once
#include "SidewayCharacter.h"

// Récupere la vitesse de déplacement du saut
int SidewayCharacter::getUpMomentum()const { return _upMomentum; }
int SidewayCharacter::getDownMomentum()const { return -_upMomentum; }
bool SidewayCharacter::isLookingToTheRight()const { return _isLookingRight; }
bool SidewayCharacter::isLookingToTheLeft()const { return !_isLookingRight; }
bool SidewayCharacter::isMoving() const { return _isMoving; }

bool SidewayCharacter::hasNoMomentum()const { return _upMomentum == 0; }
bool SidewayCharacter::isFalling()const { return _upMomentum <= 0; }
bool SidewayCharacter::isRising()const { return _upMomentum > 0; }

void SidewayCharacter::isMoving(bool isMoving) { _isMoving = isMoving; }
void SidewayCharacter::lookToTheRight(bool isLookingRight) { _isLookingRight = isLookingRight; }
void SidewayCharacter::lookToTheLeft(bool isLookingLeft) { _isLookingRight = !isLookingLeft; }

void SidewayCharacter::stopMomentum() { _upMomentum = 0; }
void SidewayCharacter::applyMomentum() { applyMomentum(_upMomentum); }

void SidewayCharacter::riseBy(int pixels) { setPositionExact(_exactX, _exactY - pixels); }
void SidewayCharacter::fallBy(int pixels) { setPositionExact(_exactX, _exactY + pixels); }

// Essaye de faire sauter le personnage
void SidewayCharacter::tryToJump()
{
    if (hasNoMomentum())
        startJump();
}

// Fait que le personnage saute dans les airs
void SidewayCharacter::startJump()
{
    _upMomentum = JUMP_STRENGTH;
    riseBy(_upMomentum);
}

// Met a jour le personnage
void SidewayCharacter::applyMomentum(int upMomentum)
{
    if (isRising())
    {
        int pixToRise = MIN(_upMomentum, MAX_FALL_SPEED);
        riseBy(pixToRise);
    }
    else
    {
        int pixToFall = -MAX(_upMomentum, -MAX_FALL_SPEED);
        fallBy(pixToFall);
    }
    _upMomentum -= GRAVITY;
}