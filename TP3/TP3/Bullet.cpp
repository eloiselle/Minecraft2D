#include "Bullet.h"

Bullet::Bullet(float x, float y, float speed)
{
    _hitBoxSize = 1;
    _speed = speed;
    setPositionExact(x, y);
}

// Deplace en fonction de la direction et de la vitesse
void Bullet::advance(float multiplicator)
{
    move( getX() * multiplicator, getY() * multiplicator);
}

// Change l'angle en fonction de coords
void Bullet::aim(int x, int y)
{
    setAngleFromXY(x - _exactX, y - _exactY);
}

// Change l'angle en fonction d'un objet
void Bullet::aim(MagnetPosition& mp)
{
    setAngleFromXY(
        mp.getExactX() - _exactX,
        mp.getExactY() - _exactY);
}
