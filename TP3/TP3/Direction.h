
#pragma once

// Direction
#include <tuple>

constexpr int D4_x[5] = { 0, 1, 0, -1, 0 };                 // Deplacement horizontal selon direction
constexpr int D4_y[5] = { -1, 0, 1, 0, 0 };                 // Deplacement vertical selon direction
constexpr int D4_char[5] = { 'N', 'E', 'S', 'O', 'A' };     // Lettre a utiliser selon direction


//const enum DIRECTION8 { UP = 0, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT };
//constexpr float D8_x[8] = { 0, 0.71, 1, 0.7, 0, -0.71,-1, -0.71 };
//constexpr float D8_y[8] = { -1, -0.71, 0, 0.71, 1, 0.71, 0, -0.71 };

const enum DIRECTION4 { D4_UP = 0, D4_RIGHT, D4_DOWN, D4_LEFT, AUCUNE_DIRECTION }; // Directions numeriques
const enum D4_PROPERTY { D4_DIR, D4_X, D4_Y, D4_CHAR };

//tuple<DIRECTION4, int, int, char> D4[4] =
//{
//    make_tuple(D4_UP,    0, -1, 'N'),
//    make_tuple(D4_RIGHT, 1,  0, 'E'),
//    make_tuple(D4_DOWN,  0,  1, 'S'),
//    make_tuple(D4_LEFT,  -1, 0, 'O')
//};

