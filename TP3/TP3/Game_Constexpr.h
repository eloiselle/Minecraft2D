/**********************************************************
File  : Game.h
Author: Anthony Cote
Date  : 2018-10-20
Goal  : Conntient les valeurs magiques constexpr
**********************************************************/

#include "list.h"
#include "WorldMap.h"
#include "Player.h"
#include "Bullet.h"
#include "Crawler.h"
#include "Boss.h"

// Messages
constexpr const char * STR_INSTRUCTIONS =   // String a afficher a l'ecran de pause
R"(******************** MINECRAFT 2D ********************
INSTRUCTIONS

Press [Backspace] to call init()

Press [P] to pause/unpause.
Press the arrow/WASD keys to move around
Press [Space] to jump
Press [T] to Teleport

Press [1] to select the Build tool
Press [2] to [9] to change weapon

Roll the mousewheel to zoom-in/zoom-out

Click on the map to modify it.)";

constexpr const char* STR_BOSS_KILLED =     // String a afficher apres avoir tuer le boss
R"(  Boss Killed :D

Press[P] to start
   a new game.)";
constexpr const char* STR_GAME_OVER =       // String a afficher quand le joueur est mort
R"(  GAME OVER :(

Press[P] to start
   a new game.)";

// Window
constexpr char WINDOW_TITLE[] = "Minecraft2D";              // Titre de base de la fenetre
constexpr int MIN_WINDOW_WIDTH = 400;                       // Largeur minimum en pixel de l'ecran
constexpr int MIN_WINDOW_HEIGHT = 300;                      // Hauteur minimum en pixel de l'ecran
constexpr int DEF_WINDOW_WIDTH = 1024;                      // Largeur en pixel de l'ecran par defaut
constexpr int DEF_WINDOW_HEIGHT = 700;                      // Hauteur en pixel de l'ecran par defaut

// Graphics
constexpr int ANTI_ALIASING_LEVEL = 2;                      // Niveau de smoothing des textures
constexpr int SHAPE_THICKNESS = 3;                          // Epaisseur par defaut des shape
constexpr int HEALTH_BAR_HEIGHT = 16;                       // Epaisseur de la bar de hp
constexpr float BORDURE = DEF_WINDOW_HEIGHT / 5;            // Zone de scroll automatique avec la souris

// Run speed
constexpr int STEP_PER_SECOND = 15;                         // Combien de step sont fait a chaque seconde
constexpr int FRAMERATE = 60;                               // Nombre de frame par seconde (FPS)
constexpr int FRAME_WAITED = FRAMERATE / STEP_PER_SECOND;   // Nbr frame attendu avant le prochain step

// View
constexpr int MOUSE_EXPLORE = 10;                           // Vitesse de Deplacement avec la souris
constexpr int ARROW_EXPLORE = 10;                           // Vitesse de Deplacement avec les fleches

// Character size
constexpr int PLAYER_HEIGHT = 16;                           // Hauteur de l'avatar du joueur pour les collisions
constexpr int PLAYER_FOOT = 8;                              // Demi-Largeur de l'avatar du joueur pour les collisions

// Difficulty
constexpr int NB_LIVES = 10;                                // Nombre de vies du joueurs au debut de partie
constexpr int BOSS_HP_MAX = 1000;                           // Nombre de hp du boss au debut
constexpr int NB_STARTING_BATS = 4;                         // Nombre d'ennemis a creer au debut

// Disposition
constexpr int PLAYER_START_COL = 15;                        // Position Col de depart du joueur
constexpr int PLAYER_START_LINE = NBR_EMPTY_LINE_ON_TOP - 1;// Position Line de depart du joueur
constexpr int NB_LINE_BEFORE_EXPAND_MAP = 12;               // Nb de line entre le joueur et le bas de la map pour aggrandir
constexpr int NB_LINE_BETWEEN_BOSS_AND_PLAYER = 8;          // Nb de line entre le joueur et le boss
constexpr int LINE_TO_CREATE_BATS = 5;                      // Ligne sur laquel les premieres bats sont creer
constexpr int SPACE_BETWEEN_BATS = NB_COL / (NB_STARTING_BATS + 1); // Espace entre les chauves souris au depart
constexpr int NB_LINE_DELETE_BULLET_ABOVE_BOSS = 5;         //

// Tools
constexpr int SLOW_MO_EFFECT = 3;                           // Frequence inverse d'action des foes lorsque en slow-mo
constexpr int NB_BOSS_BULLET = 90;                          // Nombre de balles creer par le boss a chaque attaque
constexpr int ANGLE_BOSS_BULLET = 360 / NB_BOSS_BULLET;     // Angle entre chaque balle du boss

// Shield
constexpr int NB_SHIELD_INIT = 1;                           // Nombre initial de Sphere au shield
constexpr int MAX_SHIELD_SPHERES = 12;                      // Nombre maximum de sphere au shield
constexpr int SHIELD_DISTANCE = 15;                         // Distance du shield entre le joueur et les sphere
constexpr int ANGLE_ROTATION_SHIELD = 3;                    // Vitesse de rotation du shield
constexpr int SPHERE_DAMAGE = 50;                           // Degats effectue par Shield

// Score
constexpr int SCORE_BOSS_KILLED = 10000;                    // Bonus de score pour tuer le boss
constexpr int SCORE_BAT = 100;                              // Bonus de score pour tuer un bat
constexpr int SCORE_BLOCK = 10;                             // Bonus de score pour detruire un block
