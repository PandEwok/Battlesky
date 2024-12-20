#ifndef Manager_HPP
#define Manager_HPP

#include "Entity.hpp"


using namespace sf;
using namespace std;


class ObjectManager {
private:
    ObjectManager();
    vector<SFX*> explosionList = {};
    vector<SFX*> backgroundAsteroidList = {};
    vector<SFX*> backgroundPlanetList = {};
    vector<vector<SFX*>*> backgroundPropList = { &backgroundAsteroidList, &backgroundPlanetList };
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
        ALIEN_FLAME_SHIP = 5,
        BOSS_ALIEN_SHIP = 6,
        NAUTOLAN_SHIP = 7,
        NAUTOLAN_WAVE_SHIP = 8,
        BOSS_NAUTOLAN_SHIP = 9
    };
    enum BonusEnum {
        HEALING = 1,
        RIFLE = 2,
        SNIPER = 3,
        PISTOL = 4
    };
    enum PropEnum {
        ASTEROID = 0,
        PLANET = 1,
        ASTERO1 = 2,
        ASTERO2 = 3,
        PLANET1 = 4,
        BLACK_HOLE = 5,
        ALIENBASE = 6,
        WATER_BUBBLE = 7
    };
    static ObjectManager* getInstance();

    ~ObjectManager();

    vector<vector<Entity*>*> getEntityList();

    Player* addPlayer();
    Ammo* addAmmo(Texture* texture, Vector2f pos, Vector2f behavior, int damages = 1);
    Ray* addRay(Texture texture, Vector2f pos, Vector2f behavior, int frameNumber = 4, int lenght = 30, int i = 0);
    Enemy* addEnemy(int type);
    Bonus* addBonus(Vector2f pos, int type = HEALING);

    void deleteEntity(int type, Entity* entity);

    void addExplosion(Vector2f pos, float scale);
    BackgroundProp* addBackgroundProp(int type, Vector2f pos, float scale, int asteroType = ASTERO1);
    vector<SFX*>* getExplosionList();
    vector<vector<SFX*>*>* getBackgroundPropList();
};

#endif