/*****************************************************************************
File  : TopDownCharacter.h
Author: Anthony Cote
Date  : 2018-04-23
Goal  : Defini un personnage vu de dessus qui peux se deplacer selon x et y
******************************************************************************/

#pragma once
#include "pch.h"

#include "Character.h"
#include "Direction.h"

class TopDownCharacter : public Character
{
protected:
    DIRECTION4 _direction;                  // Direction ou il regarde
    bool _isWalking;                        // Si en train de marcher
public:
    TopDownCharacter() : _direction(DOWN), _isWalking(false) {}; // Constructeur
    void init();                            // Initialize

    // Get
    DIRECTION4 getDirection();              // Retourne la direction
    bool isWalking()const;                  // Retourne s'il est en train de se deplacer automatiquement

    // Set
    void setDirection(DIRECTION4 dir);      // Change la direction du personnage
    void isWalking(bool isWalking);         // Change s'il est en train de se deplacer automatiquement

    // Move
    void move();                            // Micro déplacement du personnage
    void move(DIRECTION4 dir);              // Deplace dans une direction
    void move(pixel_t plusX, pixel_t plusY);// Micro déplacement du personnage

};
