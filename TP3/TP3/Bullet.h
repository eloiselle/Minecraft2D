/*****************************************************************************
File  : Bullet.cpp
Author: Anthony Cote
Date  : 2017-01-01
Goal  : Projectiles
******************************************************************************/

#pragma once
#include "pch.h"
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "VectorAngle.h"
#include "Character.h"

class Bullet : public Entity, public VectorAngle
{
private:
    bool _friendly = true;      // Si l'arme est alliee ou ennemie
    int _damage;                // Degats fait par l'arme

    Character* _target;         // Cible pour homing

    sf::Sound _sound;           // Son
    sf::SoundBuffer _buffer;    // Buffer de son

    float getLength()const override { return 0.f; };// desactive pour etre remplacer par getSpeed()
    void setLength(float) override {};              // desactive pour etre remplacer par setSpeed()
    void setLength(float, float) override {};       // desactive pour etre remplacer par setSpeed()

public:
    Bullet() { _target = nullptr; };                // Constructeur sans parametres
    Bullet(float x, float y, float speed = 1.f);    // Constructeur avec parametres

    void advance();									// Se deplace dans la direction du vecteur d'angle
    void aim(int x, int y, int accuracy);           // Change l'angle en fonction de coord et une donné pour rendre aléatoire
    void aim(Character & ch);                       // Change l'angle an fonction de un objet

    void setSpeed(float);                           // Change la vitesse de deplacement
    void setDamage(int);                            // Change les degats lors de collisions
    void setTarget(Character * ch);                 // Change la cible pour Homing
    void setFriendly(bool);                         // Change si c'est une balle alliee ou ennemie

    float getSpeed()const;                          // Retourne la vitesse de deplacement
    int getDamage()const;                           // Retourne le nombre de degat
    Character& getTarget()const;                    // Retourne la cible
    bool isHoming()const;                           // Retourne si c'est homing
    bool isFriendly()const;                         // Retourne si c'est une balle alliee

    void play(sf::SoundBuffer & buff, float vol);              // Joue un effet sonore
};
