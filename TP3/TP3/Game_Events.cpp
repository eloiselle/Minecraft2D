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
            if (_event.key.code == Keyboard::T && canTeleportAtMouse())
                _player.setPositionExact(
                    _mouseMagnet.getGridCol() * TILE_SIZE + (TILE_SIZE / 2),
                    _mouseMagnet.getGridLine() * TILE_SIZE + TILE_SIZE - 1);
        }

        if (_appState == RUNNING)
        {
            if (_event.type == Event::MouseWheelMoved)
                handleMouseWheelMoved();
        }
    }
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
void Game::handleKeypress()
{
    if (_appState == RUNNING)
    {
        handleArrowKeys();
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape))
        quitApplication();

    if (Keyboard::isKeyPressed(Keyboard::Num0))
        initWorldMap();

    // Change weapon
    if (Keyboard::isKeyPressed(Keyboard::Num1))
    {
        _currentTool = BUILD;
        _player.setNoWeapon(_frameRun);
    }
    if (Keyboard::isKeyPressed(Keyboard::Num2))
    {
        _currentTool = UZI;
        _player.setUzi(_frameRun);
    }
    if (Keyboard::isKeyPressed(Keyboard::Num3))
    {
        _currentTool = ASSAULT;
        _player.setAssault(_frameRun);
    }
    if (Keyboard::isKeyPressed(Keyboard::Num4))
    {
        _currentTool = SNIPER;
        _player.setSniper(_frameRun);
    }
    if (Keyboard::isKeyPressed(Keyboard::Num5))
    {
        _currentTool = SHOT_GUN;
        _player.setShotgun(_frameRun);
    }
    if (Keyboard::isKeyPressed(Keyboard::Num6))
    {
        _currentTool = BULLET_HELL;
        _player.setBulletHell(_frameRun);
    }
    if (Keyboard::isKeyPressed(Keyboard::Num7))
    {
        _currentTool = SLOW_MO;
        _player.setNoWeapon(_frameRun);
    }
    if (Keyboard::isKeyPressed(Keyboard::Num8))
    {
        _currentTool = HOMING;
        _player.setHoming(_frameRun);
    }
    if (Keyboard::isKeyPressed(Keyboard::Num9))
    {
        _currentTool = SPHERE_SHIELD;
        _player.setNoWeapon(_frameRun);
    }
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

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            //Placer un bloc
            if (isMouseInMap() && _currentTool == BUILD)
                insertBlockAtMouse(c, l);

            //Tirer le nombre de bullets
            if (toolIsAShooter() && _player.delayIsReady(_frameRun))
            {
                Character* target = nullptr;

                if (_currentTool == HOMING)
                {
                    for (Crawler& c : _bats)
                    {
                        //Détermine la target
                        if (areOnTheSameSquare(_mouseMagnet, c))
                        {
                            target = &c;
                            break;
                        }
                    }
                }

                for (int i = 0; i < _player.getWeaponNbBulletsFired(); i++)
                {
                    shootBullet(target);
                }
            }
        }
        if (Mouse::isButtonPressed(Mouse::Right))
        {
            //Enlever un bloc
            if (isMouseInMap() && _currentTool == BUILD)
                removeBlockAtMouse(c, l);
        }
    }
}

void Game::shootBullet(Character *target)
{
    _bullets.push_back(Bullet());

    if (MUSIQUE)
        _bullets.back().play(_buffBullet);

    _bullets.back().setPositionExact(
        _player.getExactX(),
        _player.getExactY() - HALF_TILE_SIZE);

    if (target == nullptr)
    {
        _bullets.back().aim(
            _mouseCoord.getPosition().x,
            _mouseCoord.getPosition().y,
            _player.getWeaponAccuracy());
    }
    else
    {
        _bullets.back().setTarget(target);
        _bullets.back().aim(*target);
    }

    _bullets.back().setSpeed(_player.getWeaponBulletSpeed());
    _bullets.back().setDamage(_player.getWeaponDamage());
    _player.delayReset(_frameRun);
}