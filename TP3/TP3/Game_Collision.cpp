#pragma once
#include "Game.h"

// Retourne si deux objet sont sue la meme case
bool Game::areOnTheSameSquare(MagnetPosition& mp1, MagnetPosition& mp2)
{
    return (mp1.getGridCol() == mp2.getGridCol()
        && mp1.getGridLine() == mp2.getGridLine());
}

// Détermine la distance entre 2 positions
float Game::distanceBetweenMP(MagnetPosition & mp1, MagnetPosition & mp2)
{
    return VectorAngle::lengthOfOffset(
        mp1.getExactY() - mp2.getExactY(),
        mp1.getExactX() - mp2.getExactX());
}

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

bool Game::isBulletHit(Bullet& b, MagnetPosition& target, int bonusDistance)
{
    return distanceBetweenMP(b, target) < b.getDamage() + bonusDistance;
}

void Game::collisionBulletFoes(Bullet& b)
{
    // Chauve souris
    list<Crawler>::iterator c = _bats.begin();
    while (c != _bats.end())
    {
        if (isBulletHit(b, *c))
        {
            _bulletWillVanish = true;
            c = _bats.erase(c);
            _score += SCORE_BAT;
        }
        else 
            c++;
    }

    // Boss
    if (isBulletHit(b, _boss))
    {
        _bulletWillVanish = true;
        _boss.loseHp(b.getDamage());
    }
}

void Game::collisionBulletPlayer(Bullet& b)
{
    if (isBulletHit(b, _player, PLAYER_FOOT))
    {
        if (_player.isVulnerable(_frameRun))
        {
            _player.loseHp(b.getDamage());
            _player.becomeInvulnerable(_frameRun);
        }

        _bulletWillVanish = true;
    }
}