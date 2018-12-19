#pragma once
#include "Game.h"

void Game::handlePlayerDeath()
{
    _appState = GAME_OVER;
    _messageOnShader.setString(STR_GAME_OVER);
}

void Game::manageBossWeapon()
{
    if (_boss.delayIsReady(_frameRun))
    {
        for (size_t i = 0; i < NB_BOSS_BULLET; i++)
        {
            bossShootBullet();

            _bullets.back().rotate(ANGLE_BOSS_BULLET * i);
        }
        _boss.delayReset(_frameRun);
    }
}

void Game::bossShootBullet()
{
    _bullets.push_back(_boss.getBullet());

    _bullets.back().setPositionExact(
        _boss.getExactX(),
        _boss.getExactY());

    _bullets.back().aim(_player);

    if (MUSIQUE)
        _bullets.back().play(_buffBullet);
}

void Game::manageBossHeight()
{
    // Descente du boss
    if (_boss.isWalking())
        _boss.move();   // Descente avec le joueur

    if (_boss.getGridLine() < _player.getGridLine() - NB_LINE_BETWEEN_BOSS_AND_PLAYER)
        handleBossMovingDown();
    else
        _boss.stopMoving();
}

void Game::handleBossDeath()
{
    _score += SCORE_BOSS_KILLED;
    _appState = BOSS_KILLED;
    _messageOnShader.setString(STR_BOSS_KILLED);
}

void Game::handleBossMovingDown()
{
    _boss.setDirection(DOWN);
    _boss.startMoving();

    for (int c = 1; c < _map.nbCol() - 1; c++)
    {
        _map.at(_boss.getGridLine() + 3, c).setType(EMPTY_BLOCK);
    }
}

void Game::handleBatCreation()
{
    if (!(rand() % 3)) // Probabilite de creer une autre chauve souris
    {
        // Create new bat on last line
        int l = _map.nbLine() - 2;
        int c = (rand() % (_map.nbCol() - LINE_TO_CREATE_BATS)) + 3;
        _bats.push_back(Crawler());
        _bats.back().setPositionInGrid(c, l);
        _map.at(l, c).setType(EMPTY_BLOCK);
    }
}



void Game::shootWeapon()
{
    //Tirer le nombre de bullets
    if (toolIsAShooter() && _player.delayIsReady(_frameRun))
    {
        Character* target = nullptr;

        if (_currentTool == HOMING)
        {
            target = &_boss;// &c; // TODO bypass c
        }

        // Tirer le nombre de bullets
        for (int i = 0; i < _player.getWeaponNbBulletsFired(); i++)
            shootBullet(target);
    }
}

void Game::shootBullet(Character *target)
{
    _bullets.push_back(Bullet());

    if (MUSIQUE)
        _bullets.back().play(_buffBullet);

    _bullets.back().setPositionExact(
        _player.getExactX(),
        _player.getExactY() - HALF_TILE_SIZE);

    if (target == nullptr)
    {
        _bullets.back().aim(
            _mouseCoord.getPosition().x,
            _mouseCoord.getPosition().y,
            _player.getWeaponAccuracy());
    }

    _bullets.back().setSpeed(_player.getWeaponBulletSpeed());
    _bullets.back().setDamage(_player.getWeaponDamage());
    _player.delayReset(_frameRun);
}