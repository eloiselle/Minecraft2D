#pragma once
#include "Crawler.h"

// Constructeur
Crawler::Crawler()
{
    init(1, 1, RANDOM, EVERY_MEET_WALL);
}

// Constructeur paramétrés
Crawler::Crawler(int x, int y, AI_Move ai, AI_Frequency decisionAI)
{
    init(x, y, ai, decisionAI);
}

// Change les variables du robot
void Crawler::init(int x, int y, AI_Move mov, AI_Frequency freq)
{
    setPositionExact(x * TILE_SIZE + HALF_TILE_SIZE, y * TILE_SIZE + HALF_TILE_SIZE);
    //_length = 0.5;
    _aiMove = mov;
    _aiFreq = freq;
    _frameLeftBeforeControl = 0;
}

// Change AI
void Crawler::setAI(AI_Move ai, AI_Frequency decisionAI)
{
    _aiMove = ai;
    _aiFreq = decisionAI;
}

//Change sa position de 1 dans la direction
void Crawler::move()
{
    setPositionExact(
        getExactX() + D4[_direction][X],
        getExactY() + D4[_direction][Y]);
    updateGridPosition();
    _frameLeftBeforeControl--;
}

//Change sa position de 1 dans la direction
void Crawler::move(int x, int y)
{
    setPositionExact(
        getExactX() + x,
        getExactY() + y);
    updateGridPosition();
    _frameLeftBeforeControl--;
}

// Décide de changer de case et commence le déplacement
void Crawler::startMoving()
{
    _isWalking = true;
    _isControllable = false;
    _frameLeftBeforeControl = TILE_SIZE / _speed;
}

// Arrete de se deplacer
void Crawler::stopMoving()
{
    _isWalking = false;
    _isControllable = true;
    _frameLeftBeforeControl = 0;
}

// Change la direction de 90 degree anti-clockwise
void Crawler::turnLeft()
{
    _direction = static_cast<DIRECTION4>((_direction + 3) % 4);
}

// Change la direction de 90 degree clockwise
void Crawler::turnRight()
{
    _direction = static_cast<DIRECTION4>((_direction + 1) % 4);
}

void Crawler::play(sf::SoundBuffer & buff)
{
    //_buffer.loadFromFile("flap.wav");
    _sound.setBuffer(buff);
    _sound.play();
}

// Effectu les operation de routine a chaque refresh
//void Crawler::update(int time, FixedGrid& map)
//{
//    if (_frameLeftBeforeControl == 0)
//    {
//        // Verifi si on doit lancer l'AI
//        switch (_aiFreq)
//        {
//        case EVERY_MEET_WALL:
//            if(!map.isWalkable(
//                getExactX() + TILE_SIZE * (Direction::xFromDir(_direction.getValue())),
//                getExactY() + TILE_SIZE * (Direction::yFromDir(_direction.getValue()))
//            )) // Not working (infinite loop), but not used currently
//            chooseNextMove(map);
//            break;
//        case EVERY_SQUARE:
//            if (isGridCentered())
//                chooseNextMove(map);
//            break;
//        case EVERY_SECOND: //Not exact
//            if (time % 30 == 0)
//                chooseNextMove(map);
//            break;
//        }
//        startMoving();
//    }
//    if (isAlive())
//        move();
//}
//
//// Choisi le prochain move en fonction de l'intelligence artificielle
//void RobotAI::chooseNextMove(FixedGrid& map)
//{
//    int randDir;
//
//    //Liste les directions possibles
//    vector<int> availableTiles = {};
//    if (map.isWalkable(getExactX(), getExactY() - TILE_SIZE))
//        availableTiles.push_back(0);
//    if (map.isWalkable(getExactX() + TILE_SIZE, getExactY()))
//        availableTiles.push_back(2);
//    if (map.isWalkable(getExactX(), getExactY() + TILE_SIZE))
//        availableTiles.push_back(4);
//    if (map.isWalkable(getExactX() - TILE_SIZE, getExactY()))
//        availableTiles.push_back(6);
//
//    if (availableTiles.size() != 0) // Pas coincé entre 4 blocks
//    {
//        switch (_aiMove)
//        {
//        case RANDOM:
//            randDir = availableTiles.at(rand() % availableTiles.size());
//            _direction.setDirection(randDir); // Genere une direction dans {0, 2, 4, 6}
//            break;
//        case RANDOM_NOT_BACK:
//            // Enleve la direction actuelle
//            for (size_t i = 0; i < availableTiles.size(); i++)
//            {
//                if (availableTiles.at(i) == _direction.getValue())
//                {
//                    availableTiles.erase(availableTiles.begin() + i);
//                    break;
//                }
//            }
//
//            randDir = availableTiles.at(rand() % availableTiles.size());
//            _direction.setDirection(randDir);
//            break;
//        case ALWAYS_LEFT:
//            // TODO Check if can move left, currently not used
//            turnLeft();
//            break;
//        case ALWAYS_RIGHT:
//            // TODO Check if can move right, currently not used
//            turnRight();
//            break;
//        default:
//            // Nothing
//            break;
//        }
//    }
//}