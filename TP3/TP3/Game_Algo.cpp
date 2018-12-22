#pragma once
#include "Game.h"

// Boucle principale
void Game::run()
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

	if (_player.isDead())
		handlePlayerDeath();

	managePlayerJump();

	if (areOnTheSameSquare(_player, _boss))
		_player.loseHp(1);


	managePlayerAnimation();
}



void Game::manageMapExpansion()
{
	if (_player.getGridLine() >= _map.nbLine() - NB_LINE_BEFORE_EXPAND_MAP)
	{
		_map.addBottomLines(1);
		_map.randomizeLine(_map.nbLine() - 2);
		_map.fillLine(_map.nbLine() - 1, HARD_BLOCK);

		handleBatCreation();
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
		handleBossDeath();
		return;
	}

	manageBossHeight();
	moveBoss();     // Deplacement horizontal et legere variation verticale


	manageBossWeapon();
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
		_frameFoes++;
	}
}

void Game::manageOneFoe(list<Crawler>::iterator& c)
{
	// Manage one foe
	if (c->isGridCentered()) // Pret a se deplacer
	{
		if (_frameRun % 24 == 12 && _isAudioActivated)
		{
		   c->playSound(_buffFoes);
		}
		c->stopMoving();
		tryToMoveInDirection(*c, static_cast<DIRECTION4>(rand() % 4));
	}

	if (c->isWalking())
		c->move();

	if (areOnTheSameSquare(_player, *c))
	{
		_player.loseHp(1);
		c = _bats.erase(c);
	}
	else if (c->getExactY() < _boss.getExactY() - TILE_SIZE * 5)// Nettoyage de bat trop haut dans la map
		c = _bats.erase(c);
	else
		c++;

}

bool Game::toolIsAShooter()const
{
    // Shield et Slow-Mo utilisent le handgun donc ce sont des shooter
    return _currentTool != BUILD;
}



void Game::manageSphereShield()
{
	if (_currentTool != SPHERE_SHIELD)
		return;

	for (size_t i = 0; i < _shield.size(); i++)
	{
		_bulletWillVanish = false;
		_shieldVA[i].rotate(ANGLE_ROTATION_SHIELD);
		_shield[i].setPositionExact(
			_player.getExactX() + _shieldVA[i].getX(),
			_player.getExactY() + _shieldVA[i].getY() - PLAYER_HEIGHT * 0.75);

		collisionBulletFoes(_shield[i]);
		//collisionBulletBlock(_shieldSphere[i]); // Presentement detruit par HARD_BLOCK

		if (_bulletWillVanish)
		{
			_shield.erase(_shield.begin() + i);
			_shieldVA.erase(_shieldVA.begin() + i);
		}
	}
}

void Game::manageBullets()
{


	// List of bullets

	list<Bullet>::iterator b = _bullets.begin();

	while (b != _bullets.end())
	{
		_bulletWillVanish = false;
		if (_currentTool == HOMING && b->isFriendly())//b->isHoming()) // TODO bypass
		{
			b->aim(_boss);
		}

		b->advance();

		if (isInMap(*b))
		{
			collisionBulletBlock(*b);
			if (b->isFriendly())
			{
				collisionBulletFoes(*b);
			}
			else
			{
				collisionBulletPlayer(*b);
			}

		}
		else
			_bulletWillVanish = true;

		if (b->getExactY() < _boss.getExactY() - TILE_SIZE * NB_LINE_DELETE_BULLET_ABOVE_BOSS)
			_bulletWillVanish = true;

		if (_bulletWillVanish)
			b = _bullets.erase(b);
		else
			b++;
	}
}
