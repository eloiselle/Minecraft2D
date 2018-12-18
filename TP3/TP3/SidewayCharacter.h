/*****************************************************************************
File  : SidewayCharacter.h
Author: Anthony Cote
Date  : 2018-11-10
Goal  : Defini un personnage qui se deplace vue de côté
        dans le style des jeu de plateforme
******************************************************************************/

#pragma once
#include "pch.h"

#include "Character.h"

constexpr float MAX_FALL_SPEED = 8;
constexpr float GRAVITY = 0.5;
constexpr float JUMP_STRENGTH = 8;

class SidewayCharacter : public Character
{
private:
    bool _isLookingRight;   // Direction qu'il regarde
    float _upMomentum;      // Acceleration verticale; Positif == Ascendant

public:

    int getUpMomentum();    // Retourne la vitesse verticale ascendante
    int getDownMomentum();  // Retourne la vitesse verticale descendante
    bool isLookingToTheRight();
    bool isLookingToTheLeft();

    void lookToTheRight(bool isLookingToTheRight = true);  //
    void lookToTheLeft(bool isLookingToTheLeft = false);   //

    bool hasNoMomentum();   // Verifi si la position vertical est a 0
    bool isFalling();       // Est en train de tomber
    bool isRising();        // Est en train de monter

    void tryToJump();            // Commence un saut
    void startJump();
    void stopMomentum();    // Arrete le momentum
    void applyMomentum();   // Effectu les operations de routine
    void applyMomentum(int upMomentum); //

    void riseBy(int pixels);

    void fallBy(int pixels);
};
