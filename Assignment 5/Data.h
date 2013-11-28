#ifndef Data_H
#define Data_H

/* This is meant to be a container struct to make handling values easier and cleaner */
/* Add / remove items as necessary                                                   */

struct Data {
	Data(int money = 0, int points = 0, int killed= 0, int waveCount = 1, int wallDefUpgrades = 0, int wallOffUpgrades = 0, int bulletUpgrades = 0) {
		this->money = money;
		this->points = points;
		this->killed = killed;
		this->waveCount = waveCount;
		this->wallDefUpgrades = wallDefUpgrades;
		this->bulletUpgrades = bulletUpgrades;
	}

	int money,
		points,
		killed,
		waveCount,
		wallDefUpgrades,    /* Intended to keep track of */
		wallOffUpgrades,    /*    number of upgrades     */
		bulletUpgrades;     /*        purchased          */ 
};

#endif