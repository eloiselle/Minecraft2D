#pragma once
#include "Game.h"

// Gere les animation du joueur
void Game::managePlayerAnimation()
{
	if (playerIsOnTheGround())
	{
		animIdle();
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
			animRight();

		else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
			animLeft();
	}
	else
		animAir();

}


// animations image lorsque ne bouge pas
void Game::animIdle()
{
    _animType = 0;

    if (_frameRun % 100 < 24)
    {
        _animFrame = 0;
    }
    else if (_frameRun % 100 < 49)
    {
        _animFrame = 1;
    }
    else if (_frameRun % 100 < 74)
    {
        _animFrame = 3;
    }
    else
    {
        _animFrame = 1;
    }
}

// animations de l'image déplacement à droite
void Game::animRight()
{
    _animType = 6;

    if (_frameRun % 49 < 7)
    {
        _animFrame = 0;
    }
    else if (_frameRun % 49 < 14)
    {
        _animFrame = 1;
    }
    else if (_frameRun % 49 < 21)
    {
        _animFrame = 2;
    }
    else if (_frameRun % 49 < 27)
    {
        _animFrame = 3;
    }
    else if (_frameRun % 49 < 34)
    {
        _animFrame = 3;
    }
    else if (_frameRun % 49 < 40)
    {
        _animFrame = 2;
    }
    else
    {
        _animFrame = 1;
    }
}

// animations de l'image déplacement à gauche
void Game::animLeft()
{
    if (_frameRun % 49 < 7)
    {
        _animFrame = 3;
        _animType = 8;
    }
    else if (_frameRun % 49 < 14)
    {
        _animFrame = 2;
        _animType = 8;
    }
    else if (_frameRun % 49 < 21)
    {
        _animFrame = 2;
        _animType = 8;
    }
    else if (_frameRun % 49 < 27)
    {
        _animFrame = 1;
        _animType = 8;
    }
    else if (_frameRun % 49 < 34)
    {
        _animFrame = 0;
        _animType = 8;
    }
    else if (_frameRun % 49 < 40)
    {
        _animFrame = 2;
        _animType = 7;
    }
    else
    {
        _animFrame = 3;
        _animType = 7;
    }
}

void Game::animAir()
{
    /* animation joueur tombe */
    if (_player.isFalling()
        && _map.isTraversable(
            _player.getExactX(),
            _player.getExactY() + TILE_SIZE))
    {
        _animFrame = 3;
        _animType = 2;
    }

    if (_player.isRising())
    {
        _animFrame = 1;
        _animType = 3;
    }
}