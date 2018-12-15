/***********************************************************************
File  : ResizableMap.hpp
Author: Anthony Cote
Date  : 2018-10-10
Goal  : Défini une structure de donnees a deux dimensions sous
        format de grille que l'on peux modifier sa taille, son nom
        ses elements et communiquer par un stream.
***********************************************************************/
#pragma once
#include "pch.h"
#include "Nameable.h"

using namespace std;

template <class T>
class ResizableMap : public Nameable
{
protected:

    unsigned int _nbL;  // Nombre de lignes pour la matrice
    unsigned int _nbC;  // Nombre de colonnes pour la matrice
    T  **_map;          // La map dynamique de lignes qui pointe sur les colonnes
public:

    ResizableMap() : _map(nullptr), _nbL(0), _nbC(0) {}; // Constructeur sans parametres
    ResizableMap(const char* name, unsigned int line, unsigned int col); // Constructeur avec parametres
    ResizableMap(const ResizableMap<T> &m);                              // Constructeur copieur
    ~ResizableMap();                                                     // Destructeur
    void clear();                                               // Vide l'objet
    void clearMap();                                            // Vide la map

    // Getteurs & Setters
    unsigned int nbLine()const;                                 // Retourne le nb de lignes
    unsigned int nbCol()const;                                  // Retourne le nb de colonnes

    T& at(unsigned int line, unsigned int col)const;            // Retourne une réference a un element
    T* operator[](unsigned int line);                           // Retourne une réference a un element

    // Methodes
    void resize(unsigned int nbLine, unsigned int nbCol, bool keepContenu = true);    // Resize la matrice
    void addBottomLines(unsigned int nbLine);
    void fill(const T& element);                                // Remplit la matrice avec l'element
    void fillLine(const T& element, unsigned int line);         // Remplit la line avec l'element
    void fillCol(const T& element, unsigned int col);           // Remplit la line avec l'element

    void printMeta(ostream& os = cout)const;                    // Output le nom et la taille de la matrice
    void print(ostream& os = cout)const;                        // Output la matrice (sans le nom)
    virtual void readGrid(istream& is = cin);                   // Lit la matrice de la map dans le flux

    const ResizableMap<T>& operator=(const ResizableMap<T> & m);// Assigne une map sur une autre
};

template <class T>
ostream& operator<<(ostream& sortie, const ResizableMap<T>& m);          // Operator d'output

template <class T>
istream& operator>> (istream& entree, ResizableMap<T>& m);               // Operator d'input

//        DEFINITION DE METHODES          *************************************

// Constructeur avec parametres
template <class T>
ResizableMap<T>::ResizableMap(const char* name, unsigned int line, unsigned int col)
{
    setName(name);
    _map = nullptr;
    _nbL = line;
    _nbC = col;

    // Initialisation de la grille
    if (line > 0 && col > 0)
    {
        // Cree les lignes d'elements
        _map = new T*[_nbL];

        // Cree les colonnes d'elements
        for (int l = 0; l < line; l++)
        {
            *(_map + l) = new T[col];
        }
    }
    else
        _nbL = _nbC = 0;
}

// Constructeur de copieur
template <class T>
ResizableMap<T>::ResizableMap(const ResizableMap<T> &m)
{
    _nbL = m._nbL;
    _nbC = m._nbC;
    _map = nullptr;
    _name = nullptr;

    // S'assure que la map n'est pas vide
    if (_nbL > 0 && _nbC > 0)
    {
        // Cree les lignes de colonnes
        _map = new T*[_nbL];

        // Creer les colonnes d'elements
        for (int l = 0; l < _nbL; l++)
            *(_map + l) = new T[_nbC];

        // Rempli la matrice avec les chiffre de l'original
        for (int l = 0; l < _nbL; l++)
        {
            for (int c = 0; c < _nbC; c++)
            {
                *(*(_map + l) + c) = *(*(m._map + l) + c);
            }
        }
    }

    setName(m._name);
}

// Destructeur
template <class T>
ResizableMap<T>::~ResizableMap()
{
    clear();
}

// Vide la memoire
template <class T>
void ResizableMap<T>::clear()
{
    clearMap();
    clearName();
}

// Vide la map
template <class T>
void ResizableMap<T>::clearMap()
{
    // Supprime les colonnes d'elements
    for (unsigned int l = 0; l < _nbL; l++)
    {
        delete[] * (_map + l);
    }

    delete[] _map;
    _map = nullptr;
    _nbL = _nbC = 0;
}

// Retourne le nb de ligne
template <class T>
unsigned int ResizableMap<T>::nbLine()const
{
    return _nbL;
}

// Retourne le nb de colonne
template <class T>
unsigned int ResizableMap<T>::nbCol()const
{
    return _nbC;
}

// Resize
template <class T>
void ResizableMap<T>::resize(unsigned int newNbL, unsigned int newNbC, bool keepContenu)
{
    // Si le tableau se fait vider
    if (newNbL == 0 && newNbC == 0)
    {
        clearMap();
        return;
    }

    // Si le tableau reste de la même taille
    if (newNbL == _nbL && newNbC == _nbC)
        return;

    T **newMap = new T*[newNbL];

    // Cree les lignes de colonnes
    for (int l = 0; l < newNbL; l++)
    {
        newMap[l] = new T[newNbC];
    }

    if (keepContenu) // Copie les elements de la matrice
    {
        for (int l = 0; l < newNbL && l < _nbL; l++)
        {
            for (int c = 0; c < newNbC && c < _nbC; c++)
            {
                newMap[l][c] = _map[l][c];
            }
        }
    }
    clearMap();

    _nbC = newNbC;
    _nbL = newNbL;
    _map = newMap;
    newMap = nullptr;
}

template<class T>
void ResizableMap<T>::addBottomLines(unsigned int nbLine)
{
    if (nbLine == 0)
        return;

    int total = _nbL + nbLine;

    T **newMap = new T*[total];

    // Transfert les anciennes lignes
    for (size_t l = 0; l < _nbL; l++)
    {
        newMap[l] = _map[l];
    }

    // Cree les nouvelles colonne d'element
    for (size_t l = _nbL; l < total; l++)
    {
        newMap[l] = new T[_nbC];
    }

    _nbL = total;
    _map = newMap;
    newMap = nullptr;
}

// Rempli complement la map avec la valeur
template<class T>
void ResizableMap<T>::fill(const T& element)
{
    for (int l = 0; l < _nbL; l++)
    {
        for (int c = 0; c < _nbC; c++)
        {
            _map[l][c] = element;
        }
    }
}

// Rempli la line avec la valeur
template<class T>
void ResizableMap<T>::fillLine(const T& element, unsigned int line)
{
    for (int c = 0; c < _nbC; c++)
    {
        _map[line][c] = element;
    }
}

// Rempli la colonne avec la valeur
template<class T>
void ResizableMap<T>::fillCol(const T& element, unsigned int col)
{
    for (int l = 0; l < _nbL; l++)
    {
        _map[l][col] = element;
    }
}

// Getter/Setter pour un element
template <class T>
T& ResizableMap<T>::at(unsigned int line, unsigned int col)const
{
    assert(_map != nullptr);
    assert(line < _nbL);
    assert(col < _nbC);

    return _map[line][col]; // Retourne l'element pour acceder ou modifier.
}

// Getter/Setter pour un element
template <class T>
T* ResizableMap<T>::operator[](unsigned int line)
{
    assert(line < _nbL);

    return *(_map + line); // Retourne une ligne de colonnes
}

// Assigne la map a une autre
template <class T>
const ResizableMap<T>& ResizableMap<T>::operator=(const ResizableMap<T> & m)
{
    if (&m == this) // Verifie si ce n'est pas la meme matrice
        return *this;

    clear();

    _nbC = m._nbC;
    _nbL = m._nbL;

    setName(m._name);

    // Si contient au moins une cellule
    if (_nbL > 0 && _nbC > 0)
    {
        // Cree les lignes de colonnes
        _map = new T*[_nbL];

        for (int l = 0; l < _nbL; l++)      // Lignes
        {
            // Cree les colonnes d'elements
            *(_map + l) = new T[_nbC];

            // Copie les elements
            for (int c = 0; c < _nbC; c++)  // Colonnes
            {
                _map[l][c] = m._map[l][c];
            }
        }
    }
    return *this;
}

// Output le nom et la taille de la matrice
template<class T>
void ResizableMap<T>::printMeta(ostream & os) const
{
    os << getName() << " (" << _nbL << "," << _nbC << ")";
}

// Envoye la map dans un stream
template <class T>
void ResizableMap<T>::print(ostream& os) const
{
    // Imprime tous les caracteres de la map
    for (int l = 0; l < _nbL; l++)            // Lignes
    {
        for (int c = 0; c < _nbC; c++)        // Colonnes
        {
            os << _map[l][c] << " "; // Imprime l'element
        }
        os << endl;
    }
}

// Lit un stream pour creer une map
template <class T>
void ResizableMap<T>::readGrid(istream& is)
{
    assert(_map != nullptr);
    assert(_nbL > 0);
    assert(_nbC > 0);

    // On remplace les characteres par celui de l'entree
    for (int l = 0; l < _nbL; l++)      // Lignes
    {
        for (int c = 0; c < _nbC; c++)  // Colonnes
        {
            is >> _map[l][c];    // Remplace le char suivant
        }
    }
}

// Operator d'output
template <class T>
ostream& operator<<(ostream& os, const ResizableMap<T>& m)
{
    m.print(os);
    return os;
}

// Operator d'input
template <class T>
istream& operator>>(istream& is, ResizableMap<T>& m)
{
    m.read(is);
    return is;
}