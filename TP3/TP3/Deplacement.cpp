/* En-tête du programme
====================
Programme:        Deplacement.cpp
Auteure:          Catherine Bronsard
Description:      contient les méthodes de la classe déplacement

/ Directives au pré-processeur
============================ */
#include "Deplacement.h"

// Constructeur avec parametres
Deplacement::Deplacement(int line, int col, DIRECTION dir)
{
    _ligne = line;
    _col = col;
    _direction = dir;
}

// Constructeur de copie
Deplacement::Deplacement(const Deplacement & d)
{
    _ligne = d._ligne;
    _col = d._col;
    _direction = d._direction;
}

// Change la direction
void Deplacement::setDirection(DIRECTION dir)
{
    assert(dir == NORD || dir == SUD || dir == EST || dir == OUEST || dir == AUCUNE_DIRECTION);
    _direction = dir;
}

// Change la Ligne
void Deplacement::setLigne(int line)
{
    assert(line >= 0);
    _ligne = line;
}

// Change la colonne
void Deplacement::setCol(int col)
{
    assert(col >= 0);
    _col = col;
}

// Retourne la direction
DIRECTION Deplacement::getDirection() const
{
    return _direction;
}

// Retourne la ligne
int Deplacement::getLigne() const
{
    return _ligne;
}

// Retourne la colonne
int Deplacement::getCol() const
{
    return _col;
}

//void Deplacement::print(std::ostream & out) const
//{
//	out << _ligne << " " << _col << " " << _direction << std::endl;
//}
//
//void Deplacement::read(std::istream & in)
//{
//	in >> _ligne >> _col >> _direction;
//}
//
//std::ostream& operator<<(std::ostream& out, const Deplacement & d)
//{
//	d.print(out);
//	return out;
//}
//
//std::istream & operator >> (std::istream & in, Deplacement & d)
//{
//	d.read(in);
//	return in;
//}