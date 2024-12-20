#ifndef Game_HPP
#define Game_HPP

#include "Manager.hpp"
#include "Wave.hpp"

using namespace sf;
using namespace std;

class Game {
private:
    Clock gameTime;
    Text chronoText;
    float chronoDecrease = 0;
    Clock mainClock; //clocks and cooldowns
    Time menuTime;
    float dashCooldown = 3;
    Clock shootCooldown;
    float shootCooldownDecrease = 0;
    float enemiesSpawnCooldownNum = 0;
    Clock enemiesBehaviorCooldown;
    float bonusCooldownNum = 0;
    float timeInRay = 0;
    float meteorCooldownChrono = 0;
    float meteorCooldownLimit = 1;
    float meteorProb = 10;
    float meteorSpeed = 1;
    vector<Clock*> clockTab = { &gameTime, &mainClock, &shootCooldown, &enemiesBehaviorCooldown };
    bool isMainMenu = true; //menus
    bool isCustomMenu = false;
    bool isPauseMenu = false;
    bool isSettingsMenu = false;
    bool isInterlude = false;
    Text interludeStartText;
    Font fontMain; //fonts
    Font fontTitle;
    Text title; //main menu's title
    Text customLevelText;
    vector<Wave*> waveList = {};
    int scoreNum = 0; //score display
    Text score;
    int waveCount = 1;
    float interludeChrono = 0;
    Text deathText;
    Text settingsTextUp;Text settingsTextDown;Text settingsTextLeft;Text settingsTextRight;Text settingsTextShoot; Text settingsTextDash;
    Texture table;
    Texture pauseHeaderTexture; Sprite pauseHeader;
    Texture pauseBgTexture; Sprite pauseBg;
    Texture playButtonOffTexture; Texture playButtonOnTexture; Sprite playButton; //menu buttons
    Texture exitButtonOffTexture; Texture exitButtonOnTexture; Sprite exitButton;
    Texture arrowButtonOffTexture; Texture arrowButtonOnTexture; Sprite arrowButtonLeft; Sprite arrowButtonRight;
    Texture mapButtonOffTexture;Texture mapButtonOnTexture;  Sprite mapButton;
    Texture settingsButtonOffTexture;Texture settingsButtonOnTexture;  Sprite settingsButton;
    Texture settingsButtonArrowTexture; Texture settingsButtonDashTexture; Texture settingsButtonShootTexture; 
    Sprite settingsButtonUp; Sprite settingsButtonDown; Sprite settingsButtonLeft; Sprite settingsButtonRight; Sprite settingsButtonShoot; Sprite settingsButtonDash;
    Sprite currentPlayerIcon;
    Text classDescription;
    Text classDescriptionStats1; Text classDescriptionStats2; Text classDescriptionStats3;
    int shipNumber = 1;
    Texture menuButtonOffTexture; Texture menuButtonOnTexture; Sprite menuButton; Text menuText;
    Texture resumeButtonOffTexture; Texture resumeButtonOnTexture; Sprite resumeButton; Text resumeText;
    Texture pauseExitButtonOffTexture; Texture pauseExitButtonOnTexture; Sprite pauseExitButton; Text pauseExitText;
    Texture adminButtonOffTexture; Texture adminButtonOnTexture; Sprite adminButton; Text adminText;
    Text hpText; Text hpBonusText; //hp display
    Texture hpBarTexture5; Texture hpBarTexture10;
    Sprite hpBar;
    Texture hpDotTexture;
    Sprite hpDot;
    Texture bossHpTableTexture;
    Texture cursorTexture; //cursor
    Sprite cursor;
    Texture backgroundTexture; //background
    Texture backgroundAlienTexture;
    Texture backgroundNautolanTexture;
    Sprite background;
    Texture obstacleTexture = meteorTexture;
    Player player; //player
    bool isAdmin = false;
    Vector2f inputMovement;
    Color playerAmmoColor = Color(255, 255, 255);
    float playerPreviousSpeed = player.getSpeed();
    Texture dashIconRedTexture; Texture dashIconGreenTexture; Sprite dashIcon;
    Texture dashArrowGreenTexture; Texture dashArrowRedTexture; Sprite dashArrow;
    SoundBuffer shootSoundBuffer; Sound shootSound; //sounds
    SoundBuffer shootEnemySB; Sound shootEnemy;
    Sound explosionSound;
    SoundBuffer musicSB; Sound music;
    SoundBuffer menuMusicSB; Sound menuMusic;
    SoundBuffer uiSB; Sound uiSound;
    SoundBuffer uiClicSB; Sound uiClicSound;
    vector<Sound*> soundVector = { &music, &menuMusic, &uiSound, &shootSound, &shootEnemy, &explosionSound, &uiClicSound };
    RectangleShape volumeBar, volumeIndicator;
    float shade = 0;
    RectangleShape screenEffect = RectangleShape(Vector2f(screenWidth, screenHeight));
public:
    Keyboard::Scancode scancodeUp = Keyboard::Scancode::W;
    Keyboard::Scancode scancodeDown = Keyboard::Scancode::S;
    Keyboard::Scancode scancodeLeft = Keyboard::Scancode::A;
    Keyboard::Scancode scancodeRight = Keyboard::Scancode::D;
    Keyboard::Scancode scancodeDash = Keyboard::Scancode::LShift;
    Keyboard::Scancode scancodeShoot = Keyboard::Scancode::Space;    

    //manager creation
    ObjectManager* manager = ObjectManager::getInstance();
    //manager creation
    bool isBossAlive();
    Game();
    void userInput();
    void update();
    void display();
    void pauseMenu();
    void customMenu();
    void settingsMenu();
    void mainMenu();
    void gameLoop();
};

#endif