/*
Auteure : Catherine Bronsard
Programme: Classe liste 
*/


#pragma once
#include <assert.h>

template<typename TYPE> class list;

//CLASSE CELLULE
template<typename TYPE>
class cellule
{
	friend class list<TYPE>;	//la seule classe ayant accès à la 
								//représentation de la cellule
	TYPE element;			//Contenu de la cellule
	cellule <TYPE> *next;		//Pointeur vers la cellule suivante 
	cellule <TYPE> *previous;	//Pointeur vers la cellule precedente

	cellule(const TYPE & e, cellule<TYPE> *n = nullptr, cellule<TYPE> *p = nullptr)
	{
		element = e;
		next = n;
		previous = p;
	}
};



template<typename TYPE>
class list
{
protected:

	cellule <TYPE> *_first;			//Adresse du premier élément 

	list(const list<TYPE> &l);		//Copieur désactivé

public:

	class iterator
	{
		friend class list<TYPE>;
	protected:
		cellule<TYPE>* 	_current;		//adresse de la cellule
		const list<TYPE>* _list;		//adresse de la liste
	public:
		iterator();					//constructeurs
		~iterator();				//destructeur

		const iterator& operator=(const iterator& iter);//pour j=i

		bool operator==(const iterator& iter)const; //pour if(j==i)
		bool operator!=(const iterator& iter)const; //pour if(j!=i)

		iterator operator++(int i);			//i++
		const iterator& operator++();		//++i

		iterator operator--(int i);			//i--
		const iterator& operator--();		//--i

		TYPE& operator*();				//accès à un élément
		const TYPE& operator*()const;		//idem, en mode const

		TYPE* operator->()const;

	};

	list();
	~list();

	void clear(); // vider la liste
	bool empty()const; // retourne si vide 

	iterator begin()const;			//return premier
	iterator end()const;				//return nullptr

	iterator back();

	iterator push_back(const TYPE& ele);


	iterator insert(iterator iter, const TYPE& e); // insérer avant l'itérateur
	iterator erase(iterator iter); // enlever 1 case
	iterator erase(iterator first, iterator last); // enlever de first jusqu'à last

	TYPE& operator[](iterator iter);		//pas ds la STL
	const TYPE& operator[](iterator iter)const; // 

	iterator operator()(const TYPE& e)const; // recherche 
	iterator operator()(const TYPE& e, iterator iter)const; // recherche d

	const list<TYPE>& operator=(const list<TYPE>& l);



};

template<typename TYPE>
list<TYPE>::list()
{
	_first = nullptr;
}

template<typename TYPE>
list<TYPE>::~list()
{
	clear();
}

template<typename TYPE>
typename void list<TYPE>::clear()
{
	list<TYPE>::iterator it;
	it = begin();
	while (!empty()) // tant que pas vide, on efface
	{
		it = erase(it);
	}
}

template<typename TYPE>
typename bool list<TYPE>::empty() const
{
	return _first == nullptr;
}

template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::begin() const
{
	list<TYPE>::iterator it;

	it._list = this;
	it._current = _first;

	return it;
}

template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::end() const
{
	list<TYPE>::iterator it;

	it._list = this;
	it._current = nullptr;

	return it;
}

template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::insert(iterator iter, const TYPE & e)
{
	assert(iter._list == this);

	if (empty()) //1e cellule à créer
		iter._current = _first->previous = _first->next = _first = new cellule<TYPE>(e, nullptr, nullptr);

	else if (iter._current == nullptr) // insérer à la fin
		iter._current = _first->previous = _first->previous->next = new cellule<TYPE>(e, _first, _first->previous);

	else // insérer n'importe où
	{
		// next de la cell d'avant = nouvelle cell
		// cell d'avant = nouvelle cell
		iter._current->previous = iter._current->previous->next = new cellule<TYPE>(e, iter._current, iter._current->previous);

		if (iter._current == _first) // si on insère avant la 1e case
		{
			_first = _first->previous; // change le pointeur sur 1e case
		}

		iter._current = iter._current->previous;
	}
	return iter;
}

template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::erase(iterator iter)
{
	assert(!empty());
	assert(iter._current != nullptr);
	assert(iter._list != nullptr);

	list<TYPE>::iterator it;
	it = iter;

	if (_first->next == _first) // si une seule case
	{
		delete _first;
		_first = nullptr;
		iter._current = nullptr;
	}
	else
	{
		iter._current->next->previous = iter._current->previous; // le previous de la cell d'après = cell avant
		iter._current->previous->next = iter._current->next; // le next de la cell avant = next de la cell à effacer

		if (iter._current == _first) // si insérer avant la 1e case, changer _first
			_first = _first->next;

		if (iter._current == _first->previous)  // si insérer à la fin
			iter._current = iter._current->previous;
		else
			iter._current = iter._current->next;
		delete it._current;
	}

	return iter;
}

template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::erase(iterator first, iterator last)
{
	assert(!empty());
	list<TYPE>::iterator it;
	it = first;
	do
	{
 		it = erase(it);
	} while (it != last);

	return it;
}

template<typename TYPE>
typename TYPE & list<TYPE>::operator[](iterator iter)
{
	assert(!empty());
	assert(iter._current != nullptr);
	assert(iter._list == this);

	return iter._current->element;
}

template<typename TYPE>
typename const TYPE & list<TYPE>::operator[](iterator iter) const
{
	assert(!empty());
	assert(iter._current != nullptr);
	assert(iter._list != nullptr);

	return iter._current->element;
}


template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::operator()(const TYPE & e) const
{
	return operator()(e, begin());
}

template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::operator()(const TYPE & e, iterator iter) const
{
	assert(iter._list == this);
	for (iter = begin(); iter != end(); iter++)
	{
		if (e == iter._current->element) // si on trouve l'élément retourne iterateur
			return iter;
	}

	return iter;
}

template<typename TYPE>
typename const list<TYPE>& list<TYPE>::operator=(const list<TYPE>& l)
{
	if (this == &l)
		return *this;

	list<TYPE>::iterator it;

	clear();

	for (it = l.begin(); it != l.end(); it++)
		insert(end(), *it);

	return *this;
}



/// Class iterator ///



template<typename TYPE>
list<TYPE>::iterator::iterator()
{
	_list = nullptr;
	_current = nullptr;
}

template<typename TYPE>
list<TYPE>::iterator::~iterator()
{
	_current = nullptr;
	_list = nullptr;
}

template<typename TYPE>
typename const list<TYPE>::iterator & list<TYPE>::iterator::operator=(const iterator & iter)
{
	_current = iter._current;
	_list = iter._list;

	return *this;
}

template<class TYPE>
bool list<TYPE>::iterator::operator==(const iterator& it) const
{
	assert(_list == it._list);
	return _current == it._current;
}

template<typename TYPE>
bool list<TYPE>::iterator::operator!=(const iterator & iter) const
{
	assert(_list == iter._list);
	return _current != iter._current;
}

template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::iterator::operator++(int i) // i++
{
	iterator it;
	it = *this;

	operator++(); // appel de l'opérateur++

	return it;
}

template<typename TYPE>
typename const list<TYPE>::iterator & list<TYPE>::iterator::operator++() // ++i
{
	assert(_current != nullptr);
	assert(_list != nullptr);

	if (_list->_first->previous == _current)
		_current = nullptr;
	else
		_current = _current->next;

	return *this;
}

template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::iterator::operator--(int i) // i--
{
	 assert(_list != nullptr);
	assert(_current != _list->_first);
	iterator it;
	it = *this;

	if (_current == nullptr) // si à la fin
		it._current = _list->_first->previous;
	else
		it._current = _current->previous;


	return it;
}

template<typename TYPE>
typename const list<TYPE>::iterator & list<TYPE>::iterator::operator--() //--i
{
	assert(_current != _list->_first);
	iterator it = *this;
	this->operator--(1);

	return *this;
}

template<typename TYPE>
TYPE & list<TYPE>::iterator::operator*()
{
	assert(_list != nullptr && _current != nullptr); // si itérateur positionné
	assert(_list->_first != nullptr); // si liste non vide
	return _current->element;
}

template<typename TYPE>
const TYPE & list<TYPE>::iterator::operator*() const
{
	assert(_list != nullptr && _current != nullptr); // si itérateur positionné
	assert(_list->_first != nullptr); // si liste non vide
	return _current->element;
}





template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::back()
{
	list<TYPE>::iterator it;
	it._list = this;

	if (_first == nullptr)
	{
		it._current = nullptr;
	}
	else if (_first == _first->previous)
		it._current = _first;
	else
		it._current = _first->previous;

	return it;


	//_first->previous->element;
	//return (end()--);
	//return (_first->previous->element);
}


template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::push_back(const TYPE& ele)
{
	list<TYPE>::iterator it;
	it = insert(end(), ele);
	return it;
}

template<typename TYPE>
typename TYPE* list<TYPE>::iterator::operator->()const
{
	assert(_list != nullptr);
	assert(_current != nullptr);
	assert(_list->_first != nullptr);

	TYPE* temp = &(_current->element);

	//return &(_current->element);
	return temp;
}