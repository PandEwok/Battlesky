#ifndef SFX_HPP
#define SFX_HPP

#include "Global.hpp"


using namespace sf;
using namespace std;


class SFX {
protected:
    Clock frameClock;
    Sprite sprite;
    Vector2f pos;
    Vector2u size = Vector2u(1,1);
    bool isOffMap = false;
    int type = 2;
public:
    SFX(Vector2f _POS, Vector2u _SIZE);
    Sprite* getSprite();
    Vector2f getPosition();
    Texture getTexture();
    Clock* getFrameClock();
    Vector2u getSize();
    bool getIsOffMap();
    void setIsOffMap(bool value);
    int getType();
};
class Explosion : public SFX {
public:
    Explosion(Vector2f _POS, float _SCALE = 0.7f);
};
class BackgroundProp : public SFX {
public:
    BackgroundProp(Texture* _TEXTURE, Vector2f _POS, float _SCALE = 0.7f, int _TYPE = 2);
};

#endif