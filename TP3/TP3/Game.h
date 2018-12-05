/**********************************************************
File  : Game.h
Author: Anthony Cote
Date  : 2018-10-20
Goal  : Solutionne un labyrinthe visuellement en SFML
        avec l'aide d'une stack de deplacement
**********************************************************/
#pragma once
#include "pch.h"

#include "WorldMap.h"
#include "Player.h"
#include "Bullet.h"
#include "TopDownCharacter.h"
#include "Crawler.h"
#include "MapRandomizer.h"

using namespace std;
using namespace sf;

// Map
constexpr char DEFAULT_FILENAME[] = "dataGrid.txt";

// Messages
constexpr const char * DEFAULT_MESSAGE =
R"(******************** MINECRAFT 2D ********************

INSTRUCTIONS

Press [Backspace] to call init()

Press [Space] to pause/unpause.

Press [1] to [4] to change the view

Press the arrow/WASD keys to move around

Roll the mousewheel to zoom-in/zoom-out

Click on the map to modify it.)";

// Window
constexpr char WINDOW_TITLE[] = "Minecraft2D";              // Titre de base de la fenetre
constexpr int MIN_WINDOW_WIDTH = 400;                       // Largeur minimum en pixel de l'ecran
constexpr int MIN_WINDOW_HEIGHT = 300;                      // Hauteur minimum en pixel de l'ecran
constexpr int DEF_WINDOW_WIDTH = 1024;                      // Largeur en pixel de l'ecran par defaut
constexpr int DEF_WINDOW_HEIGHT = 700;                      // Hauteur en pixel de l'ecran par defaut
constexpr int ANTI_ALIASING_LEVEL = 2;                      // Niveau de smoothing des textures

// Size
//constexpr pixel_t TILE_SIZE = 32;                           // Taille des tiles normaux
constexpr float BORDURE = DEF_WINDOW_HEIGHT / 5;            // Zone de scroll automatique avec la souris

// Run speed
constexpr int STEP_PER_SECOND = 15;                         // Combien de step sont fait a chaque seconde
constexpr int FRAMERATE = 60;                               // Nombre de frame par seconde (FPS)
constexpr int FRAME_WAITED = FRAMERATE / STEP_PER_SECOND;   // Nbr frame attendu avant le prochain step
constexpr int MOUSE_EXPLORE = 10;                           // Vitesse de Deplacement avec la souris
constexpr int ARROW_EXPLORE = 10;                           // Vitesse de Deplacement avec les fleches

class Game
{
private:

    // Game Elements
    WorldMap _map;                      // World map
    Player _player;                     // Avatar controlled by user
    Bullet _yoyo;                       // Tourne a l'entour de _player
    VectorAngle _yoyoString;            // Distance entre _yoyo et _player
    Crawler _spider;                    // Ennemi qui se promene dans la grille

    list<Bullet> _bullets;              // Liste des projectiles

    // Window
    ContextSettings _settings;          // Settings de la _window
    RenderWindow _window;               // Fenetre d'affichage principal
    View _view[4];
    static enum ChoosenView { NULL_VIEW = 0, NEUTRAL, CAMERA, FOLLOW };
    ChoosenView _currentView = NULL_VIEW;

    MagnetPosition _mouseMagnet;        // Position magnetique de la souris

    // Text
    string _extraTitle = "";            // Restant du titre de la fenetre
    string _message = DEFAULT_MESSAGE;  // Message pendant l'ecran de pause
    Font _fontInvasion2000;             // Font retro avec des gros pixels
    Text _texteInstructions;            // Text afficher par dessus toute la scene
    Text _debugInfo;                    // Text afficher par dessus toute la scene
    string _debug = "DEBUG";            // Message modifiable pour tracker les variables en temps réel

    // Shapes
    RectangleShape _shader;             // Shader qui applique une couche noir transparente sur l'ecran
    CircleShape _mouseCoord;            // Position de la souris qui ignore le changement fait par _view
    RectangleShape _mouseSquare;        // Carre qui affiche sur quelle case la souris se trouve
    RectangleShape _playerShape;        // Carre vert
    CircleShape _bulletShape;           // Cercle rouge

    // Sprites
    Image _spiderImage;                 // Image du robot pour modification de transparence
    Texture _spiderTexture;             // Texture du robot
    Texture _tileset;                   // Source d'image pour les sprite
    Sprite _spiderSprite;               // Sprite du robot
    Sprite _tileSprite[5];              // Ensemble de sprite pour afficher la map

    // Etat
    static enum AppState { RUNNING, PAUSED };                           // Etat possibles de application
    AppState _appState = RUNNING;       // Etat actuel de application
    long int _frameRun;                 // Garde en memoire le nombre de frame depuis le debut quand ca run
    long int _frameTotal;               // Garde en memoire le nombre de frame depuis le debut
    Event _event;                       // Event presentement en evaluation

    // Controles
    float _proximityRatio;              // Ratio de proximite de la bordure de la fenetre centré a 1

public:

    // Init
    Game();                             // Constructeur
    void init();                        // Initialization globale
    void initWindow();                  // Initialization de la fenetre
    void initSprites();                 // Initialization des images/textures
    void initTexts();                   // Initialization des polices de caracteres
    void initShapes();                  // Initialization des formes geometriques
    void initViews();                   // Initialization des view
    void initGameElements();            // Initialization des elements qui se deplacent
    void initWorldMap(const char* fileName = DEFAULT_FILENAME);   // Initialization du labyrinthe
    Sprite initOneSprite(unsigned int line, unsigned  int col, Texture & texture,
        unsigned int tileSize = TILE_SIZE, unsigned  int separation = 0);
    // Initialize un seul sprite a partir de ses proprietes

    // Event
    void quitApplication();                             // Quitte l'application
    void inputActivatedOnlyTheFirstTime();              // Get input une seule fois
    void inputActivatedInContinu();                     // Get input a repetition

    // Handler
    void handlePausing();                               // Verifi si on doit changer l'etat de pause
    View& handleResizeWindow();                         // Handler le redimensionnement de la fenetre
    void handleKeypress();                              // Handler des touches de clavier
    void handleArrowKeys();                             // Handler des fleches du clavier et WASD
    void handleMouseWheelMoved();                       // Handler de la roulette de souris
    void handleMouseButtonPressed();                    // Handler des boutons de souris
    void shootBullet();                                 // Tire une balle
    void changeBlockAtMouse();                          // Change un block a la position de la souris
    void handleMouseOnWindowBorders();                  // Gere lorsque la souris est proche des bordures d'ecran


    // Window View
    bool isInMap(int x, int y) const;                   // Retourne si les coords sont dans la map
    bool isInMap(MagnetPosition & mp) const;            // Retourne si la MagnetPosition est dans la map
    bool isMouseInWindow()const;                        // Retourne si la souris est dans la fenetre
    bool isInWindow(int x, int y) const;                // Retourne si les coords sont a l'interieur de la fenetre
    bool isInWindow(MagnetPosition & mp) const;         // Retourne si la MagnetPosition est dans la fenetre
    bool isInWindow(Vector2i & v) const;                // Retourne si l'objet est a l'interieur de la fenetre
    bool isMouseInMap()const;                           // Retourne si la souris est dans la map
    void updateViewlessMouseCoord();                    // Calcule la position interne de la souris

    // Terraria
    void mainLoop();                                    // Boucle principale d'iteration
    void managePlayer();                                // Gere l'avatar du joueur mais pas les controles
    void manageFoes();                                  // Gere les ennemis
    void manageBullets();                               // Gere les projectiles

    // Movement & Collision
    void managePlayerJump();
    bool playerIsOnTheGround();
    // Gere les collision et le deplacement du jump
    int pixelsBeforeTopBorder();                        // Nombre de pixel avant de tomber dans l'autre case du haut
    int pixelsBeforeBottomBorder();                     // Nombre de pixel avant de tomber dans l'autre case du bas
    int pixelsToRise();                                 // Nombre de pixel qu'on peux monter sans collision avec momentum
    int pixelsToFall();                                 // Nombre de pixel qu'on peux tomber sans collision avec momentum
    bool playerHitTheCeiling();                         // Detecte si on va entrer en collision avec le plafond
    bool playerIsLanding();                             // Detecte si on va entrer en collision avec le plancher
    void tryToMove(int dir, SidewayCharacter& player);  // SidewayCharacter essaye de se deplacer
    void tryToMove(DIRECTION8 dir, TopDownCharacter& mover);  // TopDownCharacter essaye de se deplacer

    // Draw
    void drawWindow();                                  // Met a jour le contenu de la window
    void updateViews();                                 // met a jour les view
    void updateWindowTitle();                           // Met a jour le titre de la fenetre
    void drawThingsDirectlyOnTheScreen();               // Affiche les elements non affecter par la view
    void drawGrid();                                    // Affiche la grille de application
    void drawMovableObjects();                          // Affiche les objets mobiles
    void flipSpriteHorizontal(Sprite& s);               // Flip un sprite selon son axeVertical
    void printMap();
};
