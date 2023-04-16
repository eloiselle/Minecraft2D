#pragma once
#include "Game.h"

void Game::handlePlayerDeath()
{
    _appState = GAME_OVER;
    _messageOnShader.setString(STR_GAME_OVER);
    _messageOnShader.setCharacterSize(100);
}

void Game::handleBossDeath()
{
    _score += SCORE_BOSS_KILLED;
    _appState = BOSS_KILLED;
    _messageOnShader.setString(STR_BOSS_KILLED);
    _messageOnShader.setCharacterSize(100);
}

void Game::manageBossWeapon()
{
    if (_boss.delayIsReady(_frameFoes))
    {

        for (size_t i = 0; i < NB_BOSS_BULLET; i++)
        {
            bossShootBullet();

            list<Bullet>::iterator b;
            b = _bullets.end()--;

            b->rotate(ANGLE_BOSS_BULLET * i);
        }
        _boss.resetDelay(_frameFoes);
    }
}


void Game::bossShootBullet()
{
    list<Bullet>::iterator b;

    b = _bullets.push_back(_boss.getBullet());

    b->setPositionExact(
        _boss.getExactX(),
        _boss.getExactY());


    b->aim(_player);

    if (_isAudioActivated)
        b->play(_buffBullet, _volume/10);

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



void Game::handleBossMovingDown()
{
    _boss.setDirection(DOWN);
    _boss.startMoving();

    _map.fillLine(_boss.getGridLine() + 3, EMPTY_BLOCK);
}

void Game::handleBatCreation()
{
    if (!(rand() % 3)) // Probabilite de creer une autre chauve souris
    {
        // Create a new bat on the "last" line
        createBatAt(
            _map.nbLine() - 2,
            (rand() % (_map.nbCol() - LINE_TO_CREATE_BATS)) + 3);
    }
}

void Game::createBatAt(int l, int c)
{
    list<Crawler>::iterator b;
    b = _bats.push_back(Crawler());
    b->setPositionInGrid(c, l);
    _map.at(l, c).setType(EMPTY_BLOCK);
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
    list<Bullet>::iterator b;
    b = _bullets.end();

    b = _bullets.insert(b, _player.getBullet());


    if (_isAudioActivated)
        b->play(_buffBullet, _volume/4);

    b->setPositionExact(
        _player.getExactX(),
        _player.getExactY() - HALF_TILE_SIZE);

    if (target == nullptr)
    {
        b->aim(
            _mouseCoord.getPosition().x,
            _mouseCoord.getPosition().y,
            _player.getWeaponInaccuracy());
    }

    //b->setSpeed(_player.getWeaponBulletSpeed());
    //b->setDamage(_player.getWeaponDamage());

    _player.resetDelay(_frameRun);
}
