#ifndef CASTLE_Hstatic int Screen
#define CASTLE_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include "Data.h"
#include <iostream>

using namespace std;

static int SCREEN_WIDTH = 1280;
static int SCREEN_HEIGHT = 720;

static int STATBAR_HEIGHT = 40;

static int GAME_HEIGHT = SCREEN_HEIGHT - STATBAR_HEIGHT;
static int GAME_WIDTH = SCREEN_WIDTH;

static int CASTLE_WIDTH = 81;
static int CASTLE_HEIGHT = 628;
static int CASTLE_OFFENCE_WIDTH = 91;
static int CASTLE_OFFENCE_HEIGHT = 641;

class Castle { 
	public:	
		struct defData { /* defensive wall data */
			const char* path;
			int healthCap;
			int cost;
		};
		struct offData { /* Offensive wall data */
			const char* path;
			int dammage; /* Damage over time for those attacking the castle */
			int cost;
		};

		Graphics graphics;
		defData* defInfo;
		offData* offInfo;
		static const int def_UPGRADES = 7; /* 0 based indexing */
		static const int OFF_UPGRADES = 7;  /* 0 based indexing */

		Castle() {
			defInfo = new defData[8];
				setVal(defInfo[0], "Images/Castle_Defense/hay.bmp", 10, 0);
				setVal(defInfo[1], "Images/Castle_Defense/wood.bmp", 25, 20);
				setVal(defInfo[2], "Images/Castle_Defense/brick.bmp", 45, 50);
				setVal(defInfo[3], "Images/Castle_Defense/iron.bmp", 70, 70);
				setVal(defInfo[4], "Images/Castle_Defense/steel.bmp", 100, 100);
				setVal(defInfo[5], "Images/Castle_Defense/mithril.bmp", 135, 140);
				setVal(defInfo[6], "Images/Castle_Defense/diamond.bmp", 175, 190);
				setVal(defInfo[7], "Images/Castle_Defense/lonsdaleite.bmp", 220, 250);

			offInfo = new offData[8];
				setVal(offInfo[0], "Images/Castle_Offense/nothing.bmp", 0, 0);
				setVal(offInfo[1], "Images/Castle_Offense/barbed_wire.bmp", 3, 10);
				setVal(offInfo[2], "Images/Castle_Offense/stakes.bmp", 7, 20);
				setVal(offInfo[3], "Images/Castle_Offense/spike.bmp", 12, 40);
				setVal(offInfo[4], "Images/Castle_Offense/poison_spike.bmp", 18, 70);
				setVal(offInfo[5], "Images/Castle_Offense/lava_poison_spike.bmp", 25, 100);
		};

		~Castle() {
			delete [] defInfo;
			delete [] offInfo;
		}

		void setVal(defData &structPiece, const char* path, int healthCap, int cost) {
			structPiece.path = path;
			structPiece.healthCap = healthCap;
			structPiece.cost = cost;
		}

		void setVal(offData &structPiece, const char* path, int dammage, int cost) {
			structPiece.path = path;
			structPiece.dammage = dammage;
			structPiece.cost = cost;
		}

		/* Can be called at the start of each new wave to ensure proper health count is being used*/
		int setHealth(int wallDefUpgrades) { return defInfo[wallDefUpgrades].healthCap; }
		int setHealth(Data &data) { return defInfo[data.wallDefUpgrades].healthCap; }

		static const int totaldefenceUpgrades() { return def_UPGRADES; }
		static const int totalOffenceUpgrades() { return OFF_UPGRADES; }

		void drawCastle(int wallDefUpgrades = 0, int walloffUpgrades = 0) {
			graphics.displaySprite(defInfo[wallDefUpgrades].path, 0, 0, SCREEN_WIDTH-CASTLE_WIDTH , STATBAR_HEIGHT+(((SCREEN_HEIGHT - STATBAR_HEIGHT)/2)-(CASTLE_HEIGHT/2)),CASTLE_WIDTH,CASTLE_HEIGHT);
			graphics.displaySprite(offInfo[walloffUpgrades].path, 0, 0, SCREEN_WIDTH-CASTLE_OFFENCE_WIDTH, STATBAR_HEIGHT+(((SCREEN_HEIGHT - STATBAR_HEIGHT)/2)-(CASTLE_OFFENCE_HEIGHT/2)), CASTLE_OFFENCE_WIDTH, CASTLE_OFFENCE_HEIGHT);
		}
};

#endif