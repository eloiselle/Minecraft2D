#pragma once
#include "Game.h"

void Game::handlePlayerDeath()
{
    _appState = GAME_OVER;
    _messageOnShader.setString(STR_GAME_OVER);
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
        int c = (rand() % (_map.nbCol() - 5)) + 3;
        _bats.push_back(Crawler());
        _bats.back().setPositionInGrid(c, l);
        _map.at(l, c).setType(EMPTY_BLOCK);
    }
}
