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

// Gere les evenements globaux de l'application
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

void Game::inputActivatedInContinu()
{
	handleKeypress(); // TODO event allow to do it only once

	if (_appState == RUNNING)
	{
		if (_currentView == CAMERA && isMouseInWindow())
			handleMouseOnWindowBorders();

		if (Mouse::isButtonPressed(Mouse::Left) || Mouse::isButtonPressed(Mouse::Right))
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
		tryToMove(DOWN, _player);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) ||
		Keyboard::isKeyPressed(Keyboard::A))
	{
		_view[CAMERA].move(-ARROW_EXPLORE, 0);
		tryToMove(LEFT, _player);
	}
}

// ############################################################################
//              MOUSE
// ############################################################################

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
				shootBullet();
			}
		}
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			if (isMouseInMap() && _player.getIsBuildingEnabled())
				removeBlockAtMouse(c, l);
		}
	}
}

// Retourne si deux objet sont sue la meme case
bool Game::areOnTheSameSquare(MagnetPosition& mp1, MagnetPosition& mp2)
{
	return (mp1.getGridCol() == mp2.getGridCol()
		&& mp1.getGridLine() == mp2.getGridLine());
}

void Game::shootBullet()
{
	_bullets.push_back(Bullet());
	_bullets.back().setPosition(_player);
	_bullets.back().aim(_mouseCoord.getPosition().x, _mouseCoord.getPosition().y);
	_bullets.back().setLength(100);
	_bullets.back().setSpeed(_player.getWeaponBulletSpeed());
	_bullets.back().setDamage(_player.getWeaponDamage());
	_player.delayReset(_frameRun);
}

void Game::insertBlockAtMouse(int c, int l)
{
	if (_map.at(l, c).getType() == EMPTY_BLOCK)
	{
		_map.at(l, c) = SOFT_BLOCK;
	}
}

void Game::removeBlockAtMouse(int c, int l)
{
	if (_map.at(l, c).getType() == SOFT_BLOCK || _map.at(l, c).getType() == HARD_BLOCK)
	{
		_map.at(l, c) = EMPTY_BLOCK;
	}
}

// Push sur les bordures de l'ecran a l'aide d'un ratio de proximite de la bordure de window
void Game::handleMouseOnWindowBorders()
{
	// Horizontal
	if (Mouse::getPosition(_window).x < BORDURE)                                    // Gauche
	{
		_proximityRatio = (BORDURE - Mouse::getPosition(_window).x) / BORDURE;
		_view[CAMERA].move(-MOUSE_EXPLORE * _proximityRatio, 0);
	}
	else if (Mouse::getPosition(_window).x > DEF_WINDOW_WIDTH - BORDURE)            // Droite
	{
		_proximityRatio = (BORDURE - DEF_WINDOW_WIDTH + Mouse::getPosition(_window).x) / BORDURE;
		_view[CAMERA].move(MOUSE_EXPLORE * _proximityRatio, 0);
	}

	// Vertical
	if (Mouse::getPosition(_window).y < BORDURE)                                    // Haut
	{
		_proximityRatio = (BORDURE - Mouse::getPosition(_window).y) / BORDURE;
		_view[CAMERA].move(0, -MOUSE_EXPLORE * _proximityRatio);
	}
	else if (Mouse::getPosition(_window).y > DEF_WINDOW_HEIGHT - BORDURE)           // Bas
	{
		_proximityRatio = (BORDURE - DEF_WINDOW_HEIGHT + Mouse::getPosition(_window).y) / BORDURE;
		_view[CAMERA].move(0, MOUSE_EXPLORE * _proximityRatio);
	}
}

// Retourne si les coords sont a l'interieur de la map
bool Game::isInMap(int x, int y)const
{
	return(
		(x > 0) && (x < _map.nbCol()*TILE_SIZE) &&
		(y > 0) && (y < _map.nbLine()*TILE_SIZE));
}

// Retourne si la position est a l'interieur de la map
bool Game::isInMap(MagnetPosition & mp) const
{
	return(
		(mp.getExactX() > 0) && (mp.getExactX() < _map.nbCol()*TILE_SIZE) &&
		(mp.getExactY() > 0) && (mp.getExactY() < _map.nbLine()*TILE_SIZE));
}

// Retourne si la souris est a l'interieur de la map
bool Game::isMouseInMap()const
{
	return(
		(_mouseCoord.getPosition().x > 0) && (_mouseCoord.getPosition().x < _map.nbCol()*TILE_SIZE) &&
		(_mouseCoord.getPosition().y > 0) && (_mouseCoord.getPosition().y < _map.nbLine()*TILE_SIZE));
}

// Retourne si la souris est a l'interieur de la fenetre
bool Game::isMouseInWindow()const
{
	return(
		(Mouse::getPosition(_window).x > 0) && (Mouse::getPosition(_window).x < _window.getSize().x) &&
		(Mouse::getPosition(_window).y > 0) && (Mouse::getPosition(_window).y < _window.getSize().y));
}

// Retourne si les coords sont a l'interieur de la fenetre
bool Game::isInWindow(int x, int y)const
{
	return(
		(x > 0) && (x < _window.getSize().x) &&
		(y > 0) && (y < _window.getSize().y));
}

bool Game::isInWindow(MagnetPosition & mp) const
{
	return( // Not-tested : Can bug because of the view
		(mp.getExactX() > 0) && (mp.getExactX() < _window.getSize().x) &&
		(mp.getExactY() > 0) && (mp.getExactY() < _window.getSize().y));
}

// Retourne si l'objet est a l'interieur de la fenetre
bool Game::isInWindow(Vector2i& v)const
{
	return( // Not-tested : Can bug because of the view
		(v.x > 0) && (v.x < _window.getSize().x) &&
		(v.y > 0) && (v.y < _window.getSize().y));
}

// Trouve les coordonnes internes de la souris sans la view
void Game::updateViewlessMouseCoord()
{
	// Convertion de : Mouse.position => Generic.Coord => Mouse.Coord

	_mouseCoord.setPosition(
		_window.mapPixelToCoords(
			Mouse::getPosition(_window), _view[_currentView]));
}