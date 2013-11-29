#ifndef CASTLE_H
#define CASTLE_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"

static int SCREEN_WIDTH = 1280;
static int SCREEN_HEIGHT = 720;

static int CASTLE_WIDTH = 81;
static int CASTLE_HEIGHT = 628;
static int CASTLE_OFFENCE_WIDTH = 91;
static int CASTLE_OFFENCE_HEIGHT = 641;

class Castle { 
	public:	
		struct deffData { /* Deffensive wall data */
			const char* path;
			int healthCap;
		};
		struct offData { /* Offensive wall data */
			const char* path;
			int dammage; /* Damage over time for those attacking the castle */
		};

		Graphics graphics;
		deffData* deffInfo;
		offData* offInfo;
		int health;

		Castle() {
			deffInfo = new deffData[8];
				setVal(deffInfo[0], "Images/Castle_Deffense/hay.bmp", 10);
				setVal(deffInfo[1], "Images/Castle_Deffense/wood.bmp", 25);
				setVal(deffInfo[2], "Images/Castle_Deffense/brick.bmp", 45);
				setVal(deffInfo[3], "Images/Castle_Deffense/iron.bmp", 70);
				setVal(deffInfo[4], "Images/Castle_Deffense/steel.bmp", 100);
				setVal(deffInfo[5], "Images/Castle_Deffense/mithril.bmp", 135);
				setVal(deffInfo[6], "Images/Castle_Deffense/diamond.bmp", 175);
				setVal(deffInfo[7], "Images/Castle_Deffense/lonsdaleite.bmp", 220);

			offInfo = new offData[8];
				setVal(offInfo[0], "Images/Castle_Offense/nothing.bmp", 0);
				setVal(offInfo[1], "Images/Castle_Offense/barbed_wire.bmp", 3);
				setVal(offInfo[2], "Images/Castle_Offense/stakes.bmp", 7);
				setVal(offInfo[3], "Images/Castle_Offense/spike.bmp", 12);
				setVal(offInfo[4], "Images/Castle_Offense/poison_spike.bmp", 18);
				setVal(offInfo[5], "Images/Castle_Offense/lava_poison_spike.bmp", 25);

			health = deffInfo[0].healthCap;
		};

		~Castle() {
			delete [] deffInfo;
			delete [] offInfo;
		}

		void setVal(deffData &structPiece, const char* path, int healthCap) {
			structPiece.path = path;
			structPiece.healthCap = healthCap;
		}

		void setVal(offData &structPiece, const char* path, int dammage) {
			structPiece.path = path;
			structPiece.dammage = dammage;
		}

		/* Can be called at the start of each new wave to ensure proper health count is being used*/
		void setHealth(int wallDefUpgrades) { health = deffInfo[wallDefUpgrades].healthCap; }
		void setHealth(Data &data) { health = deffInfo[data.wallDefUpgrades].healthCap; }

		void drawCastle(int wallDefUpgrades = 0, int walloffUpgrades = 0) {
			graphics.displaySprite(deffInfo[wallDefUpgrades].path, 0, 0, SCREEN_WIDTH-CASTLE_WIDTH ,(SCREEN_HEIGHT-CASTLE_HEIGHT)/2 ,CASTLE_WIDTH,CASTLE_HEIGHT);
			graphics.displaySprite(offInfo[walloffUpgrades].path, 0, 0, SCREEN_WIDTH-CASTLE_OFFENCE_WIDTH, (SCREEN_HEIGHT-CASTLE_OFFENCE_HEIGHT)/2, CASTLE_OFFENCE_WIDTH, CASTLE_OFFENCE_HEIGHT);
		}
};

#endif