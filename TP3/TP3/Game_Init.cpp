#include "Game.h"

// ############################################################################
//          INIT
// ############################################################################

// Constructeur
Game::Game()
{
	initWindow();
	init();
}

// Initialiseur de la classe
void Game::init()
{
	srand(time(NULL));

	initWorldMap();

	initSprites();
	initShapes();

	initGameElements();
	initTexts();
	initMusic();
	initSounds();

	_currentView == FOLLOW_Y;
	_frameRun = 0;
	_frameTotal = 0;
}

// Initialize la window
void Game::initWindow()
{
	// Window
	_window.create(VideoMode(DEF_WINDOW_WIDTH, DEF_WINDOW_HEIGHT),
		WINDOW_TITLE, Style::Default, _settings);
	_settings.antialiasingLevel = ANTI_ALIASING_LEVEL;

	_window.setFramerateLimit(FRAMERATE);
	handleResizeWindow();

	// View
	_window.setView(_view[FOLLOW]);

	// Icon
	//_window.setIcon(image.GetWidth(), image.GetHeight(), image.GetPixelsPtr());
}

// Initialize les sprites
void Game::initSprites()
{
	// Load files
	if (!_tileset.loadFromFile("img\\tiles.bmp"))
		quitApplication();
	if (!_spiderTexture.loadFromFile("img\\bat.bmp"))
		quitApplication();
	if (!_spiderImage.loadFromFile("img\\bat.bmp"))
		quitApplication();
	if (!_playerTexture.loadFromFile("img\\WaddleDoo.bmp"))
		quitApplication();
	if (!_playerImage.loadFromFile("img\\WaddleDoo.bmp"))
		quitApplication();

	// Player
	_playerImage.createMaskFromColor(Color(47, 54, 153));
	_playerTexture.update(_playerImage);
	_playerSprite.setTextureRect(IntRect(0, 0, TILE_SIZE, TILE_SIZE));
	_playerSprite.setTexture(_playerTexture);
	_playerSprite.setOrigin(Vector2f(TILE_SIZE / 2, TILE_SIZE));

	// Spider
	_spiderImage.createMaskFromColor(Color(255, 255, 255));
	_spiderTexture.update(_spiderImage);
	_spiderSprite.setTextureRect(IntRect(64, 0, TILE_SIZE, TILE_SIZE));
	_spiderSprite.setTexture(_spiderTexture);
	_spiderSprite.setOrigin(Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
	// Map
	for (size_t version = 0; version < 8; version++)
	{
		_tileSprite[EMPTY_BLOCK][version] = initOneSprite(0 + version, 0, _tileset);
		_tileSprite[SOFT_BLOCK][version] = initOneSprite(7 + version, 5, _tileset);
		_tileSprite[HARD_BLOCK][version] = initOneSprite(8 + version, 8, _tileset);
		_tileSprite[VISITED][version] = initOneSprite(13 + version, 2, _tileset);
		_tileSprite[INVALID_BLOCK][version] = initOneSprite(5 + version, 4, _tileset);
	}
}

// Recupere un sprite a partir des parametres
Sprite Game::initOneSprite(unsigned int line, unsigned int col, Texture& texture,
	unsigned int tileSize, unsigned int separation)
{
	Sprite spr;
	int xMove = line * tileSize + (line * separation * 2);
	int yMove = col * tileSize + (col * separation * 2);
	spr.setTextureRect(IntRect(xMove, yMove, tileSize, tileSize));
	spr.setTexture(texture);
	return spr;
}

// Initialize les fonts
void Game::initTexts()
{
	// Font
	if (!_fontInvasion2000.loadFromFile("INVASION2000.TTF"))
		quitApplication();

	// Text Instructions
	_texteInstructions.setFont(_fontInvasion2000);
	_texteInstructions.setCharacterSize(36);                // In pixels
	_texteInstructions.setFillColor(Color(255, 255, 255));  // White
	_texteInstructions.setOutlineColor(Color(64, 64, 64));  // Dark grey
	_texteInstructions.setOutlineThickness(3);
	_texteInstructions.setPosition(32, 32);

	// Text debugInfo
	_debugInfo.setFont(_fontInvasion2000);
	_debugInfo.setCharacterSize(24);                // In pixels
	_debugInfo.setFillColor(Color(255, 255, 255, 128));  // White
	_debugInfo.setOutlineColor(Color(64, 64, 64, 128));  // Dark grey
	_debugInfo.setOutlineThickness(3);
	_debugInfo.setPosition(32, 32);
}

// Initialize les shapes
void Game::initShapes()
{
	_playerShape.setFillColor(Color::Green);
	_playerShape.setSize(Vector2f(3, 3));
	_playerShape.setOrigin(2, 2);

	// Bullet
	_bulletShape.setRadius(2);
	_bulletShape.setOrigin(1, 1);
	_bulletShape.setFillColor(Color::White);
	_bulletShape.setOutlineColor(Color::Cyan);
	_bulletShape.setOutlineThickness(1);

	// Coord de la souris sans la view
	_mouseCoord.setFillColor(Color::Red);
	_mouseCoord.setRadius(2);
	_mouseCoord.setOrigin(2, 2);
	// Aiming Sight
	_mouseCursor.setFillColor(Color::Blue);
	_mouseCursor.setRadius(2);
	_mouseCursor.setOrigin(2, 2);

	// Mouse Square
	int tk = 3;
	_mouseSquare.setOrigin(-tk, -tk);
	_mouseSquare.setSize(Vector2f(TILE_SIZE - tk * 2, TILE_SIZE - tk * 2));
	_mouseSquare.setFillColor(Color(0, 0, 0, 0));
	_mouseSquare.setOutlineColor(Color::Black);
	_mouseSquare.setOutlineThickness(tk);

	// Shader pour l'ecran de pause
	_shader.setSize(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
	_shader.setFillColor(Color(0, 0, 0, 128)); // Noir transparent
}

// Initialize la carte de terrain
void Game::initWorldMap()
{
	//assert(strlen(fileName) > 0);

	//// Read file
	//if (!_map.readFile(fileName))
	//    return; // Action si fichier non conforme

	_map.randomize();

	initViews();
}

void Game::initMusic()
{
	if (MUSIQUE)
	{
		_music.openFromFile("zelda.wav");
		_music.play();
	}
}

void Game::initSounds()
{
	if (MUSIQUE)
	{
		_buffBullet.loadFromFile("pew.wav");
		_buffFoes.loadFromFile("flap.wav");
	}
}

void Game::initViews()
{
	// DO NOT CHANGE _currentView HERE
	//_currentView = CAMERA; == BAD
	// Zoom
	float maxDim = MAX(_map.nbCol(), _map.nbLine());
	_view[NULL_VIEW] = handleResizeWindow();
	_view[NEUTRAL] = handleResizeWindow();
	_view[NEUTRAL].zoom(maxDim / TILE_SIZE * 1.5);
	_view[CAMERA] = handleResizeWindow();
	_view[CAMERA].zoom(maxDim / TILE_SIZE * 1.5);

	// Center
	_view[NEUTRAL].setCenter(
		_map.nbCol() * TILE_SIZE / 2,
		_map.nbLine() * TILE_SIZE / 2);
	_view[CAMERA].setCenter(
		_map.nbCol() * TILE_SIZE / 2,
		_map.nbLine() * TILE_SIZE / 2);
	_view[FOLLOW_Y].zoom(0.8);

	_currentView = FOLLOW_Y;
	_view[FOLLOW_Y] = handleResizeWindow();
}

// Initialize les element du jeu
void Game::initGameElements()
{
	// Player
	_player.setPositionInGrid(15, 4);
	_player.setSpeed(4);
	_map.at(_player.getGridLine(), _player.getGridCol());

	// Shield
	for (size_t i = 0; i < NB_SHIELD; i++)
	{
		_shieldVA[i].init(25, 0, 1);
		_shieldVA[i].rotate(i * SHIELD_ANGLE);
	}
	


	initFoes();

	// Bullets
	_bullets.clear();
}

// Initialise Foes
void Game::initFoes()
{
	
	for (int i = 0; i < NB_STARTING_BATS; i++)
	{
		_bats.push_back(Crawler());
	}

	int position_x = 4;

	for (list<Crawler>::iterator it = _bats.begin(); it != _bats.end(); it++)
	{
		it->setPositionInGrid(position_x, 1);
		position_x += 6;
	}

}