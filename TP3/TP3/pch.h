// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here
#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include <time.h>
#include <math.h>

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>
#include <cassert>

#include <vector>
#include <list>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

constexpr float PI = 3.141592653589793f;

// TYPE DEFINITION
typedef float pixel_t;  // 
typedef int tile_t;     // 


// Map
constexpr int TILE_SIZE = 32;
constexpr int RATIO = TILE_SIZE;
constexpr int HALF_TILE_SIZE = TILE_SIZE / 2;

#endif //PCH_H
