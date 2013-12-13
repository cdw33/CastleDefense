#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include "SDL_TTF.h"
#include <ctime>
#include <algorithm>

static int GHOST_HEIGHT = 64;
static int GHOST_WIDTH = 71;

struct Enemies{
	double xCoor, yCoor, damage, hp, speed;
	int attackRate, lastAttack;
	vector<int> hitList;
};

class Enemy {
   
public:

    Enemy() {
        srand(time(0));
    };

	Graphics graphics;

	void drawEnemies() {
		for(int i=0; i<enemies.size(); i++){
			graphics.displaySprite("Images/Enemies/ghost.bmp",0,0,enemies[i]->xCoor,enemies[i]->yCoor,GHOST_WIDTH,GHOST_HEIGHT);
		}
    }

	void moveEnemy(Data &data, int wallAttack){
		for(int i=0; i<enemies.size(); i++){
			if(enemies[i]->xCoor >= SCREEN_WIDTH - CASTLE_WIDTH - 75) attack(data.health, i, wallAttack, data); //if enemy reaches wall, attack()

			else
				enemies[i]->xCoor+=enemies[i]->speed;	//else step speed distance
		}
	}

	void createEnemy(double damage, double hp, double speed, int attackRate){	
		enemies.push_back(new Enemies());	//add new enemy to vector
		enemies[enemies.size()-1]->xCoor=-GHOST_WIDTH;
		enemies[enemies.size()-1]->yCoor=40 + rand()%(680-GHOST_HEIGHT); //keeps enemies withing game screen

		enemies[enemies.size()-1]->damage=damage;
		enemies[enemies.size()-1]->hp=hp;
		enemies[enemies.size()-1]->speed=speed;
		enemies[enemies.size()-1]->attackRate = attackRate; //turn into seconds
		enemies[enemies.size()-1]->lastAttack = clock() - enemies[enemies.size()-1]->attackRate;
	}

	bool detectHit(double bulletX, double bulletY, int bulletWidth, int bulletHeight, int id, Data &data) {
		Bullet bulletValRef;
		//if bullet is in the same area as enemy
		for(int i = enemies.size()-1; i >= 0; --i){
			if (bulletY + bulletValRef.getHeight(data.bulletUpgrades) > enemies[i]->yCoor && bulletY < enemies[i]->yCoor + GHOST_HEIGHT && bulletX < enemies[i]->xCoor + GHOST_WIDTH && bulletX + bulletValRef.getWidth(data.bulletUpgrades) > enemies[i]->xCoor){
				if (bulletValRef.stopOnContact(data.bulletUpgrades) || hasNotHit(i, id)) {
					enemies[i]->hp = max(enemies[i]->hp - bulletValRef.getDamage(data.bulletUpgrades), 0.0);
					if (enemies[i]->hp == 0) {
						deleteEnemy(i);
						data.addMoney(1);
						++data.killed;
						++data.killedTotal;
						++data.points;
					}
					return true;
				}
			}
		}

		return false;
	}

	bool hasNotHit(int index, int id) {
		for(int i = 0; i < enemies[index]->hitList.size(); ++i) {
			if (enemies[index]->hitList[i] == id) {
				return false;
			}
		}

		enemies[index]->hitList.push_back(id);
		return true;
	}

	void deleteEnemy(int i){
		enemies.erase(enemies.begin() + i);
	}

	void deleteEnemies() {
		enemies.erase(enemies.begin(), enemies.begin() + enemies.size());
	}

	bool noEnemies() {
		return enemies.size() == 0;
	}

	void attack(int &health, int enemyIndex, int wallAttack, Data &data){
		if (clock() - enemies[enemyIndex]->lastAttack > enemies[enemyIndex]->attackRate) {
			health = max(health - enemies[enemyIndex]->damage, 0.0);
			enemies[enemyIndex]->lastAttack = clock();

			enemies[enemyIndex]->hp = max(enemies[enemyIndex]->hp - wallAttack, 0.0);
			if(enemies[enemyIndex]->hp == 0) {
				deleteEnemy(enemyIndex);
				++data.killed;
				++data.killedTotal;
			}
		}
	}

	void generateSpawnTime(vector<int> &waveTime, int waveNumber, const int ENEMIES_PER_WAVE) {
		for(int i = 0; i < waveNumber * ENEMIES_PER_WAVE; ++i) {
			waveTime.push_back(rand() % (5000 * waveNumber)); /* each wave released  span increases by 5 seconds in length */
		}
		sort(waveTime.rbegin(), waveTime.rend());
	
		/* makes it so that enemies are released imediatly */
		int min = waveTime[waveTime.size()-1];
		for(int i = 0; i < waveTime.size(); ++i) {
			waveTime[i] -= min;
		}
	}

private:
	vector<Enemies *> enemies;

};

#endif