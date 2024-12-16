#ifndef Entity_HPP
#define Entity_HPP

#include "SFX.hpp"


using namespace sf;
using namespace std;

class Entity {
protected:
    string name;
    float lifeTime = 0;
    float frameRate = 1.f, hurtTime = 10;
    int maxHp, hp, ammoAmount = 1, type = 0, weaponDamage = 1;
    float speed;
    Texture texture, linkedAmmoTexture = ammoTexture;
    Sprite sprite;
    Vector2f behavior;
    Clock shootCooldown;
    vector<Vector2f> ammoDirections = { Vector2f(0, -1) };
    vector<float> ammoPositions = {};
    vector<Entity*> linkedEntities = {};
    bool isBoss = false;
public:
    Entity(Texture _TEXTURE = basicShip, Vector2f _SCALE = Vector2f(1.5f, 1.5f), int _MAXHP = 10, float _SPEED = 100.f, Vector2f _BEHAVIOR = Vector2f(0.f, 1.f));

    string getName();
    void setName(string newName);
    float getLifeTime();
    void addToLifeTime(float value);
    float getFrameRate();
    void setFrameRate(float value);
    void addToFrameRate(float value);
    float getHurtTime();
    void setHurtTime(float value);
    void addToHurtTime(float value);
    Sprite* getSprite();
    Texture getTexture();
    Texture getLinkedAmmoTexture();
    void setLinkedAmmoTexture(Texture value);
    Vector2f getPos();
    void setColor(int r, int g, int b, int alpha = 255);
    int getHeight();
    int getWidth();
    float getLeft();
    float getRight();
    float getUp();
    float getDown();
    void setX(float x);
    void setY(float y);

    int getHp();
    int getMaxHp();
    void decreaseHp(int value = 1);
    int getWeaponDamage();
    void setWeaponDamage(int value);
    float getSpeed();
    void setSpeed(float value);
    Vector2f getBehavior();
    void setBehavior(Vector2f value);
    Clock getShootCooldown();
    void restartShootCooldown();
    int getAmmoAmount();
    vector<Vector2f> getAmmoDirections();
    void setAmmoDirections(vector<Vector2f> value);
    vector<float> getAmmoPositions();
    int getType();
    void setType(int typev);
    vector<Entity*> getLinkedEntities();
    void addToLinkedEntities(Entity* entity);
    void eraseLinkedEntities();
    void setAsBoss();
    bool getIsBoss();

    void move(Vector2f value);

    bool isColiding(Entity* other);

    void continueAnimation();
};

class Player : public Entity {
public:
    Player();
};

class Enemy : public Entity {
public:
    Enemy(Texture _TEXTURE, Vector2f _POS, int _MAXHP, float _SPEED, int _AMMOAMOUNT = 1, vector<Vector2f> _AMMODIRECTIONS = { Vector2f(0.f, 1.f) }, vector<float> _AMMOPOSITIONS = {});
};

class Ammo : public Entity {
public:
    Ammo(Texture _TEXTURE, Vector2f _POS, Vector2f _BEHAVIOR, int _DAMAGES = 1);
};

class Ray : public Entity {
public:
    Ray(Texture _TEXTURE, Vector2f _POS, Vector2f _BEHAVIOR);
};

class Bonus : public Entity {
public:
    Bonus(Texture _TEXTURE, Vector2f _POS, int _TYPE);
};

#endif