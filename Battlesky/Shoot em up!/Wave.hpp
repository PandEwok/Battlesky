#pragma once

#include "Manager.hpp"

using namespace sf;
using namespace std;

class Wave {
private:
	int theme = 0;
	bool isTransition = false;
	bool isAfterTransition = false;
	bool isBoss = false;
	float spawnCooldown = 6;
	int spawnNumber = 2;
	int enemyLimit = 6;
	vector<int> enemyTypes = {};
	vector<float> enemyTypesProb = {};
public:
	enum WaveTheme
	{
		GALAXY = 0,
		ALIEN = 1,
		ATLANTID = 2
	};
	Wave();
	void setSpawnCooldown(float value);
	void setSpawnNumber(int value);
	void setEnemyLimit(int value);
	void setEnemyTypes(vector<int> value);
	void setEnemyTypesProb(vector<float> value);
	void setTheme(int value);
	int getTheme();
	void setIsTransition(bool value);
	bool getIsTransition();
	void setIsAfterTransition(bool value);
	bool getIsAfterTransition();
	void setIsBoss(bool value);
	bool getIsBoss();
	void updateWave(float* enemiesSpawnCooldownNum, ObjectManager* manager);
};