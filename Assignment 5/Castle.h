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
static int CASTLE_OFFENCE_HEIGHT = 649;

class Castle { 
	public:	
		struct defData { /* defensive wall data */
			const char* path;
			int healthCap;
			int cost;
		};
		struct offData { /* Offensive wall data */
			const char* path;
			int damage; /* Damage over time for those attacking the castle */
			int cost;
		};

		Graphics graphics;
		defData* defInfo;
		offData* offInfo;
		bool flip;
		static const int DEF_UPGRADES = 7; /* 0 based indexing */
		static const int OFF_UPGRADES = 7;  /* 0 based indexing */

		Castle() {
			defInfo = new defData[8];
				setVal(defInfo[0], "Images/Castle_Defense/hay.bmp", 20, 0);
				setVal(defInfo[1], "Images/Castle_Defense/wood.bmp", 40, 10);
				setVal(defInfo[2], "Images/Castle_Defense/brick.bmp", 60, 20);
				setVal(defInfo[3], "Images/Castle_Defense/iron.bmp", 80, 40);
				setVal(defInfo[4], "Images/Castle_Defense/steel.bmp", 120, 80);
				setVal(defInfo[5], "Images/Castle_Defense/mithril.bmp", 160, 100);
				setVal(defInfo[6], "Images/Castle_Defense/diamond.bmp", 250, 130);
				setVal(defInfo[7], "Images/Castle_Defense/lonsdaleite.bmp", 350, 200);

			offInfo = new offData[9];
				setVal(offInfo[0], "Images/Castle_Offense/nothing.bmp", 0, 0);
				setVal(offInfo[1], "Images/Castle_Offense/barbed_wire.bmp", 1, 20);
				setVal(offInfo[2], "Images/Castle_Offense/stakes.bmp", 2, 30);
				setVal(offInfo[3], "Images/Castle_Offense/spike.bmp", 3, 40);
				setVal(offInfo[4], "Images/Castle_Offense/poison_spike.bmp", 4, 100);
				setVal(offInfo[5], "Images/Castle_Offense/lava.bmp", 5, 130);
				setVal(offInfo[6], "Images/Castle_Offense/lava_poison_spike.bmp", 6, 160);
				setVal(offInfo[7], "Images/Castle_Offense/electric_1.bmp", 7, 200);  /* Part 1 - use this index for values*/
				setVal(offInfo[8], "Images/Castle_Offense/electric_2.bmp", -1, -1);  /* Part 2 */

				flip = false;
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

		void setVal(offData &structPiece, const char* path, int damage, int cost) {
			structPiece.path = path;
			structPiece.damage = damage;
			structPiece.cost = cost;
		}

		/* Can be called at the start of each new wave to ensure proper health count is being used*/
		int setHealth(int wallDefUpgrades) { return defInfo[wallDefUpgrades].healthCap; }
		int setHealth(Data &data) { return defInfo[data.wallDefUpgrades].healthCap; }

		static const int totaldefenceUpgrades() { return DEF_UPGRADES; }
		static const int totalOffenceUpgrades() { return OFF_UPGRADES; }

		void drawCastle(int wallDefUpgrades = 0, int walloffUpgrades = 0) {
			graphics.displaySprite(defInfo[wallDefUpgrades].path, 0, 0, SCREEN_WIDTH-CASTLE_WIDTH , STATBAR_HEIGHT+(((SCREEN_HEIGHT - STATBAR_HEIGHT)/2)-(CASTLE_HEIGHT/2)),CASTLE_WIDTH,CASTLE_HEIGHT);

			if(walloffUpgrades != 7) {
				graphics.displaySprite(offInfo[walloffUpgrades].path, 0, 0, SCREEN_WIDTH-CASTLE_OFFENCE_WIDTH, STATBAR_HEIGHT+(((SCREEN_HEIGHT - STATBAR_HEIGHT)/2)-(CASTLE_OFFENCE_HEIGHT/2))-1, CASTLE_OFFENCE_WIDTH, CASTLE_OFFENCE_HEIGHT);
			} else {
				if(flip) {
					graphics.displaySprite(offInfo[walloffUpgrades].path, 0, 0, SCREEN_WIDTH-CASTLE_OFFENCE_WIDTH, STATBAR_HEIGHT+(((SCREEN_HEIGHT - STATBAR_HEIGHT)/2)-(CASTLE_OFFENCE_HEIGHT/2))-1, CASTLE_OFFENCE_WIDTH, CASTLE_OFFENCE_HEIGHT);
				} else {
					graphics.displaySprite(offInfo[walloffUpgrades+1].path, 0, 0, SCREEN_WIDTH-CASTLE_OFFENCE_WIDTH, STATBAR_HEIGHT+(((SCREEN_HEIGHT - STATBAR_HEIGHT)/2)-(CASTLE_OFFENCE_HEIGHT/2))-1, CASTLE_OFFENCE_WIDTH, CASTLE_OFFENCE_HEIGHT);
				}
				flip = !flip;
			}
		}
};

#endif