#pragma once
#include "Game.h"

void Game::managePlayerJump()
{
    _animFrame = 0;
    _animType = 0;
    if (playerHitTheCeiling())
    {
        _player.fallBy(MAX_FALL_SPEED + 1);
    }
    else
    {
        _player.applyMomentum(pixelsToRise() - pixelsToFall());
    }

    if (pixelsBeforeBottomBorder() > 0) // In air
    {
        if (_player.isFalling())
        {
            _animFrame = 3;
            _animType = 2;
        }
        if (_player.isRising() && playerHitTheCeiling())
        {
            _player.stopMomentum();
        }
        if (_player.isFalling() && playerIsLanding())
        {
            _player.stopMomentum();
        }
    }

    //_debug +=
    //    " BBorder " + to_string(pixelsBeforeBottomBorder()) + "\r\n" +
    //    " TBorder " + to_string(pixelsBeforeTopBorder()) + "\r\n" +
    //    " HitLand " + to_string(playerIsLanding()) + "\r\n" +
    //    " HitCeil " + to_string(playerHitTheCeiling()) + "\r\n" +
    //    " pToFall " + to_string(pixelsToFall()) + "\r\n" +
    //    " pToRise " + to_string(pixelsToRise()) + "\r\n" +
    //    " isFall " + to_string(_player.isFalling()) + "\r\n" +
    //    " isRise " + to_string(_player.isRising()) + "\r\n" +
    //    " upMomentum " + to_string(_player.getUpMomentum()) + "\r\n" +
    //    " x " + to_string((int)_player.getExactX()) + "\r\n" +
    //    " y " + to_string((int)_player.getExactY()) + "\r\n" +
    //    "  ";
}

// END OF MANAGERS

bool Game::playerIsOnTheGround()
{
    return (pixelsBeforeBottomBorder() == 1
        && !_map.isTraversable(_player.getExactX(), _player.getExactY() + TILE_SIZE));
}

int Game::pixelsBeforeTopBorder()
{
    return -(_player.getGridLine() * TILE_SIZE - _player.getExactY());
}

int Game::pixelsBeforeBottomBorder()
{
    return _player.getGridLine() * TILE_SIZE - _player.getExactY() + 32;
}

int Game::pixelsToRise()
{
    return MAX(0, MIN(pixelsBeforeTopBorder(), _player.getUpMomentum()));
}

int Game::pixelsToFall()
{
    return MAX(0, MIN(pixelsBeforeBottomBorder(), _player.getDownMomentum()));
}

bool Game::playerHitTheCeiling()
{
    float newExactY = _player.getExactY() - _player.getUpMomentum() - PLAYER_HEIGHT;
    return !_map.isTraversable(_player.getExactX(), newExactY);
}

bool Game::playerIsLanding()
{
    float newExactY = _player.getExactY() + _player.getDownMomentum();
    return !_map.isTraversable(_player.getExactX(), newExactY);
}

// Regarde si on peu se deplacer a la nouvelle position // Version Sideway
void Game::tryToMove(DIRECTION4 dir, SidewayCharacter& character)
{
    float testExactX;
    float newExactX = character.getExactX() + D4[dir][X] * character.getSpeed();

    if (dir == LEFT)
        testExactX = newExactX - PLAYER_FOOT;
    else if (dir == RIGHT)
        testExactX = newExactX + PLAYER_FOOT;
    else testExactX = newExactX;

    int nextGridX = testExactX / TILE_SIZE;

    bool onCurrentGridX = nextGridX == character.getGridCol();

    // Si reste sur la meme case
    if (onCurrentGridX)
    {
        character.setPositionExact(newExactX, character.getExactY());
    }
    else // Si essaye de changer de case
    {
        // Essaye de se deplacer horizontalement
        if (_map.isTraversable(testExactX, character.getExactY()))
            character.setPositionExact(newExactX, character.getExactY());
    }
}

// Regarde si on peu se deplacer a la nouvelle position // Version Top-down
void Game::tryToMove(DIRECTION4 dir, TopDownCharacter& character)
{
    float newExactX = character.getExactX() + D4[dir][X] * character.getSpeed();
    float newExactY = character.getExactY() + D4[dir][Y] * character.getSpeed();

    int nextGridX = (newExactX) / TILE_SIZE;
    int nextGridY = (newExactY) / TILE_SIZE;

    bool onCurrentGridX = nextGridX == character.getGridCol();
    bool onCurrentGridY = nextGridY == character.getGridLine();

    // Si reste sur la meme case
    if (onCurrentGridX && onCurrentGridY)
    {
        character.setPositionExact(newExactX, newExactY);
    }
    else // Si essaye de changer de case
    {
        // Essaye de se deplacer horizontalement
        if (_map.isTraversable(newExactX, character.getExactY()))
            character.setPositionExact(newExactX, character.getExactY());

        // Essaye de se deplacer verticalement
        if (_map.isTraversable(character.getExactX(), newExactY))
            character.setPositionExact(character.getExactX(), newExactY);
    }

    character.setDirection(dir);
}

void Game::tryToMoveInDirection(Crawler& c, DIRECTION4 dir)
{
    if (_map.isTraversable(
        c.getExactX() + D4[dir][X] * TILE_SIZE,
        c.getExactY() + D4[dir][Y] * TILE_SIZE))
    {
        c.setDirection(dir);
        c.startMoving();
    }
}

void Game::moveBoss()
{
    // deplacement du boss
    float round = cos(_frameRun / 100.f);//smartCos(_frameRun, 100, 10, 12) / 2;
    float minimum = TILE_SIZE * 2;
    float maximum = MAP_WIDTH_PIXELS - TILE_SIZE * 2;
    float amplitude = (maximum - minimum) / 2;
    float x = amplitude * round + amplitude + minimum;
    float y = cos(_frameRun / 16.f);// *TILE_SIZE + (TILE_SIZE * 3);

    _boss.setPositionExact(x, y + _boss.getExactY());
}