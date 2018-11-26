/*********************************************
File  : Game.h
Author: Anthony (Play) & Louis (Menu) & Christophe (Réseau)
Date  : 2018-04-30
Goal  : Lance une partie de Bomberman
*********************************************/

#pragma once

// DIRECTIVES AU PRE-PROCESSEUR

#include <string>
#include <chrono>
#include <array>
#include <thread>

#include "Const.h"

#include "Robot.h"
#include "MapB.h"

class Game
{
public:
    Game();
    ~Game();

    void init();

private:

    // array<Bomber,2> _bbm;       // Playable characters
    // array<Robot, 8> _robs;      // Ennemi CPU
    // Bomb _bom[MAX_BOMBS];       // Tableau de bombe
    MapB _map;                   // Grille pour le terrain
    int _playerId = 0;          // Index du joueur local

    // Menu
    bool _nextScreen = false;   //
    int _selection = 0;         //

    bool _continuer = true;	    // flag pour la fin de la boucle

    // Timing
    int _tempsPrecedent = 0;    // dernier moment ou un loop a été activé
    int _tempsActuel;           // stock le moment actuel pour comparaison avec le précédent
    int _frameCounter;          // Identifiant pour l'animation a utiliser
    int _animationFrame;        // Frame a utiliser pour l'animation des objet


    int _sendBomb = 0;	// Permet de savoir si l'on doit envoyer une bombe
    int _posXReseau = 0;
    int _posYReseau = 0;

};
