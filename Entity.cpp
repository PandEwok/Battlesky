
#include "Entity.hpp"
using namespace sf;
using namespace std;



Entity::Entity(Texture _TEXTURE, Vector2f _SCALE, int _MAXHP, float _SPEED, Vector2f _BEHAVIOR) : texture(_TEXTURE), maxHp(_MAXHP), hp(_MAXHP), speed(_SPEED), behavior(_BEHAVIOR) {
    sprite.setTexture(texture);
    sprite.setScale(_SCALE);
    sprite.setOrigin(Vector2f(texture.getSize()) / 2.f);
}

string Entity::getName() { return name; }
void Entity::setName(string newName) { name = newName; }
float Entity::getLifeTime() { return lifeTime; }
void Entity::addToLifeTime(float value) { lifeTime += value; }
float Entity::getFrameRate() { return frameRate; }
void Entity::setFrameRate(float value) { frameRate = value; }
void Entity::addToFrameRate(float value) { frameRate += value; }
float Entity::getHurtTime() { return hurtTime; }
void Entity::setHurtTime(float value) { hurtTime = value; }
void Entity::addToHurtTime(float value) { hurtTime += value; }
Sprite* Entity::getSprite() { return &sprite; }
Texture Entity::getTexture() { return texture; }
Texture Entity::getLinkedAmmoTexture(){ return linkedAmmoTexture; }
void Entity::setLinkedAmmoTexture(Texture value) { linkedAmmoTexture = value; }
Vector2f Entity::getPos() { return sprite.getPosition(); }
void Entity::setColor(int r, int g, int b, int alpha) { return sprite.setColor(Color(r, g, b, alpha)); }
int Entity::getHeight() { return sprite.getGlobalBounds().height; }
int Entity::getWidth() { return sprite.getGlobalBounds().width; }
float Entity::getLeft() { return sprite.getGlobalBounds().left; }
float Entity::getRight() { return (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width); }
float Entity::getUp() { return sprite.getGlobalBounds().top; }
float Entity::getDown() { return (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height); }
void Entity::setX(float x) { sprite.setPosition(Vector2f(x, sprite.getPosition().y)); }
void Entity::setY(float y) { sprite.setPosition(Vector2f(sprite.getPosition().x, y)); }

int Entity::getHp() { return hp; }
int Entity::getMaxHp() { return maxHp; }
void Entity::decreaseHp(int value) {
    hp -= value;
}
int Entity::getWeaponDamage() { return weaponDamage; }
void Entity::setWeaponDamage(int value) { weaponDamage = value; }

float Entity::getSpeed(){ return speed; }
void Entity::setSpeed(float value) { speed = value; }

Vector2f Entity::getBehavior() { return behavior; }
void Entity::setBehavior(Vector2f value) { behavior = value; }
Clock Entity::getShootCooldown() { return shootCooldown; }
void Entity::restartShootCooldown() { shootCooldown.restart(); }
int Entity::getAmmoAmount() { return ammoAmount; }
vector<Vector2f> Entity::getAmmoDirections() { return ammoDirections; }
void Entity::setAmmoDirections(vector<Vector2f> value) { ammoDirections = value; }
vector<float> Entity::getAmmoPositions() { return ammoPositions; }
int Entity::getType() { return type; }
void Entity::setType(int typev) { type = typev; }
vector<Entity*> Entity::getLinkedEntities() { return linkedEntities; }
void Entity::addToLinkedEntities(Entity* entity) { linkedEntities.push_back(entity); }
void Entity::eraseLinkedEntities() {
    for (int i = 0; i < linkedEntities.size(); i++) {
        linkedEntities[i]->eraseLinkedEntities();
        auto pos = linkedEntities.begin() + i;
        linkedEntities.erase(pos);
    }
}
void Entity::setAsBoss() { isBoss = true; }
bool Entity::getIsBoss() { return isBoss; }

void Entity::move(Vector2f value) {
    sprite.move(value * speed);
}

bool Entity::isColiding(Entity* other) {
    if (sprite.getGlobalBounds().intersects(other->getSprite()->getGlobalBounds())) { return true; }
    return false;
}

void Entity::continueAnimation() {
    if (sprite.getTextureRect().left >= texture.getSize().x - sprite.getTextureRect().width) {
        sprite.setTextureRect(IntRect(0, 0, sprite.getTextureRect().width, sprite.getTextureRect().height));
    }
    else {
        IntRect rect = sprite.getTextureRect();
        rect.left += sprite.getTextureRect().width;
        sprite.setTextureRect(rect);
    }
}

Player::Player() : Entity(playerShipYellowTexture, Vector2f(1.5f, 1.5f), 10, 350.f, Vector2f(0.f, 1.f)) {
    sprite.setPosition(Vector2f(screenWidth / 2.f, screenHeight * 0.8f));
    setFrameRate(0.25f);
    weaponDamage = 2;
}

Enemy::Enemy(Texture _TEXTURE, Vector2f _POS, int _MAXHP, float _SPEED, int _AMMOAMOUNT, vector<Vector2f> _AMMODIRECTIONS, vector<float> _AMMOPOSITIONS) : Entity(_TEXTURE, Vector2f(1.5f, 1.5f), _MAXHP, _SPEED, Vector2f(0.f, 1.f)) {
    sprite.setRotation(180.f);
    sprite.setPosition(_POS);
    ammoAmount = _AMMOAMOUNT;
    ammoDirections = _AMMODIRECTIONS;
    if (_AMMOPOSITIONS.size() == 0) {
        for (int i = 0; i < ammoAmount; i++) { ammoPositions.push_back(0.f); }
    }
    else { ammoPositions = _AMMOPOSITIONS; }
}

Ammo::Ammo(Texture _TEXTURE, Vector2f _POS, Vector2f _BEHAVIOR, int _DAMAGES) : Entity(_TEXTURE, Vector2f(1.2f, 1.2f), _DAMAGES, 300.f, _BEHAVIOR) {
    int x;
    if (texture.getSize().y > texture.getSize().x) {
        x = texture.getSize().x;
    }
    else { x = texture.getSize().y; }
    sprite.setTextureRect(IntRect(0, 0, x, texture.getSize().y));
    sprite.setOrigin(Vector2f(sprite.getTextureRect().getSize()) / 2.f);
    sprite.setPosition(_POS);
}

Ray::Ray(Texture _TEXTURE, Vector2f _POS, Vector2f _BEHAVIOR) : Entity(_TEXTURE, Vector2f(1.5f, 1.5f), 1, 300.f, _BEHAVIOR) {
    int x;
    if (texture.getSize().y > texture.getSize().x) {
        x = texture.getSize().x;
    }
    else { x = texture.getSize().x / 4.f; }
    sprite.setTextureRect(IntRect(0, 0, x, texture.getSize().y));
    sprite.setOrigin(Vector2f(texture.getSize().x / 4.f / 2.f, texture.getSize().y / 2.f));
    sprite.setPosition(_POS);
}

Bonus::Bonus(Texture _TEXTURE, Vector2f _POS, int _TYPE = 1) : Entity(_TEXTURE, Vector2f(2.f, 2.f)) {
    sprite.setTextureRect(IntRect(0, 0, texture.getSize().x / 2, texture.getSize().y));
    sprite.setPosition(_POS);
    setType(_TYPE);
    speed = 100.f;
}