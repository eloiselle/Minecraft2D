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
            manageMapExpansion();

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
    manageWeapon();

}

void Game::manageMapExpansion()
{
    if (_player.getGridLine() >= _map.nbLine() - NB_LINE_BEFORE_EXPAND_MAP)
    {
        _map.addBottomLines(1);
        _map.randomizeLine(_map.nbLine() - 1);

        if (!(rand() % 3)) // Probabilite de creer une autre chauve souris
        {
            // Create new bat on last line
            int l = _map.nbLine() - 2;
            int c = (rand() % (_map.nbCol() - 5)) + 3;
            _bats.push_back(Crawler());
            _bats.back().setPositionInGrid(c, l);
            _map.at(l, c).set(EMPTY_BLOCK);
        }
    }
}

void Game::manageWeapon()
{
    if (_player.delayIsReady(_frameRun))
    {
        _player.delayReset(_frameRun);
    }
}

void Game::manageFoes()
{
    if (_currentTool != SLOW_MO || !(_frameRun % SLOW_MO_EFFECT))
    {
        for (Crawler& c : _bats)
        {
            // Manage one foe
            if (c.isGridCentered()) // Pret a se deplacer
            {
                c.stopMoving();
                tryToMoveRandomDirection(c);
            }

            if (c.isWalking())
            {
                c.move();
            }
        }
    }

}

bool Game::toolIsAShooter()
{
    return (_currentTool != BUILD
        || _currentTool != SLOW_MO);
}

void Game::tryToMoveRandomDirection(Crawler& c)
{
    DIRECTION4 randDir = static_cast<DIRECTION4>(rand() % 4);

    if (_map.isTraversable(
        c.getExactX() + D4[randDir][X] * TILE_SIZE,
        c.getExactY() + D4[randDir][Y] * TILE_SIZE))
    {
        c.setDirection(randDir);
        c.startMoving();
    }
}

// TODO supprimer si necessaire
double smartCos(double base, double slowness = 1, double amplitude = 1, double minimum = 0)
{
    return cos(base / slowness * PI) * amplitude + minimum;
}

void Game::manageBullets()
{
    // Shield
    for (size_t i = 0; i < NB_SHIELD; i++)
    {
        // Yoyo : Example d'utilisation de VectorAngle
        //_yoyoString.setLength(smartCos(_frameRun, 20, 20, 5));
        _shieldVA[i].rotate(3);
        _shieldSphere[i].setPositionExact(
            _player.getExactX() + _shieldVA[i].getX(),
            _player.getExactY() + _shieldVA[i].getY() - PLAYER_HEIGHT / 2);

    }

    // List of bullets
    bool willVanish; //
    list<Bullet>::iterator b = _bullets.begin();

    while (b != _bullets.end())
    {
        willVanish = false;

        b->advance();

        if (isInMap(*b))
        {
            if (!_map.isTraversable(*b))
            {
                willVanish = true;
            }

            if (_map.isDestructible(*b))
            {
                // Collision entre bullet et block
                int l = b->getGridLine();
                int c = b->getGridCol();
                _map.at(l, c).loseHp(1);
                
                if (_map.at(l, c).getHp() <= 0)
                    _map.at(l, c) = EMPTY_BLOCK;

                willVanish = true;
            }

            list<Crawler>::iterator c = _bats.begin();
            while (c != _bats.end())
            {
                if (areOnTheSameSquare(*b, *c))
                {
                    willVanish = true;
                    c = _bats.erase(c);
                }
                else
                {
                    c++;
                }
            }
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
    float newExactY = _player.getExactY() - _player.getUpMomentum() - PLAYER_HEIGHT;
    return !_map.isTraversable(_player.getExactX(), newExactY);
}

bool Game::playerIsLanding()
{
    float newExactY = _player.getExactY() + _player.getDownMomentum();
    return !_map.isTraversable(_player.getExactX(), newExactY);
}

// Regarde si on peu se déplacer a la nouvelle position // Version Sideway
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

// Regarde si on peu se déplacer a la nouvelle position // Version Top-down
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
