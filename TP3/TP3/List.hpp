/*****************************************************************************
File  : List.hpp
Author: Anthony Cote
Date  : 2018-11-15
Goal  : Défini une Liste d'elements qui est iterable
******************************************************************************/

#pragma once

#include <assert.h>

template <typename TYPE> class List;

// CLASSE CELLULE
template <typename TYPE>
class cellule
{
    friend class List<TYPE>;//Seule classe ayant accès à la représentation de la cellule
    TYPE element;			//Contenu de la cellule
    cellule <TYPE> *next;	//Pointeur vers la cellule suivante
    cellule <TYPE> *prev;	//Pointeur vers la cellule precedente

    cellule(const TYPE&e, cellule<TYPE> *n = nullptr, cellule<TYPE> *p = nullptr)
        : element(e), next(n), prev(p) {};
};

// CLASSE LIST
template <typename TYPE>
class List
{
private:
    cellule <TYPE> *_first;		    // Adresse du premier élément
    List(const List<TYPE> &l);		// Copieur désactivé
public:
    // CLASSE ITERATOR
    class iterator
    {
        friend class List<TYPE>;    // Classe ayant acces au proprietes de iterator
    private:
        cellule<TYPE>* 	_current;	                        // adresse de la cellule
        const List<TYPE>* _list;	                        // adresse de la Liste
    public:
        iterator()
            : _current(nullptr), _list(nullptr) {};         // constructeurs
        iterator(cellule<TYPE>& current, const List<TYPE>* list);
        ~iterator();				                        // destructeur

        const iterator& operator=(const iterator i);        // pour j=i

        bool operator==(const iterator it)const;            // pour if(j==i)
        bool operator!=(const iterator it)const;            // pour if(j!=i)

        const iterator operator++();		                // ++i
        const iterator operator--();		                // --i
        iterator operator++(int i);			                // i++
        iterator operator--(int i);			                // i--

        TYPE& operator*();				                    // accès à un élément
        const TYPE& operator*()const;		                // idem, en mode const

        TYPE* List<TYPE>::iterator::operator->()const;
    };
    List(void) : _first(nullptr) {};                        // Constructeur
    ~List(void) { clear(); };                               // Destructeur

    void clear();                                           // vide
    bool empty()const;                                      // retourne si c'est vide

    iterator begin()const;		                            // return premier
    iterator end()const;		                            // return NULL

    const iterator insert(iterator it, const TYPE& e);      // Ajoute un element a l'iterateur
    iterator erase(iterator it);                            // Efface un element a l'iterateur
    iterator erase(iterator first, iterator last);          // Efface les elements entre les iterateurs

    TYPE& operator[](iterator it);		//pas ds la STL     // Accede a un element en setter
    const TYPE& operator[](iterator it)const;               // Accede a un element en getter

    iterator operator()(const TYPE& t)const;                // cherche l'element dans la liste
    iterator operator()(const TYPE& t, iterator it)const;   // cherche l'element dans la liste avec l'iterateur

    const List<TYPE>& operator=(const List<TYPE>& l);       // Assignation de liste

    TYPE List<TYPE>::back();
    void List<TYPE>::push_back(const TYPE& ele);

};

// ITERATOR ============================================================

template<typename TYPE>
List<TYPE>::iterator::iterator(cellule<TYPE>& current, const List<TYPE>* list)
{
    _current = current;
    _list = list;
}

template<typename TYPE>
List<TYPE>::iterator::~iterator()
{
    _current = nullptr;
    _list = nullptr;
}

template<typename TYPE>
typename const List<TYPE>::iterator & List<TYPE>::iterator::operator=(const iterator it)
{
    _current = it._current;
    _list = it._list;

    return *this;
}

template <class TYPE>
bool List<TYPE>::iterator::operator==(const iterator it)const
{
    assert(_list == it._list);
    return _current == it._current;
}

template<typename TYPE>
bool List<TYPE>::iterator::operator!=(const iterator it) const
{
    assert(_list == it._list);
    return _current != it._current;
}

template<typename TYPE>
typename const List<TYPE>::iterator List<TYPE>::iterator::operator++() // ++i
{
    assert(_list != nullptr);
    assert(_current != nullptr);


    if (_current == _list->_first->prev)  // end
        _current = nullptr;
    else                                // normal
        _current = _current->next;

    return *this;
}

template<typename TYPE>
typename const List<TYPE>::iterator List<TYPE>::iterator::operator--() // --i
{
    assert(_list != nullptr);
    assert(_current != _list->_first);

    if (_current == nullptr)   // end
        _current = _list->_first->prev;
    else                       // normal
        _current = _current->prev;

    return *this;
}

template<typename TYPE>
typename List<TYPE>::iterator List<TYPE>::iterator::operator++(int i)   // i++
{
    List<TYPE>::iterator it(*this);
    operator++();
    return it;
}

template<typename TYPE>
typename List<TYPE>::iterator List<TYPE>::iterator::operator--(int i)   // i--
{
    List<TYPE>::iterator it(*this);
    operator--();
    return it;
}

template<typename TYPE>
TYPE& List<TYPE>::iterator::operator*()
{
    assert(_list != nullptr);
    assert(_current != nullptr);

    return _current->element;
}

//Retourne l'élément où est l'itérateur en constante référence
template <class TYPE>
const TYPE& List<TYPE>::iterator::operator*()const
{
    assert(_list != nullptr);
    assert(_current != nullptr);
    assert(_list->_first != nullptr);
    return _current->element;
}


template<typename TYPE>
TYPE* List<TYPE>::iterator::operator->()const
{
    assert(_list != nullptr);
    assert(_current != nullptr);
    assert(_list->_first != nullptr);
    
    return &(_current->element);
}

//// LIST ===============================================================

template<typename TYPE>
void List<TYPE>::clear()
{
    List<TYPE>::iterator it = end();
    while (!empty())
    {
        erase(begin());
    }
}

template<typename TYPE>
bool List<TYPE>::empty() const
{
    return _first == nullptr;
}

template <typename TYPE>
typename List<TYPE>::iterator List<TYPE>::begin()const
{
    List<TYPE>::iterator it;	//Itérateur sur le début (1ere cellule)

    it._current = _first;
    it._list = this;

    return it;
}

template<typename TYPE>
typename List<TYPE>::iterator List<TYPE>::end() const
{
    List<TYPE>::iterator it;    //Itérateur sur la fin (derniere cellule)

    it._current = nullptr;
    it._list = this;

    return it;
}

template<typename TYPE>
typename const List<TYPE>::iterator List<TYPE>::insert(iterator it, const TYPE& ele)
{
    assert(it._list == this);

    if (empty()) // nouvelle cellule
    {
        it._current = _first->prev = _first->next = _first = new cellule<TYPE>(ele);
    }
    else if (it._current == nullptr) // end
    {
        it._current = _first->prev = _first->prev->next = new cellule<TYPE>(ele, _first, _first->prev);
    }
    else // normal
    {

        it._current->prev = it._current->prev->next = new cellule<TYPE>(ele, it._current, it._current->prev);
        if (it._current == _first)
            _first = _first->prev;
        it._current = it._current--; // TODO initialization 
    }
    return it;
}

template<typename TYPE>
typename List<TYPE>::iterator List<TYPE>::erase(iterator it)
{
    assert(!empty());
    assert(it._list == this);
    assert(it != end());


    if (_first == _first->prev) // Efface la derniere cellule restante
    {
        _first = it._current = nullptr;
    }
    else if (it._current == _first) // Efface la premiere cellule
    {
        _first = _first->next;
    }
    else // Situation normale
    {
        it._current->prev->next = it._current->next;
        it._current->next->prev = it._current->prev;
    }
    // TODO doit repositionner l'iterateur
    if (it != end())
        it++;

    delete it._current;
    return it;
}

template<typename TYPE>
typename List<TYPE>::iterator List<TYPE>::erase(iterator first, iterator last)
{
    assert(!empty());
    assert(first._list == this);
    assert(last._list == this);

    while (first != last)
    {
        first = erase(first);
        if (first != end())
            last = erase(last);
    }
    return last;
}

template<typename TYPE>
TYPE& List<TYPE>::operator[](iterator it)
{
    assert(it._list == this);
    return *it;
}

template<typename TYPE>
const TYPE& List<TYPE>::operator[](iterator it) const
{
    assert(it._list == this);
    return *it;
}

template<typename TYPE>
typename List<TYPE>::iterator List<TYPE>::operator()(const TYPE& t) const
{
    return this->operator()(t, begin());
}


template<typename TYPE>
typename List<TYPE>::iterator List<TYPE>::operator()(const TYPE& t, iterator it) const
{
    assert(it._list == this);
    for (it = begin(); it != end(); it++)
    {
        if (t == it->element)
            return it;
    }
    return it;
}

template<typename TYPE>
const List<TYPE>& List<TYPE>::operator=(const List<TYPE>& l)
{
    if (this == &l)
        return *this;

    clear();

    for (List<TYPE>::iterator it = begin(); it != end(); it++)
    {
        insert(end(), it->element);
    }

    return *this;
}

template<typename TYPE>
TYPE List<TYPE>::back()
{
    return *(end()--);
}


template<typename TYPE>
void List<TYPE>::push_back(const TYPE& ele)
{
    insert(end(), ele);
}

