#include "Global.hpp"

using namespace sf;
using namespace std;

float screenWidth = 780.f, screenHeight = 900.f;
RenderWindow window(VideoMode(screenWidth, screenHeight), "Battlesky", Style::Close);
//textures
Texture playerShipYellowTexture;
Texture playerShipBlueTexture;
Texture playerShipGreenTexture;
Texture basicShip;
Texture specShip;
Texture doubleBarrelShip;
Texture bossCruiser;
Texture alienShip;
Texture alienFlameShip;
Texture bossAlienShip;
Texture nautolanShip;
Texture nautolanWaveShip;
Texture bossNautolanShip;
Texture ammoTexture;
Texture ammoTextureGreen;
Texture rayTexture;
Texture flameTexture;
Texture loadingRayTexture;
Texture spinningAmmoTexture;
Texture waveAmmoTexture;
Texture bonusHealTexture;
Texture bonusRifleTexture;
Texture bonusSniperTexture;
Texture bonusPistolTexture;
Texture explosionTexture;
SoundBuffer explosionSB;
Texture backgroundAsteroidTexture1;
Texture backgroundAsteroidTexture2;
Texture backgroundWaterBubbleTexture;
Texture backgroundPlanetTexture1;
Texture backgroundBlackHoleTexture;
Texture backgroundAlienBaseTexture;
Texture meteorTexture;
Texture alienDebrisTexture;

void loadTextures() {
	playerShipYellowTexture.loadFromFile("Images/tiny-spaceships/player_ship_yellow.png");
	playerShipBlueTexture.loadFromFile("Images/tiny-spaceships/player_ship_blue.png");
	playerShipGreenTexture.loadFromFile("Images/tiny-spaceships/player_ship_green.png");
	basicShip.loadFromFile("Images/tiny-spaceships/tiny_ship20.png");
	specShip.loadFromFile("Images/tiny-spaceships/tiny_ship15.png");
	doubleBarrelShip.loadFromFile("Images/tiny-spaceships/tiny_ship19.png");
	bossCruiser.loadFromFile("Images/Foozle_2DS0012_Void_EnemyFleet_1/Kla'ed/Base/PNGs/Kla'ed - Battlecruiser - Base.png");
	alienShip.loadFromFile("Images/free-pixel-art-enemy-spaceship-2d-sprites/PNG_Parts&Spriter_Animation/Ship2/Ship2.png");
	alienFlameShip.loadFromFile("Images/free-pixel-art-enemy-spaceship-2d-sprites/PNG_Parts&Spriter_Animation/Ship3/Ship3.png");
	bossAlienShip.loadFromFile("Images/free-pixel-art-enemy-spaceship-2d-sprites/PNG_Parts&Spriter_Animation/Ship6/Ship6.png");
	nautolanShip.loadFromFile("Images/Foozle_2DS0014_Void_EnemyFleet_3/Nautolan/Designs - Base/PNGs/Nautolan Ship - Scout - Base.png");
	nautolanWaveShip.loadFromFile("Images/Foozle_2DS0014_Void_EnemyFleet_3/Nautolan/Designs - Base/PNGs/Nautolan Ship - Support - Base.png");
	bossNautolanShip.loadFromFile("Images/Foozle_2DS0014_Void_EnemyFleet_3/Nautolan/Designs - Base/PNGs/Nautolan Ship - Dreadnought - Base.png");
	ammoTexture.loadFromFile("Images/Lunar Lander Upload/Effects/Fx_02_single.png");
	ammoTextureGreen.loadFromFile("Images/Lunar Lander Upload/Effects/Fx_02_single_green.png");
	rayTexture.loadFromFile("Images/Foozle_2DS0014_Void_EnemyFleet_3/Nautolan/Weapon Effects - Projectiles/PNGs/Nautolan - Ray.png");
	flameTexture.loadFromFile("Images/Particle FX 1.2 Free/Spritesheets/Flamethrower-Sheet-line.png");
	loadingRayTexture.loadFromFile("Images/Foozle_2DS0014_Void_EnemyFleet_3/Nautolan/Weapon Effects - Projectiles/PNGs/Nautolan - LoadingRay.png");
	spinningAmmoTexture.loadFromFile("Images/Foozle_2DS0014_Void_EnemyFleet_3/Nautolan/Weapon Effects - Projectiles/PNGs/Nautolan - Spinning Bullet.png");
	waveAmmoTexture.loadFromFile("Images/Foozle_2DS0014_Void_EnemyFleet_3/Nautolan/Weapon Effects - Projectiles/PNGs/Nautolan - Wave.png");
	bonusHealTexture.loadFromFile("Images/Icons/bonusHeal.png");
	bonusRifleTexture.loadFromFile("Images/Icons/bonusRifle.png");
	bonusSniperTexture.loadFromFile("Images/Icons/bonusSniper.png");
	bonusPistolTexture.loadFromFile("Images/Icons/bonusPistol.png");
	explosionTexture.loadFromFile("Images/free-pixel-art-enemy-spaceship-2d-sprites/PNG_Parts&Spriter_Animation/Explosions/Explosion1/Explosion1_spritesheet.png");
	explosionSB.loadFromFile("SoundEffects/Heavy_8bit_Explosions_Sounds/Medium/8bit_expl_medium_17.wav");
	meteorTexture.loadFromFile("Images/Lunar Lander Upload/Space Background/Asteroid1.png");
	alienDebrisTexture.loadFromFile("Images/Lunar Lander Upload/Space Background/alienBaseDebris.png");
}