
#include "SFX.hpp"
using namespace sf;
using namespace std;


SFX::SFX(Vector2f _POS, Vector2u _SIZE) : pos(_POS), size(_SIZE) {
    sprite.setOrigin(Vector2f(_SIZE)/2.f);
    sprite.setPosition(pos);
}
Sprite* SFX::getSprite() { return &sprite; }
Vector2f SFX::getPosition() { return sprite.getPosition(); }
Texture SFX::getTexture() { return *sprite.getTexture(); }
Clock* SFX::getFrameClock() { return &frameClock; }
Vector2u SFX::getSize() { return size; }
bool SFX::getIsOffMap() { return isOffMap; }
void SFX::setIsOffMap(bool value) { isOffMap = value; }
int SFX::getType() { return type; }


Explosion::Explosion(Vector2f _POS, float _SCALE) : SFX(_POS, Vector2u(explosionTexture.getSize().y, explosionTexture.getSize().y)) {
    sprite.setTexture(explosionTexture);
    sprite.setTextureRect(IntRect(0, 0, size.y, size.y));
    sprite.setScale(_SCALE, _SCALE);
}

BackgroundProp::BackgroundProp(Texture* _TEXTURE, Vector2f _POS, float _SCALE, int _TYPE) : SFX(_POS, _TEXTURE->getSize()) {
    type = _TYPE;
    sprite.setTexture(*_TEXTURE);
    sprite.setScale(_SCALE, _SCALE);
}