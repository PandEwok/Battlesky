
#include "Manager.hpp"
using namespace sf;
using namespace std;



ObjectManager::ObjectManager() {}

ObjectManager* ObjectManager::getInstance() {
    ObjectManager* instance = new ObjectManager();
    cout << "\ncreated new manager instance\n";
    return instance;
}

    ObjectManager::~ObjectManager() {
        for (auto currentEntity : entityList) {
            for (auto obj : *currentEntity) {
                delete obj;
            }
        }
        entityList.clear();
    }

    vector<vector<Entity*>*> ObjectManager::getEntityList() {
        return entityList;
    }

    Player* ObjectManager::addPlayer() {
        Player* player = new Player();
        playerList.clear();
        playerList.push_back(player);
        return player;
    }
    Ammo* ObjectManager::addAmmo(Texture texture, Vector2f pos, Vector2f behavior, int damages) {
        Ammo* ammo = new Ammo(texture, pos, behavior, damages);
        effectList.push_back(ammo);
        return ammo;
    }
    Ray* ObjectManager::addRay(Texture texture, Vector2f pos, Vector2f behavior, int i) {
        Ray* ray = new Ray(texture, pos, behavior);
        if (i < 35) {
            ray->addToLinkedEntities(addRay(texture, Vector2f(ray->getPos().x, ray->getDown()), behavior, i + 1));
        }
        if (i == 0) {
            rayList.push_back(ray);
        }
        return ray;
    }
    Enemy* ObjectManager::addEnemy(int type = BASIC_SHIP) {
        int xRange = int(screenWidth) - 100;
        float randX = float(rand() % xRange + 50);
        float randY = float(rand() % 110 + 20);
        Vector2f randPos(randX, randY);
        Enemy* enemy;
        if (type == BASIC_SHIP) { //basic bitches
            enemy = new Enemy(basicShip, randPos, 2, 100.f);
        }
        else if (type == SPEC_SHIP) { //shotgun ships
            enemy = new Enemy(specShip, randPos, 1, 90.f, 3, vector<Vector2f>({ Vector2f(-0.5f,1.f), Vector2f(0.f,1.f), Vector2f(0.5f,1.f) }));
            enemy->setFrameRate(1.2f);
        }
        else if (type == DOUBLE_BARREL_SHIP) {
            enemy = new Enemy(doubleBarrelShip, randPos, 4, 90.f, 2, vector<Vector2f>({ Vector2f(0.f, 1.f), Vector2f(0.f, 1.f) }), vector<float>({ -15.f, 15.f }));
        }
        else if (type == BOSS_CRUISER) {
            enemy = new Enemy(bossCruiser, Vector2f(float(screenWidth / 2), 100.f), 40, 30.f, 4, vector<Vector2f>({ Vector2f(-0.3f,1.f), Vector2f(0.3f,1.f),
                    Vector2f(-0.7f, 1.f), Vector2f(0.7f,1.f) }));
            enemy->setAsBoss(); enemy->setName("Liberator");
        }
        else if (type == ALIEN_SHIP) {
            enemy = new Enemy(alienShip, randPos, 8, 110.f, 2, vector<Vector2f>({ Vector2f(0.f, 1.f), Vector2f(0.f, 1.f) }), vector<float>({ -8.f, 8.f }));
            enemy->getSprite()->setScale(Vector2f(1.1f, 1.1f));
            enemy->setFrameRate(0.6f);
        }
        else if (type == BOSS_ALIEN_SHIP) {
            float ammoAngle = 0.6f;
            enemy = new Enemy(bossAlienShip, Vector2f(float(screenWidth / 2), 100.f), 70, 50.f, 5,
                vector<Vector2f>({ Vector2f(ammoAngle, 1.f), Vector2f(ammoAngle, 1.f), Vector2f(0.f, 1.f), Vector2f(-ammoAngle, 1.f), Vector2f(-ammoAngle, 1.f) }),
                vector<float>({ -50.f, -30.f, 0.f, 30.f, 50.f }));
            enemy->setFrameRate(2.f);
            enemy->setAsBoss(); enemy->setName("Hive Mind");
        }
        else if (type == NAUTOLAN_SHIP) {
            enemy = new Enemy(nautolanShip,randPos, 6, 50.f);
            enemy->getSprite()->setScale(Vector2f(1.8f, 1.8f));
            enemy->setFrameRate(3.f);
        }
        else if (type == BOSS_NAUTOLAN_SHIP) {
            enemy = new Enemy(bossNautolanShip, Vector2f(float(screenWidth / 2), 100.f), 100, 50.f);
            enemy->getSprite()->setScale(Vector2f(2.f, 2.f));
            enemy->setFrameRate(4.5f);
            enemy->setAsBoss(); enemy->setName("Atlantic Empire's fleet commander");
        }
        else { enemy = new Enemy(basicShip, randPos, 6, 100.f); }
        enemy->setType(type);
        enemyList.push_back(enemy);
        return enemy;
    }
    Bonus* ObjectManager::addBonus(Vector2f pos, int type) {
        Bonus* bonus;
        if (type == HEALING) {
            bonus = new Bonus(bonusHealTexture, pos, HEALING);
        }
        else if (type == RIFLE) {
            bonus = new Bonus(bonusRifleTexture, pos, RIFLE);
        }
        else if (type == SNIPER) {
            bonus = new Bonus(bonusSniperTexture, pos, SNIPER);
        }
        else if (type == PISTOL) {
            bonus = new Bonus(bonusPistolTexture, pos, PISTOL);
        }
        else {
            bonus = new Bonus(bonusHealTexture, pos, HEALING);
        }
        bonusList.push_back(bonus);
        return bonus;
    }

    void ObjectManager::deleteEntity(int type, Entity* entity) {
        cout << "\n\033[31mDeletion of type " << type << "\033[0m\n";
        int i = 0;
        for (int index = 0; index < (*entityList[type]).size(); index++) {
            if ((*entityList[type])[index] == entity) { i = index; }
        }
        delete (*entityList[type])[i];
        auto pos = entityList[type]->begin() + i;
        entityList[type]->erase(pos);
        cout << "\n\033[31mEnd of deletion with i being " << i << " and vector" << type << " now of size " << (*entityList[type]).size() << "\033[0m\n";
    }

    void ObjectManager::addExplosion(Vector2f pos, float scale) {
        Explosion* explo = new Explosion(pos, scale);
        explosionList.push_back(explo);
    }
    BackgroundProp* ObjectManager::addBackgroundProp(int type, Vector2f pos, float scale, int asteroType) {
        if (type == PLANET) {
            if (asteroType == PLANET1) {
                BackgroundProp* prop = new BackgroundProp(&backgroundPlanetTexture1, pos, scale, asteroType);
                backgroundPlanetList.push_back(prop);
                return prop;
            }
            else if (asteroType == BLACK_HOLE) {
                BackgroundProp* prop = new BackgroundProp(&backgroundBlackHoleTexture, pos, scale, asteroType);
                backgroundPlanetList.push_back(prop);
                return prop;
            }
            else if (asteroType == ALIENBASE) {
                BackgroundProp* prop = new BackgroundProp(&backgroundAlienBaseTexture, pos, scale, asteroType);
                backgroundPlanetList.push_back(prop);
                return prop;
            }
            else if (asteroType == ASTERO1) {
                BackgroundProp* prop = new BackgroundProp(&backgroundAsteroidTexture1, pos, scale, asteroType);
                backgroundPlanetList.push_back(prop);
                return prop;
            }
            else {
                BackgroundProp* prop = new BackgroundProp(&backgroundAsteroidTexture2, pos, scale, asteroType);
                backgroundPlanetList.push_back(prop);
                return prop;
            }
        }
        else {
            if (asteroType == ASTERO1) {
                BackgroundProp* prop = new BackgroundProp(&backgroundAsteroidTexture1, pos, scale, asteroType);
                backgroundAsteroidList.push_back(prop);
                return prop;
            }
            else if (asteroType == ASTERO2) {
                BackgroundProp* prop = new BackgroundProp(&backgroundAsteroidTexture2, pos, scale, asteroType);
                backgroundAsteroidList.push_back(prop);
                return prop;
            }
            else {
                BackgroundProp* prop = new BackgroundProp(&backgroundWaterBubbleTexture, pos, scale, asteroType);
                backgroundAsteroidList.push_back(prop);
                return prop;
            }
        }
    }
    vector<SFX*>* ObjectManager::getExplosionList() { return &explosionList; }
    vector<vector<SFX*>*>* ObjectManager::getBackgroundPropList() { return &backgroundPropList; }

