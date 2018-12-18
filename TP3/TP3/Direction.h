/*****************************************************************************
File  : Direction.h
Author: Anthony Cote
Date  : 2018-12-01
Goal  : Tableaux de constantes pour avoir un vecteur de deplacement
        X ou Y a partir de la direction.
******************************************************************************/
#pragma once

// Direction4
const enum DIRECTION4 { UP = 0, RIGHT, DOWN, LEFT, AUCUNE_DIRECTION }; // Directions numeriques
const enum D4_PROPERTY { X = 0, Y = 1 };

constexpr int D4[4][2] = { {0,-1},{1,0},{0,1},{-1,0} };
// Usage standard : D4[UP][X];

// Direction8
//const enum DIRECTION8 { UP = 0, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT };
//constexpr float D8_x[8] = { 0, 0.71, 1, 0.7, 0, -0.71,-1, -0.71 };
//constexpr float D8_y[8] = { -1, -0.71, 0, 0.71, 1, 0.71, 0, -0.71 };
