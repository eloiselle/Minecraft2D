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
#include "Game_Constexpr.h"

using namespace std;
using namespace sf;     // librairie SFML pour les graphiques et l'audio


class Game
{
public:
    Game();                             // Constructeur
    void run();                         // Boucle principale d'iteration

private:

    // Game Elements
    WorldMap _map;                      // World map
    Player _player;                     // Avatar controlled by user
    vector<Bullet> _shield;		// Tourne a l'entour de _player
    vector<VectorAngle> _shieldVA;		// Distance entre _shieldSphere et _player
    list<Bullet> _bullets;              // Liste des projectiles
    list<Crawler> _bats;                // Liste des chauves souris-enemies
    Boss _boss;                         // Boss en haut de l'ecran
    unsigned int _score;                // Score du joueur

    // Window
    ContextSettings _settings;          // Settings de la _window
    RenderWindow _window;               // Fenetre d'affichage principal
    View _view[5];                      // View disponibles
    static enum ChoosenView {           // Index de view
        NULL_VIEW = 0,                  // View par defaut, ne pas modifier
        NEUTRAL,                        // View centree zoomable
        CAMERA,                         // View avec plein controle
        FOLLOW,                         // Centree sur le joueur
        FOLLOW_Y };                     // Centree sur le X de map et le Y de joueur
    ChoosenView _currentView = NULL_VIEW;   // Index de la view actuelle

    MagnetPosition _mouseMagnet;        // Position magnetique de la souris

    // Text
    string _extraTitle = "";            // Restant du titre de la fenetre
    string _message = STR_INSTRUCTIONS; // Message pendant l'ecran de pause
    Font _fontInvasion2000;             // Font retro avec des gros pixels
    Text _messageOnShader;              // Text afficher par dessus toute la scene
    Text _textToolSwitch;               // 
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
    RectangleShape _playerHealthBar;    // Barre verte qui represente la vie restante du joueur

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
    Music _music;						// Musique de fond
    SoundBuffer _buffBullet;            // Buffer de son des bullet
    SoundBuffer _buffFoes;				// Buffer de son des ennemis
    bool _isAudioActivated = true;      // Option pour desactiver l'audio
    float _volume = 20;


    // Etat
    static enum AppState { RUNNING, PAUSED, BOSS_KILLED, GAME_OVER };   // Etat possibles de application
    string _appStateName[4] = { "Running", "Paused", "Boss Killed", "Game Over" };
    AppState _appState = RUNNING;       // Etat actuel de application

    TOOL _currentTool;                  // Arme actuellement utiliser

    long int _frameFoes;                // Garde en memoire le nombre de frame non affecte par Slow-Mo
    long int _frameRun;                 // Garde en memoire le nombre de frame depuis le debut quand ca run
    long int _frameTotal;               // Garde en memoire le nombre de frame depuis le debut
    Event _event;                       // Event presentement en evaluation

    // Controles
    float _proximityRatio;              // Ratio de proximite de la bordure de la fenetre centré a 1
    bool _bulletWillVanish;             // Si la balle va disparaitre

    //****************************************************************************//

    // Init
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
    void clearPlayerBullet();           // Vide la list<Bullet> des bullet du player

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
    void handleKeypressOnce();                          // Handler des touches de clavier une seule fois
    void handleKeypressContinu();                       // Handler des touches de clavier en continu
    void handleArrowKeysInContinu();                    // Handler des fleches du clavier et WASD
    void handleMouseWheelMoved();                       // Handler de la roulette de souris
    void handleMouseButtonPressedInContinu();           // Handler des boutons de souris
    void handleMouseOnWindowBorders();                  // Gere lorsque la souris est proche des bordures d'ecran
    void switchTool(TOOL tool);                         // Change l'outil/arme

    // Tools
    void shootWeapon();                                 // Utilise l'arme selectionnee
    void shootBullet(Character*);                       // Tire une balle
    void insertBlockAtMouse(int c, int l);              // Insert un block a la position de la souris
    void removeBlockAtMouse(int c, int l);				// Enlève un block à la position de la souris

    float distanceBetweenMP(MagnetPosition& mp1, MagnetPosition& mp2);// Distance trigo entre deux positions
    bool areOnTheSameSquare(MagnetPosition& mp1, MagnetPosition& mp2);// Si les positions sont sur la meme case
    bool isBulletHit(Bullet& b, MagnetPosition& target, int bonusDistance = 0); // Si bullet est en collision

    // Game Handler
    void handlePlayerDeath();                           // Gere quand le joueur meurt
    void manageBossHeight();                            // Gere la hauteur du boss dans la map
    void handleBossMovingDown();                        // Gere quand le boss doit descendre dans la map
    void handleBossDeath();                             // Gere quand le boss meurt
    void handleBatCreation();                           // Gere la creation de chauve-souris
    void createBatAt(int l, int c);                     // Cree une bat a la position
    void manageBossWeapon();                            // Gere l'attaque du boss
    void bossShootBullet();                             // Gere une bullet lancee par le boss
    void addShieldSphere();                             // Ajoute une sphere au shield

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
    void drawOneBullet(Bullet& b);                      // Affiche une seul bullet
    void drawFoes();                                    // Affiche les ennemis
    void drawMovableGui();                              // Affiche les element du GUI comme la cible de la souris
    void flipSpriteHorizontal(Sprite& s);               // Flip un sprite selon son axeVertical
    void printMap();                                    // Affiche le contenu de la map dans _debug
};
