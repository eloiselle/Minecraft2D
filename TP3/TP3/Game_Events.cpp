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
            handleKeypressOnce();
        }

        if (_appState == RUNNING)
        {
            if (_event.type == Event::MouseWheelMoved)
                handleMouseWheelMoved();
        }
    }
}

void Game::handleKeypressOnce()
{
    if (_event.key.code == Keyboard::BackSpace)
        init();
    if (_event.key.code == Keyboard::P)
        handlePausing();
    if (_event.key.code == Keyboard::T && canTeleportAtMouse())
        _player.setPositionExact(
            _mouseMagnet.getGridCol() * TILE_SIZE + (TILE_SIZE / 2),
            _mouseMagnet.getGridLine() * TILE_SIZE + TILE_SIZE - 1);


    if (_event.key.code == Keyboard::M)
    {
        _isAudioActivated = !_isAudioActivated;
        _music.setVolume(100 * _isAudioActivated);
    }

    // View
    if (_event.key.code == Keyboard::F1)
        _currentView = FOLLOW_Y;
    if (_event.key.code == Keyboard::F2)
        _currentView = FOLLOW;
    if (_event.key.code == Keyboard::F3)
        _currentView = NEUTRAL;
    if (_event.key.code == Keyboard::F4)
        _currentView = CAMERA;
}

bool Game::canTeleportAtMouse()
{
    return isMouseInWindow()
        && isInMap(_mouseMagnet)
        && _map.at(_mouseMagnet.getGridLine(), _mouseMagnet.getGridCol()).getType() == EMPTY_BLOCK
        && !areOnTheSameSquare(_mouseMagnet, _player);
}

// Gere les input qui doivent etre activer en continu
void Game::inputActivatedInContinu()
{
    handleKeypressContinu(); 

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
    switch (_appState)
    {
    case Game::RUNNING:
        _appState = PAUSED;
        break;
    case Game::PAUSED:
        _appState = RUNNING;
        break;
    case Game::BOSS_KILLED:
        init();
        _appState = RUNNING;
        break;
    case Game::GAME_OVER:
        init();
        _appState = RUNNING;
        break;
    default:        break;
    }

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
void Game::handleKeypressContinu()
{
    if (_appState == RUNNING)
    {
        handleArrowKeys();
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape))           quitApplication();


    // Change tool
    if      (Keyboard::isKeyPressed(Keyboard::Num1))        switchTool(BUILD);
    else if (Keyboard::isKeyPressed(Keyboard::Num2))        switchTool(UZI);
    else if (Keyboard::isKeyPressed(Keyboard::Num3))        switchTool(ASSAULT);
    else if (Keyboard::isKeyPressed(Keyboard::Num4))        switchTool(SNIPER);
    else if (Keyboard::isKeyPressed(Keyboard::Num5))        switchTool(SHOT_GUN);
    else if (Keyboard::isKeyPressed(Keyboard::Num6))        switchTool(HOMING);
    else if (Keyboard::isKeyPressed(Keyboard::Num7))        switchTool(BULLET_HELL);
    else if (Keyboard::isKeyPressed(Keyboard::Num8))        switchTool(SPHERE_SHIELD);
    else if (Keyboard::isKeyPressed(Keyboard::Num9))        switchTool(SLOW_MO);
}

void Game::handleArrowKeys()
{
    _player.isMoving(false);

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
        _player.isMoving(true);
        _player.lookToTheRight();
        _view[CAMERA].move(ARROW_EXPLORE, 0);
        tryToMove(RIGHT, _player);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) ||
        Keyboard::isKeyPressed(Keyboard::S))
    {
        _view[CAMERA].move(0, ARROW_EXPLORE);
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) ||
        Keyboard::isKeyPressed(Keyboard::A))
    {
        _player.isMoving(true);
        _player.lookToTheLeft();
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

        // Left Click
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            //Placer un bloc
            if (isMouseInMap() && _currentTool == BUILD)
                insertBlockAtMouse(c, l);

            // Ajouter un shield au cercle de shield
            if (isMouseInMap() && _currentTool == SPHERE_SHIELD && _shieldSphere.size() <= MAX_SHIELD_SPHERES)
            {
                _shieldSphere.insert(_shieldSphere.end(), Bullet());
                _shieldVA.insert(_shieldVA.end(), VectorAngle());

                for (size_t i = 0; i < _shieldSphere.size(); i++)
                {
                    _shieldVA[i].init(100, 0, 1);
                    _shieldVA[i].setAngleDegree(i * (360 / _shieldSphere.size()));
                }
            }

            shootWeapon();
        }
        // Right Click
        if (Mouse::isButtonPressed(Mouse::Right))
        {
            //Enlever un bloc
            if (isMouseInMap() && _currentTool == BUILD)
                removeBlockAtMouse(c, l);
        }
    }
}

void Game::switchTool(TOOL tool)
{
    if (tool != _currentTool)
    {
        _bullets.clear();
        _currentTool = tool;
        _player.setWeapon(tool, _frameRun);
        _textToolSwitch.setString(TOOL_NAMES[_currentTool]);
    }
}