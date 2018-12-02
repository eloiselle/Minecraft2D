/* En-tête du programme
====================
Programme:        Deplacement.h
Auteure:          Catherine Bronsard
Description:      Déplacement (composé de la ligne, de la colonne et de la direction)
                    peut être initialisé et manipulé

/ Directives au pré-processeur
============================ */
#pragma once
#include "pch.h"
#include "Direction.h"


class Deplacement
{
protected:
    DIRECTION4 _direction;   // direction vers laquelle le robot-pile va
    int _ligne;             // ligne dans la matrice
    int _col;               // colonne dans la matrice

public:
    /* Constructeurs */
    Deplacement() : _direction(NORD), _ligne(0), _col(0) {};
    Deplacement(int line, int col, DIRECTION4 dir);
    Deplacement(const Deplacement & d);

    /* Setteurs */
    void setDirection(DIRECTION4 dir);
    void setLigne(int line);
    void setCol(int col);

    /* Getteurs */
    DIRECTION4 getDirection() const;
    int getLigne() const;
    int getCol() const;

    /* Afficher/lire un déplacement */      // Désactivé depuis l'utilisation d'un enum au lieu de char
    //void print(std::ostream& out) const;
    //void read(std::istream& in);
};

// Opérateurs pour afficher/lire
//std::ostream& operator<<(std::ostream& out, const Deplacement & d);
//std::istream& operator >> (std::istream & in, Deplacement& d);