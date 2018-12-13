#pragma once
#include "Game.h"

// ############################################################################
//              EVENTS
// ############################################################################

// Quitte l'application
void Game::quitApplication()
{
	_window.close();
	exit(1);
}

// Gere les input qui doivent etre active une seule fois par repetition
void Game::inputActivatedOnlyTheFirstTime()
{
	// Window Controls
	while (_window.pollEvent(_event))
	{
		switch (_event.type)
		{
		case Event::Closed:
			quitApplication();
			break;
		case Event::Resized:
			handleResizeWindow();
			break;
		case Event::LostFocus:
			_appState = PAUSED;
			break;
		case Event::KeyPressed:
			if (_event.key.code == Keyboard::BackSpace)
				init();
			if (_event.key.code == Keyboard::P)
				handlePausing();
			if (_event.key.code == Keyboard::T
				&& isMouseInWindow()
				&& !areOnTheSameSquare(_mouseMagnet, _player))
				_player.setPosition(_mouseMagnet);
		}

		if (_appState == RUNNING)
		{
			if (_event.type == Event::MouseWheelMoved)
				handleMouseWheelMoved();
		}
	}
}

// Gere les input qui doivent etre activer en continu
void Game::inputActivatedInContinu()
{
	handleKeypress(); // TODO event allow to do it only once

	if (_appState == RUNNING)
	{
		if (_currentView == CAMERA && isMouseInWindow())
			handleMouseOnWindowBorders();

		if (Mouse::isButtonPressed(Mouse::Left) 
            || Mouse::isButtonPressed(Mouse::Right))
			handleMouseButtonPressed();
	}

	updateViewlessMouseCoord();
}

// Evalue si l'etat de pause est change
void Game::handlePausing()
{
	if (_appState == PAUSED)
		_appState = RUNNING;
	else if (_appState == RUNNING)
		_appState = PAUSED;
}

// Gere quand la fenetre est redimensionner
View& Game::handleResizeWindow()
{
	Vector2f size = static_cast<Vector2f>(_window.getSize());

	// Garatin une taille Minimum de la fenetre
	size.x = MAX(size.x, MIN_WINDOW_WIDTH);
	size.y = MAX(size.y, MIN_WINDOW_HEIGHT);

	// Apply possible size changes
	_window.setSize(static_cast<Vector2u>(size));

	// Reset view
	_view[NEUTRAL] = View(FloatRect(0.f, 0.f, size.x, size.y));
	_view[CAMERA] = View(FloatRect(0.f, 0.f, size.x, size.y));
	_view[FOLLOW] = View(FloatRect(0.f, 0.f, size.x, size.y));
	_view[FOLLOW_Y] = View(FloatRect(0.f, 0.f, size.x, size.y));

	return _view[NEUTRAL];
}

// Observe l'etat des touches de claviers
void Game::handleKeypress()
{
	if (_appState == RUNNING)
	{
		handleArrowKeys();

		// Game Controls
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			_yoyo.setPosition(_player);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		quitApplication();

	if (Keyboard::isKeyPressed(Keyboard::Num0))
		initWorldMap("Labyrinthe1.txt");

	// Change weapon
	if (Keyboard::isKeyPressed(Keyboard::Num1))
		_player.setBuildingEnabled();

	if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		_player.setWeaponEnabled();
		_player.setUzi(_frameRun);
	}
	if (Keyboard::isKeyPressed(Keyboard::Num3))
	{
		_player.setWeaponEnabled();
		_player.setAssault(_frameRun);
	}
	if (Keyboard::isKeyPressed(Keyboard::Num4))
	{
		_player.setWeaponEnabled();
		_player.setSniper(_frameRun);
	}
	if (Keyboard::isKeyPressed(Keyboard::Num5))
	{
		_player.setWeaponEnabled();
		_player.setShotgun(_frameRun);
	}
	if (Keyboard::isKeyPressed(Keyboard::Num6))
	{
		_player.setWeaponEnabled();
		_player.setDestroyer(_frameRun);
	}
}

void Game::handleArrowKeys()
{
	// Keyboard Arrow
	if (Keyboard::isKeyPressed(Keyboard::Up) ||
		Keyboard::isKeyPressed(Keyboard::W) ||
		Keyboard::isKeyPressed(Keyboard::Space))
	{
		_view[CAMERA].move(0, -ARROW_EXPLORE);

		if (playerIsOnTheGround())
			_player.startJump();
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) ||
		Keyboard::isKeyPressed(Keyboard::D))
	{
		_view[CAMERA].move(ARROW_EXPLORE, 0);
		tryToMove(RIGHT, _player);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) ||
		Keyboard::isKeyPressed(Keyboard::S))
	{
		_view[CAMERA].move(0, ARROW_EXPLORE);
		//tryToMove(DOWN, _player);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) ||
		Keyboard::isKeyPressed(Keyboard::A))
	{
		_view[CAMERA].move(-ARROW_EXPLORE, 0);
		tryToMove(LEFT, _player);
	}
}

// Gere quand la roulette de souris a changer
void Game::handleMouseWheelMoved()
{
	if (_currentView != NULL_VIEW)
		_view[_currentView].zoom(1 - (_event.mouseWheel.delta * 0.125f));
}

// Gere quand un bouton de souris est clicker
void Game::handleMouseButtonPressed()
{
	if (isMouseInWindow()
		&& !areOnTheSameSquare(_mouseMagnet, _player))
	{
		int c = _mouseCoord.getPosition().x / TILE_SIZE;
		int l = _mouseCoord.getPosition().y / TILE_SIZE;

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (isMouseInMap() && _player.getIsBuildingEnabled())
				insertBlockAtMouse(c, l);

			if (_player.getIsWeaponEnabled() && _player.delayIsReady(_frameRun))
			{
				for (int i = 0; i < _player.getWeaponNbBulletsFired(); i++)
				{
				shootBullet();
				}
			}
		}
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			if (isMouseInMap() && _player.getIsBuildingEnabled())
				removeBlockAtMouse(c, l);
		}
	}
}

void Game::shootBullet()
{
	_bullets.push_back(Bullet());
	_bullets.back().setPositionExact(
		_player.getExactX(), 
		_player.getExactY() - HALF_TILE_SIZE);
	_bullets.back().aim(
		_mouseCoord.getPosition().x,
		_mouseCoord.getPosition().y, 
		_player.getWeaponAccuracy());
	_bullets.back().setLength(10);
	_bullets.back().setSpeed(_player.getWeaponBulletSpeed());
	_bullets.back().setDamage(_player.getWeaponDamage());
	_player.delayReset(_frameRun);

	if (MUSIQUE)
		_soundBullet.play();
}
