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
#include "Position.h"
#include "VectorAngle.h"
#include "Character.h"

class Bullet : public Entity, public VectorAngle
{
private:
    bool _friendly = true;
    int _damage;

    Character* _target;

    sf::Sound _sound;
    sf::SoundBuffer _buffer;

    float getLength()const override { return 0.f; };// Override pour utiliser getSpeed()
    void setLength(float) override {};              // Override pour utiliser setSpeed()
    void setLength(float, float) override {};       // Override pour utiliser setSpeed()

public:
    Bullet() { _target = nullptr; };                // Constructeur sans parametres
    Bullet(float x, float y, float speed = 1.f);    // Constructeur avec parametres

    void advance();									// Se deplace dans la direction du vecteur d'angle
    void aim(int x, int y, int accuracy);           // Change l'angle en fonction de coord et une donn� pour rendre al�atoire
    void aim(Character & ch);                       // Change l'angle an fonction de un objet

    void setSpeed(float);
    void setDamage(int);
    void setTarget(Character * ch);
    void setFriendly(bool);

    float getSpeed();
    int getDamage();
    Character& getTarget();
    bool getHoming();
    bool isFriendly();

    void play(sf::SoundBuffer & buff);
};
