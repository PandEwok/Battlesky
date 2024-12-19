#ifndef Global_HPP
#define Global_HPP

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


extern float screenWidth, screenHeight;
extern RenderWindow window;
//textures
extern Texture playerShipYellowTexture;
extern Texture playerShipBlueTexture;
extern Texture playerShipGreenTexture;
extern Texture basicShip;
extern Texture specShip;
extern Texture doubleBarrelShip;
extern Texture bossCruiser;
extern Texture alienShip;
extern Texture bossAlienShip;
extern Texture nautolanShip;
extern Texture bossNautolanShip;
extern Texture ammoTexture;
extern Texture rayTexture;
extern Texture loadingRayTexture;
extern Texture spinningAmmoTexture;
extern Texture bonusHealTexture;
extern Texture bonusRifleTexture;
extern Texture bonusSniperTexture;
extern Texture bonusPistolTexture;
extern Texture explosionTexture;
extern SoundBuffer explosionSB;
extern Texture backgroundAsteroidTexture1;
extern Texture backgroundAsteroidTexture2;
extern Texture backgroundWaterBubbleTexture;
extern Texture backgroundPlanetTexture1;
extern Texture backgroundBlackHoleTexture;
extern Texture backgroundAlienBaseTexture;
extern Texture meteorTexture;
extern Texture alienDebrisTexture;


void loadTextures();

#endif