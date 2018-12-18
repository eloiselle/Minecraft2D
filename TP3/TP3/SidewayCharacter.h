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

constexpr float MAX_FALL_SPEED = 8;     // Vitesse maximale de descente
constexpr float GRAVITY = 0.5;          // Diminution periodique de la force verticale
constexpr float JUMP_STRENGTH = 8;      // Force de depart du saut

class SidewayCharacter : public Character
{
private:
    bool _isLookingRight;               // Direction qu'il regarde
    bool _isMoving;                     // S'il est en train de bouger
    float _upMomentum;                  // Acceleration verticale; Positif == Ascendant

public:
    int getUpMomentum()const;           // Retourne la vitesse verticale ascendante
    int getDownMomentum()const;         // Retourne la vitesse verticale descendante
    bool isLookingToTheRight()const;    // Retourne s'il regarde vers la droite
    bool isLookingToTheLeft()const;     // Retourne s'il regarde vers la gauche
    bool isMoving()const;               // Retourne s'il est en train de bouger

    void isMoving(bool isMoving);       // Change si il est en train de bouger
    void lookToTheRight(bool isLookingToTheRight = true);  // Change la direction vers lequel il regarde
    void lookToTheLeft(bool isLookingToTheLeft = true);    // Change la direction vers lequel il regarde

    bool hasNoMomentum()const;          // Verifi si la position vertical est a 0
    bool isFalling()const;              // Est en train de tomber
    bool isRising()const;               // Est en train de monter

    void tryToJump();                   // Commence un saut
    void startJump();
    void stopMomentum();                // Arrete le momentum
    void applyMomentum();               // Effectu les operations de routine
    void applyMomentum(int upMomentum); // Applique un certain momentum

    void riseBy(int pixels);            // Deplace de exactement p pixels vers le haut
    void fallBy(int pixels);            // Deplace de exactement p pixels vers le bas
};
