/**********************************************************
File  : main.cpp
Author: Anthony Cote
Date  : 2018-10-20
Goal  : Lance le jeu
**********************************************************/

#include "Game.h"

int main(int argc, const char **argv)
{
    srand(time(NULL));

    Game g;
    g.mainLoop();

    return 0;
}
