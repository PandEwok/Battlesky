#include "Wave.hpp"

Wave::Wave() {}

void Wave::setSpawnCooldown(float value) { spawnCooldown = value; }

void Wave::setSpawnNumber(int value) { spawnNumber = value; }

void Wave::setEnemyLimit(int value) { enemyLimit = value; }

void Wave::setEnemyTypes(vector<int> value) { enemyTypes = value; }

void Wave::setEnemyTypesProb(vector<float> value) { enemyTypesProb = value; }

void Wave::setTheme(int value) { theme = value; }

int Wave::getTheme() { return theme; }

void Wave::setIsTransition(bool value) { isTransition = value; }

bool Wave::getIsTransition() { return isTransition; }

void Wave::setIsAfterTransition(bool value) { isAfterTransition = value; }

bool Wave::getIsAfterTransition() { return isAfterTransition; }

void Wave::setIsBoss(bool value) { isBoss = value; }

bool Wave::getIsBoss() { return isBoss; }

void Wave::updateWave(float* enemiesSpawnCooldownNum, ObjectManager* manager) {
    if (*enemiesSpawnCooldownNum >= spawnCooldown and manager->getEntityList()[manager->ENEMY]->size() < enemyLimit) {
        for (int i = 0; i < spawnNumber; i++) {
            if (manager->getEntityList()[manager->ENEMY]->size() < enemyLimit) {
                int randType = rand() % 100;
                for (int i = 0; i < enemyTypesProb.size(); i++) {
                    float prob = enemyTypesProb[i];
                    for (int j = 0; j < i; j++) {
                        prob += enemyTypesProb[j];
                    }
                    if (randType < prob) {
                        manager->addEnemy(enemyTypes[i]);
                        break;
                    }
                }
            }
        }
        *enemiesSpawnCooldownNum = 0;
    }
}


