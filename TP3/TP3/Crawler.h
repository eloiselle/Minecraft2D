/*****************************************************************************
File  : Crawler.h
Author: Anthony Cote
Date  : 2018-04-23
Goal  : Personnage controlé par l'ordinateur qui se deplace aleatoirement
******************************************************************************/

#pragma once
#include "pch.h"

#include <SFML/Audio.hpp>

#include "TopDownCharacter.h"
#include "ResizableMap.hpp"

enum AI_Move { NONE, RANDOM, RANDOM_NOT_BACK, BACK_AND_FORTH, ALWAYS_LEFT, ALWAYS_RIGHT };
enum AI_Frequency { EVERY_MEET_WALL, EVERY_SQUARE, EVERY_SECOND };

class Crawler : public TopDownCharacter
{
protected:
    AI_Move _aiMove;                        // Quel genre de decision le robot prend
    AI_Frequency _aiFreq;                   // Quand le robot prend des decisions
    bool _isControllable = true;            // Si le crawler est controllable
    int _frameLeftBeforeControl;            // Nombre de frame avant que le crawler puisse etre controller

    sf::Sound _sound;                       // Son
    sf::SoundBuffer _buffer;                // Buffer de son
public:
    Crawler();  // Constructeur sans parametres
    Crawler(int x, int y, AI_Move ai, AI_Frequency decisionAI); // Constructeur avec parametres

    // Gets

    // Sets
    void init(int x, int y, AI_Move Random, AI_Frequency WhenCannotWalk); // Re-set tout
    void setAI(AI_Move ai, AI_Frequency decisionAI); // Change l'intelligence artificielle
    void move();                            // se deplace de 1 vers l'avant
    void move(int x, int y);                // se deplace selon les coordonnees
    void startMoving();                     // commence un deplacement automatique
    void stopMoving();                      // termine un deplacement automatique
    void turnLeft();                        // change de direction anticlockwise
    void turnRight();                       // change de direction clockwise

    void playSound(sf::SoundBuffer & buff, float vol); // Joue un effet sonore

    // Operations
    //void chooseNextMove(FixedGrid& map);    // Utilise l'AI pour change de strategy
    //void update(int time, FixedGrid& map);  // effectu les operation de routine


};
