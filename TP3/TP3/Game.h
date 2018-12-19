/**********************************************************
File  : Game.h
Author: Anthony Cote
Date  : 2018-10-20
Goal  : Lance une partie de Minecraft2D
        C'est un jeu de plateforme :
        - le joueur se deplace avec les fleches ou WASD
        - le joueur peux selectionner un outil/arme avec les chiffres du clavier
        - le joueur utilise la souris pour utilise l'outil actif
        - la touche [P] met sur pause
        - la touche [T] teleporte le joueur
        - la roulette de souris permet de zoomer
        - les blocs sont destructibles apres un nombre de dommage
        - les ennemi peuvent etre tuer
        - Le boss a une barre de vie en haut de l'ecran
**********************************************************/
#pragma once
#include "pch.h"

#include "WorldMap.h"
#include "Player.h"
#include "Bullet.h"
#include "Crawler.h"
#include "Boss.h"

using namespace std;
using namespace sf;     // librairie SFML pour les graphiques et l'audio

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
R"(Boss Killed :D

Press[P] to start a new game)";
constexpr const char* STR_GAME_OVER =       // String a afficher quand le joueur est mort
R"(GAME OVER :(

Press[P] to start a new game)";
// Window
constexpr char WINDOW_TITLE[] = "Minecraft2D";              // Titre de base de la fenetre
constexpr int MIN_WINDOW_WIDTH = 400;                       // Largeur minimum en pixel de l'ecran
constexpr int MIN_WINDOW_HEIGHT = 300;                      // Hauteur minimum en pixel de l'ecran
constexpr int DEF_WINDOW_WIDTH = 1024;                      // Largeur en pixel de l'ecran par defaut
constexpr int DEF_WINDOW_HEIGHT = 700;                      // Hauteur en pixel de l'ecran par defaut
constexpr int ANTI_ALIASING_LEVEL = 2;                      // Niveau de smoothing des textures

constexpr float BORDURE = DEF_WINDOW_HEIGHT / 5;            // Zone de scroll automatique avec la souris

// Run speed
constexpr int STEP_PER_SECOND = 15;                         // Combien de step sont fait a chaque seconde
constexpr int FRAMERATE = 60;                               // Nombre de frame par seconde (FPS)
constexpr int FRAME_WAITED = FRAMERATE / STEP_PER_SECOND;   // Nbr frame attendu avant le prochain step
constexpr int MOUSE_EXPLORE = 10;                           // Vitesse de Deplacement avec la souris
constexpr int ARROW_EXPLORE = 10;                           // Vitesse de Deplacement avec les fleches
constexpr int NB_LINE_BEFORE_EXPAND_MAP = 12;               // Nb de line entre le joueur et le bas de la map pour aggrandir
constexpr int NB_LINE_BETWEEN_BOSS_AND_PLAYER = 8;          //

// Character size
constexpr int PLAYER_HEIGHT = 16;                           // Hauteur de l'avatar du joueur pour les collisions
constexpr int PLAYER_FOOT = 8;                              // Demi-Largeur de l'avatar du joueur pour les collisions

// Game
constexpr int NB_LIVES = 10;                                // Nombre de vies du joueurs au debut de partie
constexpr int PLAYER_START_C = 15;                          // Position Col de depart du joueur
constexpr int PLAYER_START_L = NBR_EMPTY_LINE_ON_TOP - 1;   // Position Line de depart du joueur
constexpr int NB_STARTING_BATS = 4;                         // Nombre d'ennemis a creer au debut
constexpr int SPACE_BETWEEN_BATS = NB_COL / (NB_STARTING_BATS + 1); // Espace entre les chauves souris au depart
constexpr int NB_SHIELD = 6;                                // Nombre de spheres dans le bouclier
constexpr int SHIELD_ANGLE = 360 / NB_SHIELD;               // Angle entre les spheres du bouclier
constexpr int SLOW_MO_EFFECT = 4;                           // Frequence inverse d'action des foes lorsque en slow-mo
constexpr int LINE_TO_CREATE_BATS = 5;                      // Ligne sur laquel les premieres bats sont creer
constexpr int NB_BOSS_BULLET = 90;                          // Nombre de balles creer par le boss a chaque attaque
constexpr int ANGLE_BOSS_BULLET = 360 / NB_BOSS_BULLET;     // Angle entre chaque balle du boss

// Score
constexpr int SCORE_BOSS_KILLED = 10000;                    // Bonus de score pour tuer le boss
constexpr int SCORE_BAT = 100;                              // Bonus de score pour tuer un bat
constexpr int SCORE_BLOCK = 10;                             // Bonus de score pour detruire un block

// OPTIONS
constexpr bool MUSIQUE = false;                             // Option pour desactiver l'audio

class Game
{
private:

    // Game Elements
    WorldMap _map;                      // World map
    Player _player;                     // Avatar controlled by user
    Bullet _shieldSphere[NB_SHIELD];    // Tourne a l'entour de _player
    VectorAngle _shieldVA[NB_SHIELD];   // Distance entre _shieldSphere et _player
    list<Bullet> _bullets;              // Liste des projectiles
    list<Crawler> _bats;                // Liste des chauves souris-enemies
    Boss _boss;                         // Boss en haut de l'ecran
    unsigned int _score;                // Score du joueur

    // Window
    ContextSettings _settings;          // Settings de la _window
    RenderWindow _window;               // Fenetre d'affichage principal
    View _view[5];                      // View disponibles
    static enum ChoosenView { NULL_VIEW = 0, NEUTRAL, CAMERA, FOLLOW, FOLLOW_Y };   // Index de view
    ChoosenView _currentView = NULL_VIEW;   // Index de la view actuelle

    MagnetPosition _mouseMagnet;        // Position magnetique de la souris

    // Text
    string _extraTitle = "";            // Restant du titre de la fenetre
    string _message = STR_INSTRUCTIONS; // Message pendant l'ecran de pause
    Font _fontInvasion2000;             // Font retro avec des gros pixels
    Text _messageOnShader;              // Text afficher par dessus toute la scene
    Text _debugInfo;                    // Text afficher par dessus toute la scene
    string _debug = "DEBUG";            // Message modifiable pour tracker les variables en temps réel

    // Shapes
    RectangleShape _shader;             // Shader qui applique une couche noir transparente sur l'ecran
    CircleShape _mouseCoord;            // Position de la souris qui ignore le changement fait par _view
    RectangleShape _mouseSquare;        // Carre qui affiche sur quelle case la souris se trouve
    RectangleShape _playerShape;        // Carre vert
    static enum { UNFRIENDLY = 0, FRIENDLY };   // Si les balles blesse le joueur ou le boss
    CircleShape _bulletShape[2];        // Shape des bullets
    CircleShape _aimingSight;           // Cercle vide comme cible
    RectangleShape _bossHealthBar;      // Barre rouge qui represente la vie restante du boss

    // Sprites
    Sprite  _playerSprite;              // Sprite du joueur
    Image _playerImage;					// Image de l'avatar
    Texture _playerTexture;				// Texture de l'avatar
    Sprite _playerSprites[4][9];		// Sprites de l'avatar

    int _animFrame = 3;					// indice i du tableau de sprites
    int _animType = 0;					// indice j du tableau de sprites
    static enum ANIM_FRAME {
        IDLE_LEFT = 0, IDLE_RIGHT = 1, RUN_RIGHT = 2,
        DO = 3, AIR = 4, CRY = 5,
        WALK_RIGHT = 6, RUN_LEFT = 7, WALK_LEFT = 8
    };

    Image _batImage;                    // Image du bat pour modification de transparence
    Texture _batTexture;                // Texture du bat
    Sprite _batSprite[4][4];            // Sprite du bat

    Texture _tileset;                   // Source d'image pour les sprite
    Sprite _tileSprite[5][NB_VERSION_BLOCK];    // Ensemble de sprite pour afficher la map [TYPE][VERSION]

    // Music
    Music _music;						// musique
    SoundBuffer _buffBullet;            // Buffer de son des bullet
    SoundBuffer _buffFoes;				// Buffer de son des ennemis

    // Etat
    static enum AppState { RUNNING, PAUSED, BOSS_KILLED, GAME_OVER };   // Etat possibles de application
    string _appStateName[4] = { "Running", "Paused", "Boss Killed", "Game Over" };
    AppState _appState = RUNNING;       // Etat actuel de application

    TOOL _currentTool;                  // Arme actuellement utiliser

    long int _frameRun;                 // Garde en memoire le nombre de frame depuis le debut quand ca run
    long int _frameTotal;               // Garde en memoire le nombre de frame depuis le debut
    Event _event;                       // Event presentement en evaluation

    // Controles
    float _proximityRatio;              // Ratio de proximite de la bordure de la fenetre centré a 1
    bool _bulletWillVanish;             // Si la balle va disparaitre
public:

    // Init
    Game();                             // Constructeur
    void init();                        // Initialization globale
    void initWindow();                  // Initialization de la fenetre
    void initSprites();                 // Initialization des images/textures
    void initTexts();                   // Initialization des polices de caracteres
    void initShapes();                  // Initialization des formes geometriques
    void initViews();                   // Initialization des view
    void initPlayer();                  // Initialization du joueur
    void initShield();                  // Initialization du bouclier
    void initBoss();                    // Initialization du Boss
    void initFoes();                    // Initialization des ennemis
    void initWorldMap();                // Initialization du labyrinthe
    void initMusic();                   // Initialisation de la musique
    void initSounds();                  // Initialisation des sons

    Sprite initOneSprite(unsigned int line, unsigned  int col, Texture & texture,
        unsigned int tileSize = TILE_SIZE, unsigned  int separation = 0);
    // Initialize un seul sprite a partir de ses proprietes

    // Animation
    void managePlayerAnimation();                       // Gere les animation du joueur
    void animRight();                                   // Gere l'animation quand le joueur se deplace vers la droite
    void animLeft();                                    // Gere l'animation quand le joueur se deplace vers la gauche
    void animIdle();                                    // Gere l'animation quand le joueur ne se deplace pas
    void animAir();                                     // Gere l'animation quand le joueur se deplace dans les air

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
    bool areOnTheSameSquare(MagnetPosition & mp1, MagnetPosition & mp2);
    void shootWeapon();                                 //
    void shootBullet(Character*);                       // Tire une balle
    void insertBlockAtMouse(int c, int l);              // Insert un block a la position de la souris
    void removeBlockAtMouse(int c, int l);				// Enlève un block à la position de la souris
    void handleMouseOnWindowBorders();                  // Gere lorsque la souris est proche des bordures d'ecran

    // Game Handler
    void handlePlayerDeath();                           // Gere quand le joueur meurt
    void manageBossHeight();                            // Gere la hauteur du boss dans la map
    void handleBossMovingDown();                        // Gere quand le boss doit descendre dans la map
    void handleBossDeath();                             // Gere quand le boss meurt
    void handleBatCreation();                           // Gere la creation de chauve-souris
    void manageBossWeapon();                            // Gere l'attaque du boss
    void bossShootBullet();                             // Gere une bullet lancee par le boss

    // Window View
    bool isInMap(int x, int y) const;                   // Retourne si les coords sont dans la map
    bool isInMap(MagnetPosition & mp) const;            // Retourne si la MagnetPosition est dans la map
    bool isMouseInWindow()const;                        // Retourne si la souris est dans la fenetre
    bool isInWindow(int x, int y) const;                // Retourne si les coords sont a l'interieur de la fenetre
    bool isInWindow(MagnetPosition & mp) const;         // Retourne si la MagnetPosition est dans la fenetre
    bool isInWindow(Vector2i & v) const;                // Retourne si l'objet est a l'interieur de la fenetre
    bool isMouseInMap()const;                           // Retourne si la souris est dans la map
    void updateViewlessMouseCoord();                    // Calcule la position interne de la souris
    bool canTeleportAtMouse();                          // Verify si on peux se teleporter sur la souris

    // Game Logic
    void mainLoop();                                    // Boucle principale d'iteration
    void managePlayer();                                // Gere l'avatar du joueur mais pas les controles
    void manageBoss();                                  // Gere le boss
    void manageFoes();                                  // Gere les ennemis
    void manageOneFoe(list<Crawler>::iterator& c);      // Gere un seul ennemi
    void manageMapExpansion();                          // Gere quand on doit agrandir la map

    void manageSphereShield();                          // Gere le bouclier
    void manageBullets();                               // Gere les projectiles
    bool toolIsAShooter()const;                         // Regarde si _currentTool lance des bullets

    // Edge detection
    void managePlayerJump();                            // Gere la physic du jump du joueur
    bool playerIsOnTheGround()const;                    // Retourne si le joueur est en contact avec le sol
    int pixelsBeforeTopBorder()const;                   // Nombre de pixel avant de tomber dans l'autre case du haut
    int pixelsBeforeBottomBorder()const;                // Nombre de pixel avant de tomber dans l'autre case du bas
    int pixelsToRise()const;                            // Nombre de pixel qu'on peux monter sans collision avec momentum
    int pixelsToFall()const;                            // Nombre de pixel qu'on peux tomber sans collision avec momentum
    bool playerHitTheCeiling()const;                    // Detecte si on va entrer en collision avec le plafond
    bool playerIsLanding()const;                        // Detecte si on va entrer en collision avec le plancher

    // Move
    void moveBoss();                                    // Deplace le boss en ellipse
    void tryToMove(DIRECTION4 dir, SidewayCharacter& player); // SidewayCharacter essaye de se deplacer
    void tryToMove(DIRECTION4 dir, TopDownCharacter& mover);  // TopDownCharacter essaye de se deplacer
    void tryToMoveInDirection(Crawler & c, DIRECTION4 dir);   // Crawler essaye de se deplacer
    void collisionBulletBlock(Bullet& b);               // Check les collision entre un bullet et le block sous lui
    void collisionBulletFoes(Bullet& b);                // Check les collision et les bullet et les ennemis
    void collisionBulletPlayer(Bullet & b);             // Check les collision entre un bullet et le joueur

    // Draw
    void drawWindow();                                  // Met a jour le contenu de la window
    void updateViews();                                 // met a jour les view
    void updateWindowTitle();                           // Met a jour le titre de la fenetre
    void drawBossHealthBar();                           // Affiche la barre de hp du boss
    void drawThingsDirectlyOnTheScreen();               // Affiche les elements non affecter par la view
    void drawGrid();                                    // Affiche la grille de application
    void drawPlayer();                                  // Affiche les objets mobiles
    void drawShield();                                  // Affiche les sphere du bouclier
    void drawBullets();                                 // Affiche les projectiles
    void drawFoes();                                    // Affiche les ennemis
    void drawMovableGui();                              // Affiche les element du GUI comme la cible de la souris
    void flipSpriteHorizontal(Sprite& s);               // Flip un sprite selon son axeVertical
    void printMap();                                    // Affiche le contenu de la map dans _debug
};
