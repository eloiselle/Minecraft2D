#pragma once
#include "Entity.h"
class Character : public Entity, public Killable
{
public:
    Character();
    ~Character();
};
