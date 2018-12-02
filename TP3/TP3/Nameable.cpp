#include "Nameable.h"



Nameable::Nameable()
{
}


Nameable::~Nameable()
{
}


// Retourne le nom
const char* Nameable::getName() const
{
    if (_name == nullptr)
        return "\0";

    return _name;
}

// Modifie le nom
void Nameable::setName(const char* name)
{
    clearName();

    int nameLength = strlen(name);
    if (nameLength > 0)
    {
        // Modifi le nom
        _name = new char[nameLength + 1];
        strcpy_s(_name, nameLength + 1, name);
    }
}


// Vide le nom
void Nameable::clearName()
{
    delete[] _name;
    _name = nullptr;
}
