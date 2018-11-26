/*****************************************************************************
File  : Const.h
Author: Anthony Cote
Date  : 2018-05-05
Goal  : Contient les constantes a un seul endroit
******************************************************************************/
#pragma once
#include "pch.h"

// TYPE DEFINITION
typedef float pixel_t;
typedef unsigned int tile_t;

// CONSTANTES

constexpr bool SKIP_MAIN_MENU = false;
constexpr bool IS_DEBUG = false;

// Window
//constexpr char TITRE[] = "Bomberman";
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 608;
//constexpr char ICONE[] = "Ress\\sdl_icone.bmp";

// Files
//constexpr char TILESET_FILE[] = "Ress\\customTileset 2x.bmp";
//constexpr char MAP1[] = "Ress\\map1.txt";

// Font
//constexpr char ANGELINA[] = "Ress\\angelina.ttf";
//constexpr char ARIAL[] = "Ress\\arial.ttf";
//constexpr char INVASION2000[] = "Ress\\INVASION2000.TTF";

// Map
constexpr int TILE_SIZE = 32;
constexpr int RATIO = TILE_SIZE;
constexpr int HALF_TILE_SIZE = TILE_SIZE / 2;
//constexpr int DEATH_TILE_SIZE = 24;

constexpr int MAP_SIZE_X = SCREEN_WIDTH / TILE_SIZE;
constexpr int MAP_SIZE_Y = SCREEN_HEIGHT / TILE_SIZE;

const enum DIR8 { UP = 0, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT };
const float D8_x[8] = { 0, 0.71, 1, 0.7, 0, -0.71,-1, -0.71 };
const float D8_y[8] = { -1, -0.71, 0, 0.71, 1, 0.71, 0, -0.71 };
