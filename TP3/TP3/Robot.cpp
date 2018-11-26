/* En-tête du programme
====================
Programme:        Robot.cpp
Auteure:          Catherine Bronsard
Description:      Contient les méthodes de la classe Robot

/ Directives au pré-processeur
============================ */

#include "Robot.h"

// Constructeur avec parametres
Robot::Robot(int line, int col)
{
    init(line, col);
}

// Initialization
void Robot::init(int line, int col)
{
    assert(line >= 0);
    assert(col >= 0);

    _pile.push(Deplacement(line, col, NORD));
}

// Deplacement
void Robot::deplacer(int line, int col, DIRECTION dir)
{
    assert(line >= 0);
    assert(col >= 0);
    assert(dir == NORD || dir == SUD || dir == EST || dir == OUEST || dir == AUCUNE_DIRECTION);

    _pile.push(Deplacement(line, col, dir));
}

// Enleve le dernier deplacement
void Robot::revenir()
{
    _pile.pop();
}

// Change la direction
void Robot::changeDir(DIRECTION newDir)
{
    assert(newDir == NORD || newDir == SUD || newDir == EST || newDir == OUEST || newDir == AUCUNE_DIRECTION);
    _pile.top().setDirection(newDir);
}

bool Robot::empty()
{
    return _pile.empty();
}

// avoir accès au dernier déplacement possible
Deplacement Robot::getLastDeplacement() const
{
    return _pile.top();
}

// Retourne la direction
DIRECTION Robot::getDir() const
{
    return _pile.top().getDirection();
}