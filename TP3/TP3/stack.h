/*
Auteure : Catherine Bronsard
Fichier : stack.h
Objectif: Classe stack - empile par dessus les anciennes données (comme une pile de livres)
		  peut être modifiée, 
*/
#pragma once
#include <cassert>
#include <iostream>
using namespace std;
template <class TYPE>
class stack
{
protected:
	struct cellule
	{
		TYPE	element;	// élément ds la cellule
		cellule *next; 		// pointeur vers prochaine cellule

		cellule(const TYPE& e, cellule * n)
		{
			element = e;
			next = n;
		}
	};
	cellule  *_top;			// 1er élément de la pile
	int  	 _size;			// taille (nb. élément) de la pile
	stack(const stack& p);

	cellule* copyStack(cellule * c)
	{
		if (c == nullptr)
			return nullptr;
		return new cellule(c->element, copyStack(c->next));
	}
public:
	stack();				// constructeur & destructeurr
	~stack();
	void push(const TYPE& e);			//ajoute un nouveau dessus
	void pop();					//enlève le dessus

	const TYPE& top() const;			//retourne le dessus, mais dépile pas
	TYPE& top();				//retourne le dessus, mais en setteur
	int size()const;				//retourne le nb d’élément
	int getSizeEnComptant()const;

	bool empty() const;				//si la pile est vide
	void clear();					//vide la pile

	const stack& operator=(const stack& s);	//affectateur
	bool operator==(const stack& s)const;	//comparaison de 2 piles
	void print(ostream & sortie) const; // seulement pour afficher les tests
};
template<class TYPE>
ostream & operator<<(ostream & sortie, const stack<TYPE> & s); // seulement pour les tests

template<class TYPE>
stack<TYPE>::stack()
{
	_size = 0;
	_top = nullptr;
}

template<class TYPE>
stack<TYPE>::~stack()
{
	clear();
}

template<class TYPE>
void stack<TYPE>::push(const TYPE & e)
{
	_top = new cellule(e, _top); // ajoute une nouvelle cellule avant le _top
	_size++;
}

template<class TYPE>
void stack<TYPE>::pop()
{
	assert(!empty()); // on ne peut enlever si c'est vide
	TYPE tempEle = _top->element;
	cellule *tempCell = _top;
	_size--;
	_top = _top->next;
}

template<class TYPE>
const TYPE & stack<TYPE>::top() const
{
	assert(!empty());
	return _top->element; // getteur
}

template<class TYPE>
TYPE & stack<TYPE>::top()
{
	assert(!empty());
	return _top->element; // setteur
}

template<class TYPE>
int stack<TYPE>::size() const
{
	return _size;
}

template<class TYPE>
int stack<TYPE>::getSizeEnComptant() const
{
	int taille = 0;

	cellule *temp = _top;
	while (temp != nullptr)
	{
		taille++;
		temp = temp->next;
	}
	return taille;
}

template<class TYPE>
bool stack<TYPE>::empty() const
{
	return _top == nullptr; // si vide
}

template<class TYPE>
void stack<TYPE>::clear()
{
	while (!empty()) // tant que pas vide on enlève
		pop();
}

template<class TYPE>
const stack<TYPE> & stack<TYPE>::operator=(const stack & s)
{
	if (this == &s)
		return *this;
	
	clear();

	if (!s.empty())
	{
		_top = copyStack(s._top); // appel de la fonction qui copie une pile
		_size = s._size;
	}
	return *this;
}

/* OPÉRATEUR= sans récursivité */

//template<class TYPE>
//const stack & stack<TYPE>::operator=(const stack & p)
//{
//	cellule *itImp, *itExp = p._top;
//	if (!empty())
//	{
//		itExp = itExp->next;
//		itImp = _top = new cellule(itExp->element, nullptr);
//		while (itExp != nullptr)
//		{
//			itImp = ItImp->next = new cellule(itExp->element, nullptr);
//			itExp = itExp->next;
//		}
//
//		_size = s._size;
//	}
//	return this;
//}

template<class TYPE>
bool stack<TYPE>::operator==(const stack & p) const
{
	if (_size != p._size)
	{
		return false;
	}

	cellule *itImp = _top, *itExp = p._top;

	while (itExp != nullptr)
	{
		if (itImp->element != itExp->element)
			return false;

		itExp = itExp->next;
		itImp = itImp->next;
	}
	return true;
}

template<class TYPE>
void stack<TYPE>::print(ostream & sortie) const
{
	cellule *temp = _top;

	while (temp != nullptr)
	{
		sortie << temp->element;
		temp = temp->next;
	}
}



template<class TYPE>
ostream & operator<<(ostream & sortie, const stack<TYPE>& s)
{
	s.print(sortie);
	return sortie;
}
