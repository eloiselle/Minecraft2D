/* En-tête du programme
====================
Programme:        Robot.h
Auteure:          Catherine Bronsard
Description:      pile de déplacements qui peut ajouter, enlever et s'initialiser avec un déplacement
                    et peut être manipulée

/ Directives au pré-processeur
============================ */
#pragma once
#include "pch.h"

#include "stack.h"
#include "Deplacement.h"

class Robot
{
protected:
    stack<Deplacement> _pile;                           // pile des déplacements effectués
public:
    Robot() {};                                         // constructeur sans parametres
    Robot(int line, int col);                           // initialiser à la position de départ
    void init(int line, int col);                       // initialiser à la position de départ

    void deplacer(int line, int col, DIRECTION dir);    // ajouter un déplacement
    void revenir();                                     // revenir en arrière (enlever un déplacement)
    void changeDir(DIRECTION newDir);                   // changer la direction
    bool empty();

    Deplacement getLastDeplacement() const;             // Retourne le dernier deplacement
    DIRECTION getDir()const;                            // Retourne la direction
};
