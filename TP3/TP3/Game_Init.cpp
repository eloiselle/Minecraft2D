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
    _window.setView(_view[CAMERA]);

    // Icon
    //_window.setIcon(image.GetWidth(), image.GetHeight(), image.GetPixelsPtr());
}

// Initialize les sprites
void Game::initSprites()
{
    // Load files
    if (!_tileset.loadFromFile("img\\tiles.bmp"))
        quitApplication();
    if (!_spiderTexture.loadFromFile("img\\spider.bmp"))
        quitApplication();
    if (!_spiderImage.loadFromFile("img\\spider.bmp"))
        quitApplication();

    // Map
    _tileSprite[EMPTY_BLOCK - 48] = initOneSprite(0, 2, _tileset);
    _tileSprite[SOFT_BLOCK - 48] = initOneSprite(10, 5, _tileset);
    _tileSprite[HARD_BLOCK - 48] = initOneSprite(0, 17, _tileset);
    _tileSprite[VISITED - 48] = initOneSprite(13, 2, _tileset);
    _tileSprite[CHECKPOINT - 48] = initOneSprite(5, 4, _tileset);

    // Spider
    _spiderImage.createMaskFromColor(Color(255, 255, 255));
    _spiderTexture.update(_spiderImage);
    _spiderSprite.setTextureRect(IntRect(0, 0, TILE_SIZE, TILE_SIZE));
    _spiderSprite.setTexture(_spiderTexture);
    _spiderSprite.setOrigin(Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
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
    _playerShape.setSize(Vector2f(8, 8));
    _playerShape.setOrigin(4, 4);

    // Bullet
    _bulletShape.setRadius(2);
    _bulletShape.setOrigin(1, 1);
    _bulletShape.setFillColor(Color::Red);
    _bulletShape.setOutlineColor(Color(128, 0, 0));
    _bulletShape.setOutlineThickness(1);

    // Coord de la souris sans la view
    _mouseCoord.setFillColor(Color::Red);
    _mouseCoord.setRadius(2);
    _mouseCoord.setOrigin(2, 2);

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
void Game::initWorldMap(const char* fileName)
{
    assert(strlen(fileName) > 0);

    // Read file
    if (!_map.readFile(fileName))
        return; // Action si fichier non conforme

    // Read Start & Finish
    //_map.at(_lab.xDepart(), _lab.yDepart()) = CHECKPOINT; // Depart
    _map.at(_map.xFin(), _map.yFin()) = CHECKPOINT;       // Arrivee

    // Prepare search
    _spider.setPositionInGrid(1, 1);

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
		_buffB.loadFromFile("pew.wav");
		_soundBullet.setBuffer(_buffB);

		_buffF.loadFromFile("flap.wav");
		_soundFlap.setBuffer(_buffF);

	}
}

void Game::initViews()
{
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
}

// Initialize les element du jeu
void Game::initGameElements()
{
    // Player
    _player.setPositionInGrid(15, 1);
    _player.setSpeed(4);

    _yoyoString.init(25, 0.71, 0.71);

    // Foes
    _spider.setPositionInGrid(12, 8);
    _spider.setSpeed(4);
    // Bullets
    _bullets.clear();
}