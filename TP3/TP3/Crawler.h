/*****************************************************************************
File  : Robot.h
Author: Anthony Cote
Date  : 2018-04-23
Goal  : Personnage controlé par l'ordinateur
        a l'origine c'est des ennemis dans Bomberman
******************************************************************************/

#pragma once
#include "pch.h"

#include "TopDownCharacter.h"
#include "Foe.h"
#include "ResizableMap.hpp"

enum AI_Move { NONE, RANDOM, RANDOM_NOT_BACK, BACK_AND_FORTH, ALWAYS_LEFT, ALWAYS_RIGHT };
enum AI_Frequency { EVERY_MEET_WALL, EVERY_SQUARE, EVERY_SECOND };

class Crawler : public TopDownCharacter, public Foe
{
public:
    Crawler();
    Crawler(int x, int y, AI_Move ai, AI_Frequency decisionAI);

    // Gets

    // Sets
    void init(int x, int y, AI_Move Random, AI_Frequency WhenCannotWalk); // Re-set tout
    void setAI(AI_Move ai, AI_Frequency decisionAI); // Change l'intelligence artificielle
    void move();                            // se deplace de 1 vers l'avant
    void startMoving();
    void turnLeft();                        // change de direction anticlockwise
    void turnRight();                       // change de direction clockwise

    // Operations
    //void chooseNextMove(FixedGrid& map);    // Utilise l'AI pour change de strategy
    //void update(int time, FixedGrid& map);  // effectu les operation de routine

protected:
    AI_Move _aiMove;                        // Quel genre de decision le robot prend
    AI_Frequency _aiFreq;                   // Quand le robot prend des decisions
    bool _isControllable = true;
    int _frameLeftBeforeControl;
};
