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
            manageBoss();
            manageSphereShield();
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
}

void Game::manageMapExpansion()
{
    if (_player.getGridLine() >= _map.nbLine() - NB_LINE_BEFORE_EXPAND_MAP)
    {
        _map.addBottomLines(1);
        _map.randomizeLine(_map.nbLine() - 2);
        _map.fillLine(_map.nbLine() - 1, HARD_BLOCK);

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
}

// TODO supprimer si necessaire
double smartCos(double base, double slowness = 1, double amplitude = 1, double minimum = 0)
{
    return cos(base / slowness * PI) * amplitude + minimum;
}

void Game::manageBoss()
{
    if (_boss.isDead())
    {
        _appState = BOSS_KILLED;
        _pauseMessage.setString("Boss killed !! :)");
        _score += SCORE_BOSS_KILLED;
        return;
    }

    if (_boss.isWalking())
        _boss.move();   // Descente avec le joueur

    if (_boss.getGridLine() < _player.getGridLine() - 9)

    {
        _boss.setDirection(DOWN);
        _boss.startMoving();

        for (int c = 1; c < _map.nbCol() - 1; c++)
        {
            _map.at(_boss.getGridLine() + 3, c).setType(EMPTY_BLOCK);
        }


    }
    else
    {
        _boss.stopMoving();
    }

    moveBoss();     // Deplacement horizontal et legere variation verticale


}


void Game::manageFoes()
{
    if (_currentTool != SLOW_MO || !(_frameRun % SLOW_MO_EFFECT))
    {
        list<Crawler>::iterator c = _bats.begin();
        while (c != _bats.end())
        {
            manageOneFoe(c);
        }
    }
}

void Game::manageOneFoe(list<Crawler>::iterator& c)
{
    // Manage one foe
    if (c->isGridCentered()) // Pret a se deplacer
    {
        if (_frameRun % 24 == 12 && MUSIQUE)
        {
            _bats.back().play(_buffFoes);
        }
        c->stopMoving();
        tryToMoveInDirection(*c, static_cast<DIRECTION4>(rand() % 4));
    }

    if (c->isWalking())
        c->move();

    // Nettoyage de bat trop haut dans la map
    if (c->getExactY() < _boss.getExactY() - TILE_SIZE * 5)
        c = _bats.erase(c);
    else
        c++;

}

bool Game::toolIsAShooter()
{
    return (_currentTool != BUILD
        || _currentTool != SLOW_MO);
}



void Game::manageSphereShield()
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
}

void Game::manageBullets()
{


    // List of bullets

    list<Bullet>::iterator b = _bullets.begin();

    while (b != _bullets.end())
    {
        _bulletWillVanish = false;
        if (b->getHoming())
        {
            if (b->getTarget().isAlive())
                b->aim(b->getTarget());
            else
                b->setTarget(nullptr);
        }

        b->advance();

        if (isInMap(*b))
        {
            collisionBulletBlock(*b);
            collisionBulletFoes(*b);
        }
        else
            _bulletWillVanish = true;

        if (b->getExactY() < _boss.getExactY() - TILE_SIZE * 5)
            _bulletWillVanish = true;

        if (_bulletWillVanish)
            b = _bullets.erase(b);
        else
            b++;
    }
}
