// Shoot'em up!.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Audio.hpp>
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace sf;
using namespace std;

float screenWidth = 780.f, screenHeight = 900.f;
RenderWindow window(VideoMode(screenWidth, screenHeight), "~Shooty~", Style::Close);
//textures
Texture playerShip;
Texture basicShip;
Texture specShip;
Texture doubleBarrelShip;
Texture bossCruiser;
Texture alienShip;
Texture bossAlienShip;
Texture nautolanShip;
Texture bossNautolanShip;
Texture ammoTexture;
Texture spinningAmmoTexture;
Texture bonusHealTexture;

class Entity {
protected:
    float lifeTime = 0;
    float frameRate = 1.f;
    int maxHp, hp, ammoAmount=1, type=0;
    float speed;
    Texture texture;
    Sprite sprite;
    Vector2f behavior;
    Clock shootCooldown;
    string ammoTexturePath;
    vector<Vector2f> ammoDirections;
    vector<float> ammoPositions = {};
public:
    Entity(Texture _TEXTURE = basicShip, Vector2f _SCALE=Vector2f(1.5f, 1.5f), int _MAXHP = 10, float _SPEED = 100.f, Vector2f _BEHAVIOR = Vector2f(0.f, 1.f)) : texture(_TEXTURE), maxHp(_MAXHP), hp(_MAXHP), speed(_SPEED), behavior(_BEHAVIOR) {
        sprite.setTexture(texture);
        sprite.setScale(_SCALE);
        sprite.setOrigin(Vector2f(texture.getSize()) / 2.f);
    }
    ~Entity() { /*cout << "\n\033[31mdeleted an entity\033[0m\n";*/ }

    float getLifeTime() { return lifeTime; }
    void addToLifeTime(float value) { lifeTime += value; }
    float getFrameRate() { return frameRate; }
    void setFrameRate(float value) { frameRate = value; }
    void addToFrameRate(float value) { frameRate += value; }
    Sprite* getSprite() { return &sprite; }
    Texture getTexture() { return texture; }
    Vector2f getPos() { return sprite.getPosition(); }
    void setColor(int r, int g, int b) { return sprite.setColor(Color(r, g, b)); }
    int getHeight() { return sprite.getGlobalBounds().height; }
    int getWidth() { return sprite.getGlobalBounds().width; }
    float getLeft() { return sprite.getGlobalBounds().left; }
    float getRight() { return (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width); }
    float getUp() { return sprite.getGlobalBounds().top; }
    float getDown() { return (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height); }
    void setX(float x) { sprite.setPosition(Vector2f(x, sprite.getPosition().y)); }
    void setY(float y) { sprite.setPosition(Vector2f(sprite.getPosition().x, y)); }

    int getHp() { return hp; }
    int getMaxHp() { return maxHp; }
    void decreaseHp(int value=1) {
        hp -= value;
    }
    Vector2f getBehavior() { return behavior; }
    void setBehavior(Vector2f value) { behavior = value; }
    Clock getShootCooldown() { return shootCooldown; }
    void restartShootCooldown() { shootCooldown.restart(); }
    int getAmmoAmount() { return ammoAmount; }
    vector<Vector2f> getAmmoDirections() { return ammoDirections; }
    vector<float> getAmmoPositions() { return ammoPositions; }
    int getType() { return type; }
    void setType(int typev) { type = typev; }

    void move(Vector2f value) {
        sprite.move(value*speed);
    }

    bool isColiding(Entity other) {
        if (sprite.getGlobalBounds().intersects(other.getSprite()->getGlobalBounds())) { return true; }
        return false;
    }

    void continueAnimation() {
        if (sprite.getTextureRect().left >= texture.getSize().x - sprite.getTextureRect().width) {
            sprite.setTextureRect(IntRect(0, 0, sprite.getTextureRect().width, sprite.getTextureRect().height));
        }
        else {
            IntRect rect = sprite.getTextureRect();
            rect.left += sprite.getTextureRect().width;
            sprite.setTextureRect(rect);
        }
    }
};

class Player : public Entity {
public:
    Player() : Entity(playerShip, Vector2f(1.5f, 1.5f), 10, 300.f, Vector2f(0.f, 1.f)) {
        sprite.setPosition(Vector2f(screenWidth / 2.f, screenHeight * 0.8f));
    }
};

class Enemy : public Entity {
public:
    Enemy(Texture _TEXTURE, Vector2f _POS, int _MAXHP, float _SPEED, int _AMMOAMOUNT = 1, vector<Vector2f> _AMMODIRECTIONS = { Vector2f(0.f, 1.f) }, vector<float> _AMMOPOSITIONS = {}) : Entity(_TEXTURE, Vector2f(1.5f, 1.5f), _MAXHP, _SPEED, Vector2f(0.f, 1.f)) {
        sprite.setRotation(180.f);
        sprite.setPosition(_POS);
        ammoAmount = _AMMOAMOUNT;
        ammoDirections = _AMMODIRECTIONS;
        if (_AMMOPOSITIONS.size() == 0) {
            for (int i = 0; i < ammoAmount; i++) { ammoPositions.push_back(0.f); }
        }
        else { ammoPositions = _AMMOPOSITIONS; }
    }
};

class Ammo : public Entity {
public:
    Ammo(Texture _TEXTURE, Vector2f _POS, Vector2f _BEHAVIOR) : Entity(_TEXTURE, Vector2f(1.2f, 1.2f), 1, 300.f, _BEHAVIOR) {
        int x;
        if (texture.getSize().y > texture.getSize().x) {
            x = texture.getSize().x;
        }
        else { x = texture.getSize().y; }
        sprite.setTextureRect(IntRect(0, 0, x, texture.getSize().y));
        sprite.setOrigin(Vector2f(sprite.getTextureRect().getSize()) / 2.f);
        sprite.setPosition(_POS);
    }
};

class Ray : public Entity {
public:
    Ray(Texture _TEXTURE, Vector2f _POS, Vector2f _BEHAVIOR) : Entity(_TEXTURE, Vector2f(1.2f, 1.2f), 1, 300.f, _BEHAVIOR) {
        int x;
        if (texture.getSize().y > texture.getSize().x) {
            x = texture.getSize().x;
        }
        else { x = texture.getSize().y; }
        sprite.setTextureRect(IntRect(0, 0, x, texture.getSize().y));
        sprite.setOrigin(Vector2f(sprite.getTextureRect().getSize()) / 2.f);
        sprite.setPosition(_POS);
    }
};

class Bonus : public Entity {
public:
    Bonus(Texture _TEXTURE, Vector2f _POS, int _TYPE=1) : Entity(_TEXTURE, Vector2f(0.5f, 0.5f)) {
        sprite.setTextureRect(IntRect(0,0, texture.getSize().x / 2, texture.getSize().y));
        sprite.setPosition(_POS);
        setType(_TYPE);
    }
};

class SFX {
protected:
    Clock frameClock;
    Sprite sprite;
    Texture texture;
    Vector2f pos;
    float size = 1.f;
public:
    SFX(Vector2f _POS, float _SIZE) : pos(_POS), size(_SIZE) {
        sprite.setOrigin(Vector2f(size / 2.f, size / 2.f));
        sprite.setPosition(pos);
    }
    Sprite* getSprite() { return &sprite; }
    Texture getTexture() { return texture; }
    Clock* getFrameClock() { return &frameClock; }
    float getSize() { return size; }
};
class SmallExplosion : public SFX {
public:
    SmallExplosion(Vector2f _POS, float _SCALE = 0.7f) : SFX(_POS, 128.f) {
        texture.loadFromFile("Images/free-pixel-art-enemy-spaceship-2d-sprites/PNG_Parts&Spriter_Animation/Explosions/Explosion1/Explosion1_spritesheet.png");
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, size, size));
        sprite.setScale(_SCALE, _SCALE);
    }
};

class ObjectManager {
private:
    ObjectManager() {}
    vector<SFX*> explosionList = {};
    vector<Entity*> bonusList = {};
    vector<Entity*> rayList = {};
    vector<Entity*> effectList = {};
    vector<Entity*> enemyList = {};
    vector<Entity*> playerList = {};
    vector<vector<Entity*>*> entityList = { &playerList, &enemyList, &effectList, &rayList, &bonusList };
public:
    enum EntityIndex {
        PLAYER = 0,
        ENEMY = 1,
        EFFECT = 2,
        RAY = 3,
        BONUS = 4
    };
    enum EnemyType {
        BASIC_SHIP = 0,
        SPEC_SHIP = 1,
        DOUBLE_BARREL_SHIP = 2,
        BOSS_CRUISER = 3,
        ALIEN_SHIP = 4,
        BOSS_ALIEN_SHIP = 5,
        NAUTOLAN_SHIP = 6,
        BOSS_NAUTOLAN_SHIP = 7
    };
    enum BonusEnum {
        HEALING = 1
    };
    static ObjectManager* getInstance() {
        static ObjectManager* instance = new ObjectManager();
        return instance;
    }

    ~ObjectManager() {
        for (auto currentEntity : entityList) {
            for (auto obj : *currentEntity) {
                delete obj;
            }
        }
        entityList.clear();
    }

    vector<vector<Entity*>*> getEntityList() {
        return entityList;
    }

    Player* addPlayer() {
        Player* player = new Player();
        playerList.clear();
        playerList.push_back(player);
        return player;
    }
    Ammo* addAmmo(Texture texture, Vector2f pos, Vector2f behavior) {
        Ammo* ammo = new Ammo(texture, pos, behavior);
        effectList.push_back(ammo);
        return ammo;
    }
    Enemy* addEnemy(int type=BASIC_SHIP) {
        int xRange = int(screenWidth) - 100;
        float randX = float(rand() % xRange + 50);
        float randY = float(rand() % 110 + 20);
        Vector2f randPos(randX, randY);
        Enemy* enemy;
        if (type == BASIC_SHIP) { //basic bitches
            enemy = new Enemy(basicShip, randPos, 6, 100.f);
        }
        else if (type == SPEC_SHIP) { //shotgun ships
            enemy = new Enemy(specShip, randPos, 4, 90.f, 3, vector<Vector2f>({ Vector2f(-0.5f,1.f), Vector2f(0.f,1.f), Vector2f(0.5f,1.f) }));
            enemy->setFrameRate(1.2f);
        }
        else if (type == DOUBLE_BARREL_SHIP) {
            enemy = new Enemy(doubleBarrelShip, randPos, 6, 90.f, 2, vector<Vector2f>({ Vector2f(0.f, 1.f), Vector2f(0.f, 1.f) }), vector<float>({ -15.f, 15.f }));
        }
        else if (type == BOSS_CRUISER) {
            enemy = new Enemy(bossCruiser, Vector2f(float(screenWidth/2), 100.f), 40, 30.f, 4, vector<Vector2f>({Vector2f(-0.3f,1.f), Vector2f(0.3f,1.f),
                    Vector2f(-0.7f, 1.f), Vector2f(0.7f,1.f)}) );
        }
        else if (type == ALIEN_SHIP) {
            enemy = new Enemy(alienShip, randPos, 8, 110.f, 2, vector<Vector2f>({ Vector2f(0.f, 1.f), Vector2f(0.f, 1.f) }), vector<float>({ -8.f, 8.f }));
            enemy->getSprite()->setScale(Vector2f(1.1f, 1.1f));
            enemy->setFrameRate(0.6f);
        }
        else if (type == BOSS_ALIEN_SHIP) {
            enemy = new Enemy(bossAlienShip, Vector2f(float(screenWidth / 2), 100.f), 70, 50.f, 5,
                vector<Vector2f>({ Vector2f(0.4f, 1.f), Vector2f(0.4f, 1.f), Vector2f(0.f, 1.f), Vector2f(-0.4f, 1.f), Vector2f(-0.4f, 1.f) }),
                vector<float>({ -50.f, -30.f, 0.f, 30.f, 50.f }));
            enemy->setFrameRate(2.f);
        }
        else if (type == NAUTOLAN_SHIP) {
            enemy = new Enemy(nautolanShip, Vector2f(float(screenWidth / 2), 100.f), 70, 50.f, 5,
                vector<Vector2f>({ Vector2f(0.4f, 1.f), Vector2f(0.4f, 1.f), Vector2f(0.f, 1.f), Vector2f(-0.4f, 1.f), Vector2f(-0.4f, 1.f) }),
                vector<float>({ -50.f, -30.f, 0.f, 30.f, 50.f }));
            enemy->setFrameRate(2.f);
        }
        else if (type == BOSS_NAUTOLAN_SHIP) {
            enemy = new Enemy(bossNautolanShip, Vector2f(float(screenWidth / 2), 100.f), 70, 50.f, 5,
                vector<Vector2f>({ Vector2f(0.4f, 1.f), Vector2f(0.4f, 1.f), Vector2f(0.f, 1.f), Vector2f(-0.4f, 1.f), Vector2f(-0.4f, 1.f) }),
                vector<float>({ -50.f, -30.f, 0.f, 30.f, 50.f }));
            enemy->setFrameRate(2.f);
        }
        else { enemy = new Enemy(basicShip, randPos, 6, 100.f); }
        enemy->setType(type);
        enemyList.push_back(enemy);
        return enemy;
    }
    Bonus* addBonus(Vector2f pos, int type = HEALING) {
        Bonus* bonus;
        if (type == HEALING) {
            bonus = new Bonus(bonusHealTexture, pos, HEALING);
        }
        else {
            bonus = new Bonus(bonusHealTexture, pos, HEALING);
        }
        bonusList.push_back(bonus);
        return bonus;
    }

    void deleteEntity(int type, int i) {
        cout << "\n\033[31mOLD SIZE IS " << entityList[type]->size() << "\033[0m\n";
        vector<Entity*>* tempVector = entityList[type];
        delete (*tempVector)[i];
        auto pos = (*tempVector).begin() + i;
        (*tempVector).erase(pos);
        cout << "\n\033[31mNEW SIZE IS " << entityList[type]->size() << "\033[0m\n";
    }

    void addExplosion(Vector2f pos, float scale) {
        SmallExplosion* explo = new SmallExplosion(pos, scale);
        explosionList.push_back(explo);
    }
    vector<SFX*>* getExplosionList() { return &explosionList; }
};
//manager creation
ObjectManager* manager = ObjectManager::getInstance();
//manager creation

class Game {
private:
    Clock gameTime;
    Text chronoText;
    float chronoDecrease = 0;
    Clock mainClock; //clocks and cooldowns
    Time menuTime;
    Clock shootCooldown;
    float shootCooldownDecrease = 0;
    float enemiesSpawnCooldownNum = 0;
    Clock enemiesBehaviorCooldown;
    float bonusCooldownNum = 0;
    vector<Clock*> clockTab = { &gameTime, &mainClock, &shootCooldown, &enemiesBehaviorCooldown };
    bool isMainMenu = true; //menus
    bool isPauseMenu = false;
    Font fontMain; //fonts
    Font fontTitle;
    Text title; //main menu's title
    int scoreNum = 0; //score display
    Text score;
    int waveCount = 1;
    Text deathText;
    Texture table;
    Texture pauseHeaderTexture; Sprite pauseHeader;
    Texture pauseBgTexture; Sprite pauseBg;
    Texture playButtonOffTexture; Texture playButtonOnTexture; Sprite playButton; //menu buttons
    Texture exitButtonOffTexture; Texture exitButtonOnTexture; Sprite exitButton;
    Texture menuButtonOffTexture; Texture menuButtonOnTexture; Sprite menuButton; Text menuText;
    Texture resumeButtonOffTexture; Texture resumeButtonOnTexture; Sprite resumeButton; Text resumeText;
    Texture pauseExitButtonOffTexture; Texture pauseExitButtonOnTexture; Sprite pauseExitButton; Text pauseExitText;
    Text hpText; Text hpBonusText; //hp display
    Texture hpBarTexture;
    Sprite hpBar;
    Texture hpDotTexture;
    Sprite hpDot;
    Texture cursorTexture; //cursor
    Sprite cursor;
    Texture backgroundTexture; //background
    Sprite background;
    Player player; //player
    Vector2f inputMovement;
    SoundBuffer shootSoundBuffer; Sound shootSound; //sounds
    SoundBuffer shootEnemySB; Sound shootEnemy;
    SoundBuffer musicSB; Sound music;
    SoundBuffer menuMusicSB; Sound menuMusic;
    SoundBuffer uiSB; Sound uiSound;
    SoundBuffer uiClicSB; Sound uiClicSound;
    vector<Sound*> soundVector = { &music, &menuMusic, &uiSound, &shootSound, &shootEnemy, &uiClicSound };
    Texture explosionTexture;
    RectangleShape volumeBar, volumeIndicator;
public:
    Game() : inputMovement(0.f, 0.f) {
        cout << "\nnew game\n";
        //title and chrono
        fontTitle.loadFromFile("Fonts/race-space/RACESPACESTRIPE.ttf");
        title.setFont(fontTitle); title.setCharacterSize(80); title.setString("BATTLESKY"); title.setFillColor(Color(0, 222, 222, 255));
        title.setOrigin(Vector2f(250.f, 40.f)); title.setPosition(Vector2f(screenWidth / 2, 100.f));
        chronoText.setFont(fontMain); chronoText.setCharacterSize(22);
        chronoText.setPosition(Vector2f(15.f, 15.f));
        //sounds
        shootSoundBuffer.loadFromFile("SoundEffects/futuristic-gun-shot-sci-fi.wav");
        shootSound.setBuffer(shootSoundBuffer); shootSound.setVolume(10.f);
        shootEnemySB.loadFromFile("SoundEffects/sci-fi-weapon-shoot-firing-plasma.mp3");
        shootEnemy.setBuffer(shootEnemySB); shootEnemy.setVolume(10.f); 
        musicSB.loadFromFile("SoundEffects/Sci-Fi Music Pack/Loops/mp3/Sci-Fi 8 Loop.mp3");
        music.setBuffer(musicSB); music.setVolume(10.f); music.setLoop(true);
        uiSB.loadFromFile("SoundEffects/SCI-FI_UI_SFX_PACK/SCI-FI_UI_SFX_PACK/Tone1/Basic Tones/Tone1B.wav");
        uiSound.setBuffer(uiSB); uiSound.setVolume(10.f);
        uiClicSB.loadFromFile("SoundEffects/SCI-FI_UI_SFX_PACK/SCI-FI_UI_SFX_PACK/Tone1/Basic Tones/Tone1A.wav");
        uiClicSound.setBuffer(uiClicSB); uiClicSound.setVolume(10.f);
        menuMusicSB.loadFromFile("SoundEffects/Sci-Fi Music Pack Vol. 2/Tracks/wav/6 - Orbital Echoes.wav");
        menuMusic.setBuffer(menuMusicSB); menuMusic.setVolume(10.f); menuMusic.setLoop(true);
        //score
        fontMain.loadFromFile("Fonts/space-crusaders-cufonfonts/SpaceCrusaders-x3DP0.ttf");
        score.setString("SCORE : " + to_string(scoreNum) + "\n wave " + to_string(waveCount));
        score.setFont(fontMain);
        score.setCharacterSize(40);
        score.setOrigin(Vector2f(100.f, 10.f));
        score.setPosition(Vector2f(float(screenWidth / 2), 10.f));
        //title screen buttons
        playButtonOffTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_Menu/Start_BTN.png"); playButtonOnTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_Menu/Start_BTN_on.png");
        playButton.setTexture(playButtonOffTexture); playButton.setOrigin(Vector2f(playButtonOffTexture.getSize())/2.f); playButton.setPosition(Vector2f(float(screenWidth/2), 410.f));
        exitButtonOffTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_Menu/Exit_BTN.png"); exitButtonOnTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_Menu/Exit_BTN_on.png");
        exitButton.setTexture(exitButtonOffTexture); exitButton.setOrigin(Vector2f(exitButtonOffTexture.getSize())/2.f); exitButton.setPosition(Vector2f(float(screenWidth / 2), 650.f));
        //pause menu
        float pauseMenuOffset = 130.f;
        pauseHeaderTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Pause/Header.png");
        pauseHeader.setTexture(pauseHeaderTexture); pauseHeader.setOrigin(Vector2f(pauseHeaderTexture.getSize().x/2, 0.f)); pauseHeader.setPosition(Vector2f(float(screenWidth / 2), 8.f + pauseMenuOffset));
        pauseBgTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Pause/Window.png");
        pauseBg.setTexture(pauseBgTexture); pauseBg.setOrigin(Vector2f(pauseBgTexture.getSize().x/2, 0.f)); pauseBg.setScale(Vector2f(0.55f, 0.5f)); pauseBg.setPosition(Vector2f(float(screenWidth / 2), pauseMenuOffset));
        menuButtonOffTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Pause/Menu_BTN.png"); menuButtonOnTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Buttons/BTNs_Active/Menu_BTN.png");
        menuButton.setTexture(menuButtonOffTexture); menuButton.setOrigin(Vector2f(105.f, 105.f)); menuButton.setScale(Vector2f(0.4f, 0.4f)); menuButton.setPosition(Vector2f(float(screenWidth / 2 - 160), 180.f + pauseMenuOffset));
        menuText.setString("MAIN MENU"); menuText.setFont(fontMain); menuText.setCharacterSize(40); menuText.setOrigin(Vector2f(0.f, 30.f)); menuText.setPosition(menuButton.getPosition() + Vector2f(60.f, 0.f));
        resumeButtonOffTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Buttons/BTNs/Play_BTN.png"); resumeButtonOnTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Buttons/BTNs_Active/Play_BTN.png");
        resumeButton.setTexture(resumeButtonOffTexture); resumeButton.setOrigin(Vector2f(105.f, 105.f)); resumeButton.setScale(Vector2f(0.4f, 0.4f)); resumeButton.setPosition(Vector2f(float(screenWidth / 2 - 160), 280.f + pauseMenuOffset));
        resumeText.setString("RESUME"); resumeText.setFont(fontMain); resumeText.setCharacterSize(40); resumeText.setOrigin(Vector2f(0.f, 30.f)); resumeText.setPosition(resumeButton.getPosition() + Vector2f(60.f, 0.f));
        pauseExitButtonOffTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Buttons/BTNs/Close_BTN.png"); pauseExitButtonOnTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Buttons/BTNs_Active/Close_BTN.png");
        pauseExitButton.setTexture(resumeButtonOffTexture); pauseExitButton.setOrigin(Vector2f(105.f, 105.f)); pauseExitButton.setScale(Vector2f(0.4f, 0.4f)); pauseExitButton.setPosition(Vector2f(float(screenWidth / 2 - 160), 380.f + pauseMenuOffset));
        pauseExitText.setString("CLOSE GAME"); pauseExitText.setFont(fontMain); pauseExitText.setCharacterSize(40); pauseExitText.setOrigin(Vector2f(0.f, 30.f)); pauseExitText.setPosition(pauseExitButton.getPosition() + Vector2f(60.f, 0.f));
        //health and death
        hpText.setFont(fontMain); hpText.setCharacterSize(30); hpText.setPosition(Vector2f(20.f, float(screenHeight - 50))); hpText.setFillColor(Color(157, 217, 146));
        hpBarTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_UI/Health_Bar_Table.png");
        hpBar.setTexture(hpBarTexture); hpBar.setPosition(hpText.getPosition() + Vector2f(100.f, 0.f)); hpBar.setScale(Vector2f(0.5f, 0.5f));
        hpDotTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Main_UI/Health_Dot.png");
        hpDot.setTexture(hpDotTexture); hpDot.setScale(Vector2f(0.5f, 0.5f));
        hpBonusText.setFont(fontMain); hpBonusText.setCharacterSize(25); hpBonusText.setPosition(hpText.getPosition() - Vector2f(-10.f, 20.f));
        hpBonusText.setString("+1"); hpBonusText.setFillColor(Color(20, 180, 200));
        deathText.setFont(fontMain); deathText.setString("YOU DIED"); deathText.setCharacterSize(60); deathText.setFillColor(Color(150, 10, 10));
        deathText.setOrigin(Vector2f(100.f, 10.f)); deathText.setPosition(pauseExitText.getPosition() + Vector2f(50.f, -130));
        table.loadFromFile("Images/Space_Game_GUI_PNG/PNG/You_Lose/Table.png"); table.setSmooth(true);
        //background
        backgroundTexture.loadFromFile("Images/space_background_pack/Assets/Blue Version/blue-preview.png");
        background.setTexture(backgroundTexture);
        background.setColor(Color(200, 0, 200));
        background.setOrigin(Vector2f(backgroundTexture.getSize()) / 2.f);
        background.setScale(Vector2f(1.6f, 1.5f));
        background.setPosition(Vector2f(screenWidth/2, screenHeight/2));
        //cursor
        cursorTexture.loadFromFile("Images/CoB_cursor/Layer 1_sprite_1.png");
        cursor.setTexture(cursorTexture);
        cursor.setOrigin(Vector2f(7.f, 7.f));
        cursor.setScale(Vector2f(2.f, 2.f));
        //volume bar
        volumeBar.setSize(Vector2f(150, 8));
        volumeIndicator.setSize(Vector2f(15, 30));
        volumeBar.setFillColor(Color(150, 150, 150)); volumeIndicator.setFillColor(Color(210, 210, 210));
        volumeBar.setOrigin(static_cast<Vector2f>(volumeBar.getSize()) / 2.f); volumeIndicator.setOrigin(static_cast<Vector2f>(volumeIndicator.getSize()) / 2.f);
        volumeBar.setPosition(Vector2f(screenWidth - volumeBar.getSize().x, 30)); volumeIndicator.setPosition(volumeBar.getPosition());
    }

    void userInput() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed and Keyboard::isKeyPressed(Keyboard::Escape)) {
                isPauseMenu = true;
            }
            else if (event.type == Event::Closed) { window.close(); delete manager; exit(1); }
        }
        inputMovement = Vector2f(0.f, 0.f);
        if (Keyboard::isKeyPressed(Keyboard::delocalize(Keyboard::Z))) {
            inputMovement += Vector2f(0.f, -1.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            inputMovement += Vector2f(0.f, 1.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            inputMovement += Vector2f(1.2f, 0.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            inputMovement += Vector2f(-1.2f, 0.f);
        }
        if ((Keyboard::isKeyPressed(Keyboard::Space) or Mouse::isButtonPressed(Mouse::Left)) and shootCooldown.getElapsedTime().asSeconds() > 0.25f) {
            Ammo* ammoAdded = manager->addAmmo(ammoTexture, Vector2f(player.getPos().x, player.getUp()), Vector2f(0.f, -1.f));
            /*ammoAdded->setColor(20, 255, 20);*/
            shootCooldown.restart();
            shootSound.play();
        }
    }

    void update() {
        Time timeSinceLastFrame = mainClock.restart() - menuTime;
        chronoDecrease += menuTime.asSeconds();

        player.move(inputMovement * timeSinceLastFrame.asSeconds());
        /*player.getHitBox();*/
        if (player.getLeft() > screenWidth) { player.setX(0.f); }
        if (player.getRight() < 0) { player.setX(screenWidth); }
        if (player.getUp() < 0) { player.setY(player.getHeight()/2.f); }
        if (player.getDown() > screenHeight) { player.setY(screenHeight - player.getHeight()/2.f); }

        enemiesSpawnCooldownNum += timeSinceLastFrame.asSeconds();
        bonusCooldownNum += timeSinceLastFrame.asSeconds();

        if (scoreNum < 10) {
            if (enemiesSpawnCooldownNum >= 8 and manager->getEntityList()[manager->ENEMY]->size() < 5) {
                int randType = rand() % 100;
                if (randType < 65) { manager->addEnemy(manager->BASIC_SHIP); }
                else { manager->addEnemy(manager->SPEC_SHIP); }
                enemiesSpawnCooldownNum = 0;
            }
        }
        else if (scoreNum < 20) {
            if (enemiesSpawnCooldownNum >= 6 and manager->getEntityList()[manager->ENEMY]->size() < 8) {
                int randType = rand() % 100;
                if (randType < 40) { manager->addEnemy(manager->BASIC_SHIP); }
                else if (randType < 70) { manager->addEnemy(manager->SPEC_SHIP); }
                else { manager->addEnemy(manager->DOUBLE_BARREL_SHIP); }
                enemiesSpawnCooldownNum = 0;
            }
        }
        else if (waveCount == 3) {
            if (enemiesSpawnCooldownNum >= 8 and manager->getEntityList()[manager->ENEMY]->size() < 4) {
                manager->addEnemy(manager->DOUBLE_BARREL_SHIP);
                enemiesSpawnCooldownNum = 0;
            }
        }
        else if (waveCount == 4) {
            if (enemiesSpawnCooldownNum >= 12 and manager->getEntityList()[manager->ENEMY]->size() < 3) {
                manager->addEnemy(manager->ALIEN_SHIP);
                enemiesSpawnCooldownNum = 0;
            }
        }
        else if (waveCount == 5) {
            if (enemiesSpawnCooldownNum >= 5 and manager->getEntityList()[manager->ENEMY]->size() < 10) {
                int randType = rand() % 100;
                if (randType < 70) { manager->addEnemy(manager->NAUTOLAN_SHIP); }
                else { manager->addEnemy(manager->ALIEN_SHIP); }
                enemiesSpawnCooldownNum = 0;
            }
        }

        for (int i = 0; i < manager->getEntityList()[manager->ENEMY]->size(); i++) {
            Entity* enemy = (*manager->getEntityList()[manager->ENEMY])[i];
            if (enemiesBehaviorCooldown.getElapsedTime().asSeconds() - menuTime.asSeconds() >= 0.8f) {
                int randBehav = rand() % 8;
                int edge = 120;
                int forwardLimit = screenHeight / 3;
                int backLimit = edge;
                int rightLimit = screenWidth - edge;
                int leftLimit = edge;
                if (randBehav == 0 and enemy->getPos().y < forwardLimit) { enemy->setBehavior(Vector2f(0.f, 1.f)); } //moves forward
                else if (randBehav == 1 and enemy->getPos().x < rightLimit) { enemy->setBehavior(Vector2f(1.f, 0.f)); } //moves right
                else if (randBehav == 2 and enemy->getPos().y > backLimit) { enemy->setBehavior(Vector2f(0.f, -1.f)); } //moves back
                else if (randBehav == 3 and enemy->getPos().x > leftLimit) { enemy->setBehavior(Vector2f(-1.f, 0.f)); } //moves left
                else if (randBehav == 4 and enemy->getPos().y < forwardLimit and enemy->getPos().x < rightLimit) { enemy->setBehavior(Vector2f(1.f, 1.f)); } //moves forward-right
                else if (randBehav == 5 and enemy->getPos().y > backLimit and enemy->getPos().x > leftLimit) { enemy->setBehavior(Vector2f(-1.f, -1.f)); } //moves back-left
                else if (randBehav == 6 and enemy->getPos().y < forwardLimit and enemy->getPos().x > leftLimit) { enemy->setBehavior(Vector2f(-1.f, 1.f)); } //moves forward-left
                else if (randBehav == 7 and enemy->getPos().y > backLimit and enemy->getPos().x < rightLimit) { enemy->setBehavior(Vector2f(1.f, -1.f)); } //moves back-right
                if (i == manager->getEntityList()[manager->ENEMY]->size() - 1) { enemiesBehaviorCooldown.restart(); }
            }
            enemy->move(enemy->getBehavior() * timeSinceLastFrame.asSeconds());
            if (enemy->getLeft() > screenWidth) { enemy->setX(0.f); }
            if (enemy->getRight() < 0) { enemy->setX(screenWidth); }
            if (enemy->getUp() < 0) { enemy->setY(enemy->getHeight() / 2.f); }
            if (enemy->getDown() > screenHeight) { enemy->setY(screenHeight - enemy->getHeight() / 2.f); }
            if (enemy->getShootCooldown().getElapsedTime().asSeconds() - shootCooldownDecrease >= enemy->getFrameRate()) {
                shootEnemy.play();
                for (int i = 0; i < enemy->getAmmoAmount(); i++) {
                    Vector2f currentDirection = enemy->getAmmoDirections()[i];
                    Vector2f currentPos = Vector2f(enemy->getPos().x + enemy->getAmmoPositions()[i], enemy->getDown());
                    Texture texture = ammoTexture;
                    if (enemy->getType() == manager->ALIEN_SHIP or enemy->getType() == manager->BOSS_ALIEN_SHIP) {
                        texture = spinningAmmoTexture;
                    }
                    manager->addAmmo(texture, currentPos, currentDirection);
                }
                enemy->restartShootCooldown();
                shootCooldownDecrease = 0;
            }
        }

        for (int i = 0; i < manager->getEntityList()[manager->EFFECT]->size(); i++) {
            Entity* ammo = (*manager->getEntityList()[manager->EFFECT])[i];
            ammo->move(ammo->getBehavior() * timeSinceLastFrame.asSeconds());
            ammo->addToFrameRate(timeSinceLastFrame.asSeconds());
            if (ammo->getFrameRate() > 0.08f) {
                ammo->setFrameRate(0);
                ammo->continueAnimation();
            }
            if (ammo->getPos().y < 0 or ammo->getPos().y > screenHeight) { manager->deleteEntity(manager->EFFECT, i); }
            if (ammo->getBehavior() == Vector2f(0.f, -1.f)) {
                for (int j = 0; j < manager->getEntityList()[manager->ENEMY]->size(); j++) {
                    Entity* currentEntity = (*manager->getEntityList()[manager->ENEMY])[j];
                    if (ammo->isColiding(*currentEntity)) {
                        cout << "\n\033[32menemy hit!\033[0m\n";
                        currentEntity->decreaseHp(2);
                        manager->deleteEntity(manager->EFFECT, i);
                        cout << "remaining hp : " << currentEntity->getHp() << endl;
                        if (currentEntity->getHp() <= 0) {
                            manager->addExplosion(currentEntity->getPos(), currentEntity->getHeight() * 0.015);
                            manager->deleteEntity(manager->ENEMY, j);
                            scoreNum++;
                            if (scoreNum == 10) { waveCount = 2; }
                            if (scoreNum == 20) {
                                manager->addEnemy(manager->BOSS_CRUISER);
                                for (int i = 0; i < 2; i++) {
                                    manager->addEnemy(manager->DOUBLE_BARREL_SHIP);
                                }
                                waveCount = 3;
                            }
                            if (waveCount == 3 and manager->getEntityList()[manager->ENEMY]->size() == 0) {
                                manager->addEnemy(manager->BOSS_ALIEN_SHIP);
                                for (int i = 0; i < 2; i++) {
                                    manager->addEnemy(manager->ALIEN_SHIP);
                                }
                                waveCount = 4;
                            }
                            if (waveCount == 4 and manager->getEntityList()[manager->ENEMY]->size() == 0) { manager->addEnemy(manager->BOSS_NAUTOLAN_SHIP); waveCount = 5; }
                            score.setString("SCORE : " + to_string(scoreNum) + "\n wave " + to_string(waveCount));
                        }
                    }
                }
            }
            else {
                if (ammo->isColiding(player)) {
                    cout << "\n\033[32player hit!\033[0m\n";
                    player.decreaseHp();
                    manager->deleteEntity(manager->EFFECT, i);
                }
            }
        }
        for (int i = 0; i < manager->getEntityList()[manager->BONUS]->size(); i++) {
            Entity* bonus = (*manager->getEntityList()[manager->BONUS])[i];
            bonus->addToFrameRate(timeSinceLastFrame.asSeconds());
            bonus->addToLifeTime(timeSinceLastFrame.asSeconds());
            if (player.getHp() <= player.getMaxHp() and player.isColiding(*bonus)) {
                manager->deleteEntity(manager->BONUS, i);
                player.decreaseHp(-1);
            }
            else if (bonus->getLifeTime() > 15) {
                manager->deleteEntity(manager->BONUS, i);
            }
            else if (bonus->getLifeTime() > 10) {
                if (bonus->getFrameRate() > 0.25f) {
                    bonus->setFrameRate(0);
                    bonus->continueAnimation();
                }
            }
        }
        if (bonusCooldownNum > 16) {
            bonusCooldownNum = 0;
            int randIsBonus = rand() % 100;
            if (randIsBonus < 70) {
                Vector2f randPos = Vector2f(float(rand() % int(screenWidth)), float(rand() % (int(screenHeight) / 2) + (int(screenHeight) / 2)));
                manager->addBonus(randPos);
            }
        }

        for (int i = 0; i < (*manager->getExplosionList()).size(); i++) {
            SFX* sfx = (*manager->getExplosionList())[i];
            if (sfx->getFrameClock()->getElapsedTime().asSeconds() > 0.04f) {
                IntRect newRect = sfx->getSprite()->getTextureRect();
                newRect.left += sfx->getSize();
                if (sfx->getTexture().getSize().x <= newRect.left) {
                    delete sfx;
                    auto pos = manager->getExplosionList()->begin() + i;
                    manager->getExplosionList()->erase(pos);
                }
                else {
                    sfx->getSprite()->setTextureRect(newRect);
                    sfx->getFrameClock()->restart();
                }
            }
        }
        menuTime = Time().Zero;

        if (player.getHp() < -99999999) {
            bool isDeath = true;
            bool onMenu = false; resumeButton.setTexture(resumeButtonOffTexture);
            bool onExit = false; pauseExitButton.setTexture(pauseExitButtonOffTexture);
            bool onVolume = false;
            Sprite tableRect(table); tableRect.setOrigin(Vector2f(table.getSize().x / 2, table.getSize().y / 2));
            while (isDeath) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::MouseButtonPressed and Mouse::isButtonPressed(Mouse::Left)) {
                        if (onMenu) {
                            uiClicSound.play();
                            isMainMenu = true; isDeath = false;
                        }
                        else if (onExit) {
                            uiClicSound.play();
                            window.close(); delete manager; exit(1);
                        }
                    }
                    else if (event.type == Event::Closed) { window.close(); delete manager; exit(1); }
                }
                if (onVolume and Mouse::isButtonPressed(Mouse::Left)) {
                    if (Mouse::getPosition(window).x <= volumeBar.getPosition().x + volumeBar.getSize().x / 2 and Mouse::getPosition(window).x >= volumeBar.getPosition().x - volumeBar.getSize().x / 2) {
                        volumeIndicator.setPosition(Vector2f(Mouse::getPosition(window).x, volumeIndicator.getPosition().y));
                        for (Sound* currentSound : soundVector) {
                            currentSound->setVolume(10.f + (volumeIndicator.getPosition().x - volumeBar.getPosition().x) / 7.5f);
                        }
                    }
                }
                window.clear();
                display();
                window.draw(chronoText);
                RectangleShape blurry(Vector2f(screenWidth, screenHeight));
                blurry.setFillColor(Color(255, 255, 255, 150));
                window.draw(blurry);
                tableRect.setScale(Vector2f(0.6f, 0.5f)); tableRect.setPosition(volumeBar.getPosition() + Vector2f(0.f, 2.f));
                window.draw(tableRect);
                window.draw(volumeBar); window.draw(volumeIndicator);
                if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) or volumeBar.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        volumeIndicator.setFillColor(Color(255, 255, 255));
                    }
                    else { volumeIndicator.setFillColor(Color(210, 210, 210)); }
                    if (!onVolume) {
                        onVolume = true;
                        if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                            uiSound.play();
                        }
                    }
                }
                else if (onVolume and !Mouse::isButtonPressed(Mouse::Left)) { volumeIndicator.setFillColor(Color(210, 210, 210)); onVolume = false; }

                tableRect.setScale(Vector2f(1.2f, 1.2f));
                tableRect.setPosition(menuText.getPosition() + Vector2f(80, 5));
                window.draw(tableRect);
                tableRect.setPosition(pauseExitText.getPosition() + Vector2f(80, 5));
                window.draw(tableRect);
                window.draw(menuButton); window.draw(menuText); window.draw(deathText);

                if (menuButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    if (!onMenu) {
                        menuButton.setTexture(menuButtonOnTexture);
                        onMenu = true; uiSound.play();
                    }
                }
                else if (onMenu) { menuButton.setTexture(menuButtonOffTexture); onMenu = false; }
                window.draw(pauseExitButton); window.draw(pauseExitText);
                if (pauseExitButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    if (!onExit) {
                        pauseExitButton.setTexture(pauseExitButtonOnTexture);
                        onExit = true; uiSound.play();
                    }
                }
                else if (onExit) { pauseExitButton.setTexture(pauseExitButtonOffTexture); onExit = false; }
                cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
                window.draw(cursor);
                window.display();
            }
        }
    }

    void display() {
        window.clear();
        window.draw(background);
        for (Entity* bonus : *(manager->getEntityList()[manager->BONUS])) {
            window.draw(*bonus->getSprite());
        }
        for (Entity* ammo : *(manager->getEntityList()[manager->EFFECT])) {
            window.draw(*ammo->getSprite());
        }
        for (Entity* enemy : *(manager->getEntityList()[manager->ENEMY])) {
            window.draw(*enemy->getSprite());
        }
        for (int i = 0; i < (*manager->getExplosionList()).size(); i++) {
            window.draw(*((*manager->getExplosionList())[i]->getSprite()));
        }
        window.draw(*player.getSprite());

        if (player.getHp() > 10) { window.draw(hpBonusText); hpText.setString(to_string(player.getHp()-1) + "/" + to_string(player.getMaxHp())); }
        else { hpText.setString(to_string(player.getHp()) + "/" + to_string(player.getMaxHp())); }
        window.draw(hpText);
        window.draw(hpBar);
        for (int i = 0; i < player.getHp(); i++) {
            Sprite heart = hpDot;
            heart.setPosition(hpBar.getPosition() + Vector2f(4.0f, 3.f) + float(i) * Vector2f(15.0f, 0.f));
            if (i >= 10) { heart.setColor(Color(50, 150, 255)); }
            window.draw(heart);
        }
        window.draw(score);
    }

    void pauseMenu() {
        Clock pauseMenuClock;
        bool onResume = false; menuButton.setTexture(menuButtonOffTexture);
        bool onMenu = false; resumeButton.setTexture(resumeButtonOffTexture);
        bool onExit = false; pauseExitButton.setTexture(pauseExitButtonOffTexture);
        bool onVolume = false;
        music.pause();
        while (isPauseMenu) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::KeyPressed and Keyboard::isKeyPressed(Keyboard::Escape)) {
                    isPauseMenu = false; menuTime = pauseMenuClock.getElapsedTime(); shootCooldownDecrease = menuTime.asSeconds(); shootCooldown.restart(); music.play();
                }
                else if (event.type == Event::MouseButtonPressed and Mouse::isButtonPressed(Mouse::Left)) {
                    if (onMenu) {
                        uiClicSound.play();
                        isMainMenu = true; isPauseMenu = false;
                    }
                    else if (onResume) {
                        uiClicSound.play();
                        isPauseMenu = false; menuTime = pauseMenuClock.getElapsedTime(); shootCooldownDecrease = menuTime.asSeconds(); shootCooldown.restart(); music.play();
                    }
                    else if (onExit) {
                        uiClicSound.play();
                        window.close(); delete manager; exit(1);
                    }
                }
                else if (event.type == Event::Closed) { window.close(); delete manager; exit(1); }
            }
            if (onVolume and Mouse::isButtonPressed(Mouse::Left)) {
                if (Mouse::getPosition(window).x <= volumeBar.getPosition().x + volumeBar.getSize().x / 2 and Mouse::getPosition(window).x >= volumeBar.getPosition().x - volumeBar.getSize().x / 2) {
                    volumeIndicator.setPosition(Vector2f(Mouse::getPosition(window).x, volumeIndicator.getPosition().y));
                    for (Sound* currentSound : soundVector) {
                        currentSound->setVolume(10.f + (volumeIndicator.getPosition().x - volumeBar.getPosition().x) / 7.5f);
                    }
                }
            }
            window.clear();
            display();
            window.draw(chronoText);
            window.draw(pauseBg);
            window.draw(pauseHeader);
            //menu button
            window.draw(menuButton); window.draw(menuText);
            if (menuButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                if (!onMenu) {
                    menuButton.setTexture(menuButtonOnTexture);
                    onMenu = true; uiSound.play();
                }
            }
            else if (onMenu) { menuButton.setTexture(menuButtonOffTexture); onMenu = false; }
            //resume button
            window.draw(resumeButton); window.draw(resumeText);
            if (resumeButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                if (!onResume) {
                    resumeButton.setTexture(resumeButtonOnTexture);
                    onResume = true; uiSound.play();
                }
            }
            else if (onResume) { resumeButton.setTexture(resumeButtonOffTexture); onResume = false; }
            //exit button
            window.draw(pauseExitButton); window.draw(pauseExitText);
            if (pauseExitButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                if (!onExit) {
                    pauseExitButton.setTexture(pauseExitButtonOnTexture);
                    onExit = true; uiSound.play();
                }
            }
            else if (onExit) { pauseExitButton.setTexture(pauseExitButtonOffTexture); onExit = false; }
            window.draw(volumeBar); window.draw(volumeIndicator);
            if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) or volumeBar.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    volumeIndicator.setFillColor(Color(255, 255, 255));
                }
                else { volumeIndicator.setFillColor(Color(210, 210, 210)); }
                onVolume = true;
                if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) and !onVolume) {
                    uiSound.play();
                }
            }
            else if (onVolume and !Mouse::isButtonPressed(Mouse::Left)) { volumeIndicator.setFillColor(Color(210, 210, 210)); onVolume = false; }

            cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
            window.draw(cursor);
            window.display();
        }
    }

    void mainMenu() {
        Clock mainMenuClock;
        bool onStart = false; playButton.setTexture(playButtonOffTexture);
        bool onExit = false; exitButton.setTexture(exitButtonOffTexture);
        bool onVolume = false;
        menuMusic.play();
        
        while (isMainMenu) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) { window.close(); exit(1); }
                else if (event.type == Event::MouseButtonPressed and Mouse::isButtonPressed(Mouse::Left)) {
                    if (onStart) {
                        uiClicSound.play();
                        for (Clock* clock : clockTab) {
                            clock->restart();
                        }
                        chronoDecrease = 0; enemiesSpawnCooldownNum = 0; bonusCooldownNum = 0;
                        scoreNum = 0; waveCount = 1; score.setString("SCORE : " + to_string(scoreNum) + "\n wave " + to_string(waveCount));
                        cout << "\nentity list size " << manager->getEntityList().size() << endl;
                        for (int type = 0; type < manager->getEntityList().size(); type++) {
                            cout << type << " size is " << manager->getEntityList()[type]->size() << endl;
                            for (Entity* entity : *manager->getEntityList()[type]) {
                                manager->deleteEntity(type, 0);
                            }
                            cout << type << " new size is " << manager->getEntityList()[type]->size() << endl;
                        }
                        player = *(manager->addPlayer());
                        for (int i = 0; i < 2; i++) {
                            manager->addEnemy(manager->BASIC_SHIP);
                        }
                        for (int i = 0; i < (*manager->getExplosionList()).size(); i++) {
                            SFX* sfx = (*manager->getExplosionList())[i];
                            delete sfx;
                            auto pos = manager->getExplosionList()->begin() + i;
                            manager->getExplosionList()->erase(pos);
                        }
                        menuMusic.stop(); music.stop(); music.play();
                        isMainMenu = false;
                    }
                    else if (onExit) {
                        uiClicSound.play();
                        window.close(); delete manager; exit(1);
                    }
                }
            }
            if (onVolume and Mouse::isButtonPressed(Mouse::Left)) {
                if (Mouse::getPosition(window).x <= volumeBar.getPosition().x + volumeBar.getSize().x/2 and Mouse::getPosition(window).x >= volumeBar.getPosition().x - volumeBar.getSize().x/2) {
                    volumeIndicator.setPosition(Vector2f(Mouse::getPosition(window).x, volumeIndicator.getPosition().y));
                    for (Sound* currentSound : soundVector) {
                        currentSound->setVolume(10.f + (volumeIndicator.getPosition().x - volumeBar.getPosition().x) / 7.5f);
                    }
                }
            }
            window.clear();
            window.draw(background);
            //start-button check
            if (playButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                if (!onStart) {
                    playButton.setTexture(playButtonOnTexture);
                    onStart = true; uiSound.play();
                }
            }
            else if (onStart) { playButton.setTexture(playButtonOffTexture); onStart = false; }
            window.draw(playButton);
            //exit-button check
            if (exitButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                if (!onExit) {
                    exitButton.setTexture(exitButtonOnTexture);
                    onExit = true; uiSound.play();
                }
            }
            else if (onExit) { exitButton.setTexture(exitButtonOffTexture); onExit = false; }
            window.draw(volumeBar); window.draw(volumeIndicator);
            if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) or volumeBar.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    volumeIndicator.setFillColor(Color(255, 255, 255));
                }
                else { volumeIndicator.setFillColor(Color(210, 210, 210)); }
                if (!onVolume) {
                    onVolume = true;
                    if (volumeIndicator.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        uiSound.play();
                    }
                }
            }
            else if (onVolume and !Mouse::isButtonPressed(Mouse::Left)) { volumeIndicator.setFillColor(Color(210, 210, 210)); onVolume = false; }
            window.draw(exitButton);
            //title
            window.draw(title);
            //cursor
            cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
            window.draw(cursor);
            window.display();
        }
    }

    void gameLoop() {
        
        cout << "\nloop\n";
        while (window.isOpen()) {
            
            if (!isMainMenu and !isPauseMenu) {
                userInput();
                update();
                display();
                cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
                string chronoTextStr = "chrono\n";
                string gameTimeStr = to_string(gameTime.getElapsedTime().asSeconds() - chronoDecrease);
                for (int i = 0; i < gameTimeStr.size(); i++) {
                    if (i > 1) {
                        if (gameTimeStr[i - 2] == '.') { chronoTextStr += " s\n----------"; break; }
                    }
                    chronoTextStr += gameTimeStr[i];
                }
                chronoText.setString(chronoTextStr);
                window.draw(chronoText);
                window.draw(cursor);
                window.display();
            }
            else if (isMainMenu) {
                mainMenu();
            }
            else if (isPauseMenu) {
                pauseMenu();
            }
        }
    }
};

int WinMain() {
    Image icon; icon.loadFromFile("icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    playerShip.loadFromFile("Images/tiny-spaceships/tiny_ship9.png");
    basicShip.loadFromFile("Images/tiny-spaceships/tiny_ship20.png");
    specShip.loadFromFile("Images/tiny-spaceships/tiny_ship15.png");
    doubleBarrelShip.loadFromFile("Images/tiny-spaceships/tiny_ship19.png");
    bossCruiser.loadFromFile("Images/Foozle_2DS0012_Void_EnemyFleet_1/Kla'ed/Base/PNGs/Kla'ed - Battlecruiser - Base.png");
    alienShip.loadFromFile("Images/free-pixel-art-enemy-spaceship-2d-sprites/PNG_Parts&Spriter_Animation/Ship2/Ship2.png");
    bossAlienShip.loadFromFile("Images/free-pixel-art-enemy-spaceship-2d-sprites/PNG_Parts&Spriter_Animation/Ship6/Ship6.png");
    nautolanShip.loadFromFile("Images/Foozle_2DS0014_Void_EnemyFleet_3/Nautolan/Designs - Base/PNGs/Nautolan Ship - Scout - Base.png");
    bossNautolanShip.loadFromFile("Images/Foozle_2DS0014_Void_EnemyFleet_3/Nautolan/Designs - Base/PNGs/Nautolan Ship - Dreadnought - Base.png");
    ammoTexture.loadFromFile("Images/Lunar Lander Upload/Effects/Fx_02_single.png");
    spinningAmmoTexture.loadFromFile("Images/Foozle_2DS0014_Void_EnemyFleet_3/Nautolan/Weapon Effects - Projectiles/PNGs/Nautolan - Spinning Bullet.png");
    bonusHealTexture.loadFromFile("Images/Space_Game_GUI_PNG/PNG/Upgrade/HP_Icon.png");
    
    window.setMouseCursorVisible(false);
    srand(time(0));
    /*CircleShape shape(20.f);
    shape.setFillColor(Color::Green);*/
    Game game;
    game.gameLoop();
    cout << "\nend\n";
    delete manager;
    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
