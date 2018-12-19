#pragma once
#include "Game.h"

// Retourne si deux objet sont sue la meme case
bool Game::areOnTheSameSquare(MagnetPosition& mp1, MagnetPosition& mp2)
{
	return (mp1.getGridCol() == mp2.getGridCol()
		&& mp1.getGridLine() == mp2.getGridLine());
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
	if (_map.at(l, c).getType() == SOFT_BLOCK
		|| _map.at(l, c).getType() == HARD_BLOCK)
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

// Détermine la distance entre 2 positions
float Game::distanceBetweenMP(MagnetPosition & mp1, MagnetPosition & mp2)const
{
	return abs(sqrt(
		(mp1.getExactY() - mp2.getExactY()) * (mp1.getExactY() - mp2.getExactY())
		+ (mp1.getExactX() - mp2.getExactX()) * (mp1.getExactX() - mp2.getExactX())));
}