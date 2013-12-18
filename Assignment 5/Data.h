#ifndef Data_H
#define Data_H

/* This is meant to be a container struct to make handling values easier and cleaner */
/* Add / remove items as necessary                                                   */

struct Data {
	Data(int health = 0, int money = 0, int moneyTotal = 0, int points = 0, int killed= 0, int killedTotal = 0, int waveCount = 1, int shotsHit = 0, int shotsFired = 0, int rateOfFire = 0, int wallDefUpgrades = 0, int wallOffUpgrades = 0, int bulletUpgrades = 0) {
		this->health = health;
		this->money = money;
		this->money = moneyTotal;
		this->points = points;
		this->killed = killed;
		this->killed = killedTotal;
		this->waveCount = waveCount;
		this->shotsHit = shotsHit;
		this->shotsFired = shotsFired;
		this->rateOfFire = rateOfFire;
		this->wallDefUpgrades = wallDefUpgrades;  /* Type of wall being used                     */
		this->wallOffUpgrades = wallOffUpgrades;  /* Type of offensive upgrade the wall is using */
		this->bulletUpgrades = bulletUpgrades;    /* Type of bullet being used                   */
	}

	int health,
		money,
		moneyTotal,
		points,
		killed,
		killedTotal,
		waveCount,
		shotsHit,
		shotsFired,
		rateOfFire,		  /*                           */
		wallDefUpgrades,  /* Intended to keep track of */
		wallOffUpgrades,  /*    number of upgrades     */
		bulletUpgrades;   /*        purchased          */ 

	void resetData() {
		health = 0;
		money = 0;
		moneyTotal = 0;
		points = 0;
		killed = 0;
		killedTotal = 0;
		waveCount = 1;
		shotsHit = 0;
		shotsFired = 0;
		rateOfFire = 0;
		wallDefUpgrades = 0;
		wallOffUpgrades = 0;
		bulletUpgrades = 0;
	}

	void addMoney(int toAdd) {
		money += toAdd;
		moneyTotal += toAdd;
	}
};

#endif