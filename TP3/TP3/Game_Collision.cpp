#pragma once
#include "Game.h"

void Game::collisionBulletBlock(Bullet& b)
{
    if (!_map.isTraversable(b))
    {
        _bulletWillVanish = true;
    }

    if (_map.isDestructible(b))
    {
        int l = b.getGridLine();
        int c = b.getGridCol();
        _map.at(l, c).loseHp(1); // TODO utiliser les damage de bullet

        if (_map.at(l, c).getHp() <= 0)
            _map.at(l, c) = EMPTY_BLOCK;
        _bulletWillVanish = true;

        _score += SCORE_BLOCK;
    }
}

void Game::collisionBulletFoes(Bullet& b)
{
    // Chauve souris
    list<Crawler>::iterator c = _bats.begin();
    while (c != _bats.end())
    {
        if (areOnTheSameSquare(b, *c))
        {
            _bulletWillVanish = true;
            c = _bats.erase(c);
            _score += SCORE_BAT;
        }
        else
        {
            c++;
        }
    }
    // Boss

    if (areOnTheSameSquare(b, _boss))
    {
        _bulletWillVanish = true;
        _boss.loseHp(1);// TODO mettre les damage du bullet
    }
}