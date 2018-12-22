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

        if (b.isFriendly())
        {
            _map.at(l, c).loseHp(b.getDamage());
            _score += SCORE_BLOCK;
        }
        else
            _map.at(l, c).die();

        if (_map.at(l, c).isDead())
            _map.at(l, c) = EMPTY_BLOCK;

        _bulletWillVanish = true;
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

        _boss.loseHp(b.getDamage());
    }
}

void Game::collisionBulletPlayer(Bullet& b)
{
    if (areOnTheSameSquare(b, _player))
    {
        _bulletWillVanish = true;

        if (_player.isVulnerable(_frameRun))
        {
            _player.loseHp(b.getDamage());
            _player.becomeInvulnerable(_frameRun);
        }
    }
}