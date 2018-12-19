#include "Game.h"

// ############################################################################
//              DRAW
// ############################################################################

// Affiche les graphiques a l'ecran
void Game::drawWindow()
{
	_window.clear();

	updateWindowTitle();
	drawGrid();
	updateViews();

	drawPlayer();
	drawFoes();
	drawBullets();
	drawShield();
	drawMovableGui();

	drawThingsDirectlyOnTheScreen();

	_window.display();
}

// Met a jour les view
void Game::updateViews()
{
	_view[FOLLOW].setCenter(
		_player.getExactX(),
		_player.getExactY());

	_view[FOLLOW_Y].setCenter(
		_map.nbCol() * TILE_SIZE / 2,
		_player.getExactY());
	////}
}

// Met a jour le titre de la fenetre
void Game::updateWindowTitle()
{
	// Ajoute de l'information dans le titre
	//_extraTitle += "Mouse: " +
	//    to_string((int)_mouseMagnet.getExactX()) + " " +
	//    to_string((int)_mouseMagnet.getExactY());
	//_extraTitle += "  Coord: " +
	//    to_string(_mouseMagnet.getGridCol()) + " " +
	//    to_string(_mouseMagnet.getGridLine());

	_extraTitle += toolName[_currentTool];

	_extraTitle += "        Lives : " + to_string((int)_player.getHp()) + "/" + to_string((int)_player.getHpMax());
	_extraTitle += "        Game State : " + _appStateName[_appState];
	_extraTitle += "        Score : " + to_string(_score);

	if (_extraTitle != "")
		_extraTitle = " : " + _extraTitle;

	// Change le titre
	_window.setTitle(WINDOW_TITLE + _extraTitle);

	// Reinitialise pour la prochain iteration
	_extraTitle = "";
}

// Affiche la grille du labyrinthe
void Game::drawGrid()
{
	for (size_t l = 0; l < _map.nbLine(); l++)
	{
		for (size_t c = 0; c < _map.nbCol(); c++)
		{
			// Choix de la bonne tuile a afficher
			BLOCK_TYPE t = _map.at(l, c).getType();
			int v = _map.at(l, c).getVersion();
			_tileSprite[t][v].setPosition(c*TILE_SIZE, l*TILE_SIZE);
			_window.draw(_tileSprite[t][v]);
		}
	}
}

void Game::drawPlayer()
{
	_playerSprites[_animFrame][_animType].setPosition(_player.getExactX(), _player.getExactY());
	_window.draw(_playerSprites[_animFrame][_animType]);
}

void Game::drawShield()
{
	if (_currentTool == SPHERE_SHIELD)
	{
		for (size_t i = 0; i < _shieldSphere.size(); i++)
		{
			_bulletShape[FRIENDLY].setPosition(_shieldSphere[i].getExactX(), _shieldSphere[i].getExactY());
			_window.draw(_bulletShape[FRIENDLY]);
		}
	}
}

void Game::drawBullets()
{
	for (list<Bullet>::iterator b = _bullets.begin(); b != _bullets.end(); b++)
	{
        if (b->isFriendly())
        {
            _bulletShape[b->isFriendly()].setScale(Vector2f(b->getDamage(), b->getDamage()));
        }
		_bulletShape[b->isFriendly()].setPosition(b->getExactX(), b->getExactY());
		_window.draw(_bulletShape[b->isFriendly()]);
	}
}

void Game::drawMovableGui()
{
	// Mouse Square
	_mouseMagnet.setPositionExact(
		_mouseCoord.getPosition().x,
		_mouseCoord.getPosition().y);

	if (_currentTool == BUILD)
	{
		_mouseSquare.setPosition(
			_mouseMagnet.getGridCol() * TILE_SIZE,
			_mouseMagnet.getGridLine() * TILE_SIZE);
		_window.draw(_mouseSquare);
	}

	if (toolIsAShooter())
	{
		_aimingSight.setPosition(
			_mouseCoord.getPosition().x,
			_mouseCoord.getPosition().y);
		_window.draw(_aimingSight);
	}
}

void Game::drawFoes()
{
	// Bats
	for (Crawler& c : _bats)
	{
		_batSprite[_frameRun / 5 % 4][c.getDirection()].setPosition(
			c.getExactX(),
			c.getExactY());
		_window.draw(_batSprite[_frameRun / 5 % 4][c.getDirection()]);
	}

	// Boss
	if (_boss.isAlive())
	{
		_batSprite[_frameRun / 5 % 4][2].setScale(Vector2f(2, 2));
		_batSprite[_frameRun / 5 % 4][2].setPosition(_boss.getExactX(), _boss.getExactY());
		_window.draw(_batSprite[_frameRun / 5 % 4][2]);
		_batSprite[_frameRun / 5 % 4][2].setScale(Vector2f(1, 1));
	}
}

void Game::drawBossHealthBar()
{
	// Boss health bar
	if (_boss.isAlive())
	{
		float hpRatio = (float)_boss.getHp() / _boss.getHpMax();
		_bossHealthBar.setSize(Vector2f(
			(MAP_WIDTH_PIXELS - 6) * hpRatio, // Le 6 est pour 2 fois la thickness de la bar
			16));
		_bossHealthBar.setPosition(3, 3);
		_window.draw(_bossHealthBar);
	}
}

// Affiche les objets qui ne sont pas affecter par la view
void Game::drawThingsDirectlyOnTheScreen()
{
	_window.setView(_view[NULL_VIEW]);

	drawBossHealthBar();

	// Affichage du shader
	if (_appState != RUNNING)
	{
		_window.draw(_shader);
		_window.draw(_messageOnShader);
	}

	// Debug info
	_debugInfo.setString(_debug);
	_window.draw(_debugInfo);
	_debug = "";

	_window.draw(_mouseCoord);

	_window.setView(_view[_currentView]);
}

// Miroir d'un sprite sur l'axe vertical
void Game::flipSpriteHorizontal(Sprite& s)
{
	s.setOrigin({ s.getLocalBounds().width, 0 });
	s.setScale({ -1, 1 });
}

// Affiche le contenu de map dans le _debug
void Game::printMap()
{
	_debug += "\r\n";
	for (size_t l = 0; l < 20; l++)
	{
		for (size_t c = 0; c < 20; c++)
		{
			_debug += _map.at(l, c).getType() + 48;
		}
		_debug += "\r\n";
	}
}
