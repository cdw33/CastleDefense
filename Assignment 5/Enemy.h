#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include "SDL_TTF.h"
#include <ctime>
#include <algorithm>

static int GHOST_HEIGHT = 64;
static int GHOST_WIDTH = 71;

//Character_Data_Setup*********************************************************************************************************************
//*****************************************************************************************************************************************

/*
/ The way the wizards are set up, they have pointers to vectors that contain the information they need to be displayed.
/ They use pointers so that every wizard that is made will not need to contain this repetative information, saving space.
/
/ Through implementing this extra enemy, the code has gotten really jumbled and comfusing. I'm trying to comment code as
/ best I can so that it will be understandable in the future.
/
/ Ghosts have been replaced with minions. The ghost height and width constants have been kept because they are a conveniant 
/ measurement to use.
/
/ Notes
/	Enemy stats are created in the spawnEnemies function
/	Enemy release rates are found in generateSpawnTime as the const int RELEASE_RATE
/	The number of enemies that are spawned in a given wave are found in gnerateSpawnTime, as the conditinal in the for loops
*/


struct imageInfo {
	imageInfo(string s, int w, int h) {
		imagePath = s;
		width = w;
		height = h;
	};
	string imagePath;
	int width, height;
};

struct enemyData {
	enemyData() {
		wizardWP.push_back(imageInfo("Images/Enemies/wizard_idle.bmp",24,63));
		wizardWP.push_back(imageInfo("Images/Enemies/wizard_walk_1.bmp",29,63));
		wizardWP.push_back(imageInfo("Images/Enemies/wizard_walk_2.bmp",37,63));
		wizardAP.push_back(imageInfo("Images/Enemies/wizard_idle.bmp",24,63));
		wizardAP.push_back(imageInfo("Images/Enemies/wizard_attack_1.bmp",31,63));
		wizardAP.push_back(imageInfo("Images/Enemies/wizard_attack_2.bmp",43,63));
		wizardAP.push_back(imageInfo("Images/Enemies/wizard_attack_3.bmp",49,63));
		wizardSP.push_back(imageInfo("Images/Enemies/wizard_special_1.bmp",30,61));
		wizardSP.push_back(imageInfo("Images/Enemies/wizard_special_2.bmp",32,61));
		wizardSP.push_back(imageInfo("Images/Enemies/wizard_special_3.bmp",39,61));
		wizardSP.push_back(imageInfo("Images/Enemies/wizard_special_4.bmp",47,65));
	
		minionWP.push_back(imageInfo("Images/Enemies/minion_idle.bmp",56,63));
		minionWP.push_back(imageInfo("Images/Enemies/minion_walk_1.bmp",55,62));
		minionWP.push_back(imageInfo("Images/Enemies/minion_walk_2.bmp",55,61));
		minionWP.push_back(imageInfo("Images/Enemies/minion_walk_3.bmp",56,60));
		minionAP.push_back(imageInfo("Images/Enemies/minion_idle.bmp",56,63));
		minionAP.push_back(imageInfo("Images/Enemies/minion_attack_1.bmp",56,63));
		minionAP.push_back(imageInfo("Images/Enemies/minion_attack_2.bmp",56,63));
	}
	vector<imageInfo> wizardWP; /* walk path    */
	vector<imageInfo> wizardAP; /* attack path  */
	vector<imageInfo> wizardSP; /* special path */

	vector<imageInfo> minionWP; /* walk path    */
	vector<imageInfo> minionAP; /* attack path  */
};

struct Enemies {
	Enemies(double damage, double hp, double speed, int attackRate) {
		this->damage = damage;
		this->speed = speed;
		this->hp = hp;
		this->attackRate = attackRate;

		lastAttack = clock() - attackRate;
		xCoor=-GHOST_WIDTH;
		yCoor=40 + rand()%(680-GHOST_HEIGHT);
		specialFlag = true;
		attackFlag = true;
		walkFlag = true;
		attackAnimation = false;

		curAction = WALK;
		walkIndex = 0;
		attackIndex = 0;
		specialIndex = 0;
		curWalkTick = 0;
		curAttackTick = 0;
		curSpecialTick = 0;
	}

	double xCoor, yCoor, damage, hp, speed;
	int walkIndex, attackIndex, specialIndex,
		curWalkTick, curAttackTick, curSpecialTick,
		curAction, attackRate, lastAttack;
	bool specialFlag, attackFlag, walkFlag, attackAnimation;
	vector<int> hitList;
	vector<imageInfo>* walkPath;
	vector<imageInfo>* attackPath;
	vector<imageInfo>* specialPath;
	static const enum characterAction { WALK, ATTACK, SPECIAL };
};

struct Wizard : Enemies {
	Wizard(double damage, double hp, double speed, int attackRate) : Enemies(damage, hp, speed, attackRate) { 
		nextTeleport = clock() + SPECIAL_DELAY + rand() % SPECIAL_FREQUENCY;
		yCoor = 40 + rand()%(650-GHOST_HEIGHT) + 30;
	}
	static const int 
		WALK_TICKS = 3, 
		ATTACK_TICKS = 2,
		SPECIAL_TICKS = 3,
		SPECIAL_FREQUENCY = 3000, /* Increase for less teleporting */
		SPECIAL_DELAY = 5000; /* Minimum of 2 seconds between teleports */
	int 
		nextTeleport;

	void update() {
		/* Switch to your special ability animation if enough time has passed */
		if (clock() >= nextTeleport && curAction == WALK) {
			nextTeleport = clock() + SPECIAL_DELAY + rand() % SPECIAL_FREQUENCY;
			curAction = SPECIAL;
		}

		/* Walk Cycle */
		if (curAction == WALK) {

			/* Updates the counter for how long you are displaying an image */
			curWalkTick += (walkFlag ? 1 : -1);

			/* Sets teleport ability */
			if(walkIndex == walkPath->size()-1 && curWalkTick == WALK_TICKS) {
				walkFlag = !walkFlag;
				curWalkTick = 1;
			}

			/* Increments the picture you are looking at */
			if ((curWalkTick == WALK_TICKS && walkFlag) || (curWalkTick == 0 && !walkFlag)) {
				walkIndex += (walkFlag ? 1 : -1);
			}

			/* Reset the tick counter if you have reached the max / min */
			if (curWalkTick == 0 || curWalkTick == WALK_TICKS) {
				curWalkTick = (walkFlag ? 0 : WALK_TICKS);
			}
			
			/* End of cycle reached, restart */
			if (curWalkTick == WALK_TICKS &&  walkIndex == 0 && walkFlag == false) {
				curWalkTick = 0;
				walkFlag = true;
			}
		  /* Attack Cycle */
		} else if (curAction == ATTACK) {

			/* If you have attacked the castle, preform the attack animation (else the idle animation is displayed) */
			if (attackAnimation) {
				if (curAttackTick == ATTACK_TICKS) {
					attackIndex += (attackFlag ? 1 : -1);
				}
				if (curAttackTick == ATTACK_TICKS && attackIndex == attackPath->size()-1) {
					attackFlag = !attackFlag;
				}

				curAttackTick = (curAttackTick == ATTACK_TICKS ? 0 : curAttackTick + 1);
				if(attackIndex == 0 && !attackFlag) {
					curAttackTick == 0;
					attackFlag = !attackFlag;
					attackAnimation = false;
				}
			}

		  /* Special Cycle */
		} else if (curAction == SPECIAL) {

			/* Updates the counter for how long you are displaying an image */
			curSpecialTick += (specialFlag ? 1 : -1);

			/* Sets teleport ability */
			if(specialIndex == specialPath->size()-1 && curSpecialTick == SPECIAL_TICKS) {
				yCoor = 40 + rand()%(650-GHOST_HEIGHT) + 30;
				xCoor = min((int)(xCoor + 30 + rand()%150), (SCREEN_WIDTH - CASTLE_WIDTH - 50));
				specialFlag = !specialFlag;
			}

			/* Increments the picture you are looking at */
			if ((curSpecialTick == SPECIAL_TICKS && specialFlag) || (curSpecialTick == 0 && !specialFlag)) {
				specialIndex += (specialFlag ? 1 : -1);
			}

			/* Reset the tick counter if you have reached the max / min */
			if (curSpecialTick == 0 || curSpecialTick == SPECIAL_TICKS) {
				curSpecialTick = (specialFlag ? 0 : SPECIAL_TICKS);
			}
			
			/* If you are done teleporting, then start walking */
			if (curSpecialTick == SPECIAL_TICKS &&  specialIndex == 0 && specialFlag == false) {
				curSpecialTick = 0;
				specialFlag = true;
				curAction = WALK;
			}
		}
	}
};

struct Minion : Enemies {
	Minion(double damage, double hp, double speed, int attackRate) : Enemies(damage, hp, speed, attackRate) { }
	static const int 
		WALK_TICKS = 3, 
		ATTACK_TICKS = 1,
		SPECIAL_TICKS = 8,
		SPECIAL_FREQUENCY = 20000, /* Increase for less defending */
		SPECIAL_DELAY = 8000; /* Minimum of 2 seconds between defends */

	void update() {

		/* Walk Cycle */
		if (curAction == WALK) {
			/* Updates the counter for how long you are displaying an image */
			curWalkTick += (walkFlag ? 1 : -1);

			/* Sets teleport ability */
			if(walkIndex == walkPath->size()-1 && curWalkTick == WALK_TICKS) {
				walkFlag = !walkFlag;
				curWalkTick = 1;
			}

			/* Increments the picture you are looking at */
			if ((curWalkTick == WALK_TICKS && walkFlag) || (curWalkTick == 0 && !walkFlag)) {
				walkIndex += (walkFlag ? 1 : -1);
			}

			/* Reset the tick counter if you have reached the max / min */
			if (curWalkTick == 0 || curWalkTick == WALK_TICKS) {
				curWalkTick = (walkFlag ? 0 : WALK_TICKS);
			}
			
			/* End of cycle reached, restart */
			if (curWalkTick == WALK_TICKS &&  walkIndex == 0 && walkFlag == false) {
				curWalkTick = 0;
				walkFlag = true;
			}
		  /* Attack Cycle */
		} else if (curAction == ATTACK) {

			/* If you have attacked the castle, preform the attack animation (else the idle animation is displayed) */
			if (attackAnimation) {
				if (curAttackTick == ATTACK_TICKS) {
					attackIndex += (attackFlag ? 1 : -1);
				}
				if (curAttackTick == ATTACK_TICKS && attackIndex == attackPath->size()-1) {
					attackFlag = !attackFlag;
				}

				curAttackTick = (curAttackTick == ATTACK_TICKS ? 0 : curAttackTick + 1);
				if(attackIndex == 0 && !attackFlag) {
					curAttackTick == 0;
					attackFlag = !attackFlag;
					attackAnimation = false;
				}
			}
		} 
	}
};
//End_Character_Data_Setup**********************************************************************************************************************
//**********************************************************************************************************************************************


class Enemy {

private:
	Graphics graphics;
	enemyData enemyValues;
	vector<Wizard *> wizards;
	vector<Minion *> minions;
	vector<int> wizardSpawnTime;
	vector<int> minionSpawnTime;

public:
	static const enum characterIndex { WIZARD, MINION };
	static const enum characterAction { WALK, ATTACK, SPECIAL };

    Enemy() {
        srand(time(0));
    };

	//*******************************************************************
	// drawEnemies
	//*******************************************************************
	void drawEnemies() {
		for (int i=0; i<wizards.size(); i++) {
			wizards[i]->update();	
			graphics.displaySprite(getImage(wizards[i]).c_str(),0,0,wizards[i]->xCoor,wizards[i]->yCoor,getWidth(wizards[i]),getHeight(wizards[i]));
		}
		for (int i=0; i<minions.size(); i++) {
			minions[i]->update();	
			graphics.displaySprite(getImage(minions[i]).c_str(),0,0,minions[i]->xCoor,minions[i]->yCoor,getWidth(minions[i]),getHeight(minions[i]));
		}
    }

	//*******************************************************************
	// moveEnemy
	//*******************************************************************
	void moveEnemy(Data &data, int wallAttack){
		/* Minions */
		for (int i = 0; i < minions.size(); ++i) {
			if (minions[i]->xCoor >= SCREEN_WIDTH - CASTLE_WIDTH - 60) {
				minions[i]->curAction = ATTACK; //Set wizard for attacking animation
				attack(MINION, i, wallAttack, data); //if enemy reaches wall, attack()
			}
			else if (minions[i]->curAction != SPECIAL){
				minions[i]->xCoor+=minions[i]->speed;	//else step speed distance
			}
		}

		/* Wizards */
		for (int i = 0; i < wizards.size(); ++i) {
			if (wizards[i]->xCoor >= SCREEN_WIDTH - CASTLE_WIDTH - 50) {
				wizards[i]->curAction = ATTACK; //Set wizard for attacking animation
				attack(WIZARD, i, wallAttack, data); //if enemy reaches wall, attack()
			}
			else if (wizards[i]->curAction != SPECIAL){
				wizards[i]->xCoor+=wizards[i]->speed;	//else step speed distance
			}
		}
	}

	//*******************************************************************
	// createEnemy
	//*******************************************************************
	void createEnemy(int type, double damage, double hp, double speed, int attackRate){
		if (type == WIZARD) {
			wizards.push_back(new Wizard(damage, hp, speed, attackRate));   //add new enemy to vector
			wizards[wizards.size()-1]->walkPath = &enemyValues.wizardWP;
			wizards[wizards.size()-1]->attackPath = &enemyValues.wizardAP;
			wizards[wizards.size()-1]->specialPath = &enemyValues.wizardSP;
		} else if (type == MINION) {
			minions.push_back(new Minion(damage, hp, speed, attackRate));   //add new enemy to vector
			minions[minions.size()-1]->walkPath = &enemyValues.minionWP;
			minions[minions.size()-1]->attackPath = &enemyValues.minionAP;
		}
	}

	//*******************************************************************
	// detectHit
	//*******************************************************************
	bool detectHit(double bulletX, double bulletY, int bulletWidth, int bulletHeight, int id, Data &data) {
		Bullet bulletValRef;

		/* If bullet is in the same area as enemy - MINION */
		for (int i = minions.size()-1; i >= 0; --i){
			if (bulletY + bulletHeight > minions[i]->yCoor 
				&& bulletY < minions[i]->yCoor + getHeight(minions[i])
				&& bulletX < minions[i]->xCoor + getWidth(minions[i])
				&& bulletX + bulletWidth > minions[i]->xCoor) {
				
				if (bulletValRef.stopOnContact(data.bulletUpgrades) || hasNotHit(MINION, i, id)) {
					minions[i]->hp -= bulletValRef.getDamage(data.bulletUpgrades);
					++data.shotsHit;
					if (minions[i]->hp <= 0) {
						deleteEnemy(MINION, i);
						data.addMoney(data.waveCount);
						++data.killed;
						++data.killedTotal;
						data.points += 2;
					}
					return true;
				}
			}
		}

		/* If bullet is in the same area as enemy - WIZARDS */
		for (int i = wizards.size()-1; i >= 0; --i){
			if (bulletY + bulletHeight > wizards[i]->yCoor 
				&& bulletY < wizards[i]->yCoor + getHeight(wizards[i])
				&& bulletX < wizards[i]->xCoor + getWidth(wizards[i]) + 4 /* Extra width added because wizards are thin and bullets travel through them */
				&& bulletX + bulletWidth > wizards[i]->xCoor) {
				
				if (bulletValRef.stopOnContact(data.bulletUpgrades) || hasNotHit(WIZARD, i, id)) {
					wizards[i]->hp -= bulletValRef.getDamage(data.bulletUpgrades);
					++data.shotsHit;
					if (wizards[i]->hp <= 0) {
						deleteEnemy(WIZARD, i);
						data.addMoney(data.waveCount);
						++data.killed;
						++data.killedTotal;
						data.points += 2;
					}
					return true;
				}
			}
		}

		return false;
	}

	//*******************************************************************
	// hasNotHit
	//*******************************************************************
	bool hasNotHit(int type, int index, int id) {
		if (type == MINION) {
			for (int i = 0; i < minions[index]->hitList.size(); ++i) {
				if (minions[index]->hitList[i] == id) {
					return false;
				}
			}
			minions[index]->hitList.push_back(id);
		}		

		if (type == WIZARD) {
			for (int i = 0; i < wizards[index]->hitList.size(); ++i) {
				if (wizards[index]->hitList[i] == id) {
					return false;
				}
			}
			wizards[index]->hitList.push_back(id);
		}

		return true;
	}

	//*******************************************************************
	// deleteEnemy
	//*******************************************************************
	void deleteEnemy(int type, int i){
		if (type == MINION) {
			minions.erase(minions.begin() + i);
		} else if (type == WIZARD) {
			wizards.erase(wizards.begin() + i);
		} 
	}

	//*******************************************************************
	// deleteEnemies
	//*******************************************************************
	void deleteEnemies() {
		minions.erase(minions.begin(), minions.begin() + minions.size());
		wizards.erase(wizards.begin(), wizards.begin() + wizards.size());
	}

	//*******************************************************************
	// deleteSpawnTimes
	//*******************************************************************
	void deleteSpawnTimes() {
		minionSpawnTime.erase(minionSpawnTime.begin(), minionSpawnTime.begin() + minionSpawnTime.size());
		wizardSpawnTime.erase(wizardSpawnTime.begin(), wizardSpawnTime.begin() + wizardSpawnTime.size());
	}

	//*******************************************************************
	// noEnemies
	//*******************************************************************
	bool noEnemies() {
		return (minions.size() == 0 && wizards.size() == 0);
	}

	//*******************************************************************
	// noSpawns
	//*******************************************************************
	bool noSpawns() {
		return (minionSpawnTime.size() == 0 && wizardSpawnTime.size() == 0);
	}

	//*******************************************************************
	// attack
	//*******************************************************************
	void attack(int type, int enemyIndex, int wallAttack, Data &data){
		if (type == MINION) {
			if (clock() - minions[enemyIndex]->lastAttack > minions[enemyIndex]->attackRate) {
				data.health -= minions[enemyIndex]->damage;
				minions[enemyIndex]->lastAttack = clock();
				minions[enemyIndex]->attackAnimation = true;

				minions[enemyIndex]->hp -= wallAttack;
				if(minions[enemyIndex]->hp <= 0) {
					deleteEnemy(MINION, enemyIndex);
					++data.killed;
					++data.killedTotal;
				}
			}
		} else if (type == WIZARD) {
			if (clock() - wizards[enemyIndex]->lastAttack > wizards[enemyIndex]->attackRate) {
				data.health -= wizards[enemyIndex]->damage;
				wizards[enemyIndex]->lastAttack = clock();
				wizards[enemyIndex]->attackAnimation = true;

				wizards[enemyIndex]->hp -= wallAttack;
				if(wizards[enemyIndex]->hp <= 0) {
					deleteEnemy(WIZARD, enemyIndex);
					++data.killed;
					++data.killedTotal;
				}
			}
		} 
	}
	
	//*******************************************************************
	// generateSpawnTime
	//*******************************************************************
	void generateSpawnTime(int waveNumber, const int ENEMY_WAVE_RATE) {
		const int RELEASE_RATE = 3000;

		/* MINION SPAWN TIMES */
		for(int i = 0; i < (waveNumber < 7 ? waveNumber * 2 : (waveNumber + max(1.0,(waveNumber/3) + 0.0)) * ENEMY_WAVE_RATE); ++i) {
			minionSpawnTime.push_back(rand() % (RELEASE_RATE * waveNumber)); /* each wave released  span increases by RELEASE_RATE seconds in length */
		}
		sort(minionSpawnTime.rbegin(), minionSpawnTime.rend());
		if(minionSpawnTime.size() != 0) {
			/* makes it so that enemies are released imediatly */
			int min = minionSpawnTime[minionSpawnTime.size()-1];
			for(int i = 0; i < minionSpawnTime.size(); ++i) {
				minionSpawnTime[i] -= min;
			}
		}

		/* WIZARD SPAWN TIMES */
		for(int i = 0; i < waveNumber/2 - 1; ++i) {
			wizardSpawnTime.push_back(rand() % (RELEASE_RATE * (waveNumber-1))); /* each wave released  span increases by RELEASE_RATE seconds in length */
		}
		sort(wizardSpawnTime.rbegin(), wizardSpawnTime.rend());
	}

	//*******************************************************************
	// spawnEnemies
	//*******************************************************************
	void spawnEnemies(int startOfWave, int waveNumber) {
		/* MINION */ 
		while(minionSpawnTime.size() != 0 && minionSpawnTime[minionSpawnTime.size()-1] < clock() - startOfWave) {
			minionSpawnTime.erase(minionSpawnTime.begin() + minionSpawnTime.size() - 1);
			createEnemy(MINION, 1 + waveNumber, (1 + waveNumber/5) * 2, (rand()%2 ? 3 : 4) + waveNumber/8, 1000); /* Type, Damage, hp, speed, attack rate (in ms) */ /* <- speed increases every 6 rounds */
		}

		/* WIZARD */
		while(wizardSpawnTime.size() != 0 && wizardSpawnTime[wizardSpawnTime.size()-1] < clock() - startOfWave) {
			wizardSpawnTime.erase(wizardSpawnTime.begin() + wizardSpawnTime.size() - 1);
			createEnemy(WIZARD, (1 + waveNumber) * 2, (1 + waveNumber/5) * 4, (rand()%2 ? 2 : 3) + waveNumber/8, 2000); /* Type, Damage, hp, speed, attack rate (in ms) */ /* <- speed increases every 6 rounds */
		}
	}

	
	/* For the following 3 functions it should be noted that I accidently made a 2D matrix with vectors */
	/* hense the "[0]" in walkPath[0][enemy->walkIndex]. I don't know how I did it, and am thoroughly   */
	/* confused.																						*/

	//*******************************************************************
	// getWidth
	//*******************************************************************
	template <class T>
	int getWidth(T* enemy) {
		if(enemy->curAction == Enemy::WALK) {
			return enemy->walkPath[0][enemy->walkIndex].width;
		} else if (enemy->curAction == Enemy::ATTACK) {
			return enemy->attackPath[0][enemy->attackIndex].width;
		} else if (enemy->curAction == Enemy::SPECIAL) {
			return enemy->specialPath[0][enemy->specialIndex].width;
		}
	}

	//*******************************************************************
	// getHeight
	//*******************************************************************
	template <class T>
	int getHeight(T* enemy) {
		if(enemy->curAction == Enemy::WALK) {
			return enemy->walkPath[0][enemy->walkIndex].height;
		} else if (enemy->curAction == Enemy::ATTACK) {
			return enemy->attackPath[0][enemy->attackIndex].height;
		} else if (enemy->curAction == Enemy::SPECIAL) {
			return enemy->specialPath[0][enemy->specialIndex].height;
		}
	}

	//*******************************************************************
	//  getImage
	//*******************************************************************
	template <class T>
	string getImage(T* enemy) {
		if(enemy->curAction == Enemy::WALK) {
			return enemy->walkPath[0][enemy->walkIndex].imagePath;
		} else if (enemy->curAction == Enemy::ATTACK) {
			return enemy->attackPath[0][enemy->attackIndex].imagePath;
		} else if (enemy->curAction == Enemy::SPECIAL) {
			return enemy->specialPath[0][enemy->specialIndex].imagePath;
		}
	}
};

#endif