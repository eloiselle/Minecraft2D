
#pragma once

// Direction


const enum DIRECTION4 { NORD = 0, EST, SUD, OUEST, AUCUNE_DIRECTION}; // Directions numeriques
constexpr int D4_x[5] = { 0, 1, 0, -1, 0 };                 // Deplacement horizontal selon direction
constexpr int D4_y[5] = { -1, 0, 1, 0, 0 };                 // Deplacement vertical selon direction
constexpr int D4_char[5] = { 'N', 'E', 'S', 'O', 'A' };     // Lettre a utiliser selon direction


const enum DIRECTION8 { UP = 0, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT };
constexpr float D8_x[8] = { 0, 0.71, 1, 0.7, 0, -0.71,-1, -0.71 };
constexpr float D8_y[8] = { -1, -0.71, 0, 0.71, 1, 0.71, 0, -0.71 };
