#pragma once
#include "Game.h"

// Boucle principale
void Game::mainLoop()
{
    while (_window.isOpen())
    {
        inputActivatedOnlyTheFirstTime();
        inputActivatedInContinu();

        if (_appState == RUNNING)
        {
            managePlayer();
            manageFoes();
            manageBullets();

            _frameRun++;
        }

        // Update
        drawWindow();
        _frameTotal++;
    }

    quitApplication();
}

void Game::managePlayer()
{
    managePlayerJump();
}

void Game::manageFoes()
{
    // Manage one foe
    if (_spider.isGridCentered()) // Pret a se deplacer
    {
        DIR8 randDirection = static_cast<DIR8>(rand() % 8 * 2);

        if (_map.isTraversable(
            _spider.getExactX() + D8_x[randDirection] * TILE_SIZE,
            _spider.getExactY() + D8_y[randDirection] * TILE_SIZE))
        {
            _spider.setDirection(randDirection);
            _spider.startMoving();
        }
    }
    
    if (_spider.isWalking())
    {
        _spider.move();
    }
}

double smartCos(double base, double slowness = 1, double amplitude = 1, double minimum = 0)
{
    return cos(base / slowness * PI) * amplitude + minimum;
}

void Game::manageBullets()
{
    // Yoyo : Example d'utilisation de VectorAngle
    _yoyoString.setLength(smartCos(_frameRun, 20, 20, 5));
    _yoyoString.rotate(30);
    _yoyo.setPositionExact(
        _player.getExactX() + _yoyoString.getX(),
        _player.getExactY() + _yoyoString.getY());

    // List of bullets
    bool willVanish; //
    list<Bullet>::iterator b = _bullets.begin();

    while (b != _bullets.end())
    {
        willVanish = false;

        b->advance();

        if (isInMap(*b))
        {
            //if (_map.isDestructible(*b))
            //{
            //    //softBlock.affectHealth(-1);
            //    //_map.at(b->getGridLine(), b->getGridCol()) == TRAIL;
            //    willVanish = true;
            //}

            //if (!_map.isTraversable(*b))
            //{
            //    willVanish = true;
            //}
        }
        else
            willVanish = true;

        if (willVanish)
            b = _bullets.erase(b);
        else
            b++;
    }
}

void Game::managePlayerJump()
{
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
    float newExactY = _player.getExactY() - _player.getUpMomentum();
    return !_map.isTraversable(_player.getExactX(), newExactY);
}

bool Game::playerIsLanding()
{
    float newExactY = _player.getExactY() + _player.getDownMomentum();
    return !_map.isTraversable(_player.getExactX(), newExactY);
}

// Regarde si on peu se déplacer a la nouvelle position // Version Sideway
void Game::tryToMove(int dir, SidewayCharacter& character)
{
    float newExactX = character.getExactX() + D8_x[dir] * character.getSpeed();

    int nextGridX = (newExactX) / TILE_SIZE;

    bool onCurrentGridX = nextGridX == character.getGridCol();

    // Si reste sur la meme case
    if (onCurrentGridX)
    {
        character.setPositionExact(newExactX, character.getExactY());
    }
    else // Si essaye de changer de case
    {
        // Essaye de se deplacer horizontalement
        if (_map.isTraversable(newExactX, character.getExactY()))
            character.setPositionExact(newExactX, character.getExactY());
    }
}

// Regarde si on peu se déplacer a la nouvelle position // Version Top-down
void Game::tryToMove(DIR8 dir, TopDownCharacter& character)
{
    float newExactX = character.getExactX() + D8_x[dir] * character.getSpeed();
    float newExactY = character.getExactY() + D8_y[dir] * character.getSpeed();

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