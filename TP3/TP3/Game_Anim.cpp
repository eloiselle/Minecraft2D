#pragma once
#include "Game.h"

// Gere les animation du joueur
void Game::managePlayerAnimation()
{
    if (playerIsOnTheGround())
    {

        if (_player.isMoving())
        {
            if (_player.isLookingToTheRight())
                animRight();
            else
                animLeft();
        }
        else
            animIdle();
    }
    else
        animAir();
}

// animations image lorsque ne bouge pas
void Game::animIdle()
{
    _animType = _player.isLookingToTheRight(); // index bool : 0 ou 1
    _animFrame = (_frameRun / 10) % 4;

}

// animations de l'image déplacement à droite
void Game::animRight()
{
    _animType = WALK_RIGHT;
    _animFrame = (_frameRun / 10) % 4;

}

// animations de l'image déplacement à gauche
void Game::animLeft()
{
    _animType = WALK_LEFT;
    _animFrame = (_frameRun / 10) % 4;

}

void Game::animAir()
{
    _animType = AIR;

    /* animation joueur tombe */
    if (_player.isFalling()
        && _map.isTraversable(
            _player.getExactX(),
            _player.getExactY() + TILE_SIZE))
    {
        _animFrame = 2 + _player.isLookingToTheRight(); // 2 == offset
    }

    if (_player.isRising())
    {
        _animFrame = _player.isLookingToTheRight();
    }
}