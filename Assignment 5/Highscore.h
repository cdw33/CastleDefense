#ifndef Highscore_H
#define Highscore_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct entree {
	entree(string name, int wave, int score) {
		this->name = name;
		this->wave = wave;
		this->score = score;
	}
	entree(string data) {
		this->name = data.substr(0, data.find("."));
		this->wave = atoi((data.substr(data.find(".")+1, data.find("..") - data.find(".")-1)).c_str());
		this->score = atoi((data.substr(data.find("..")+2, data.size() - data.find("..")-2)).c_str());
	}
	bool operator < (const entree& n) const {
		if (this->wave != n.wave) {
			return (this->wave < n.wave);
		} else {
			return (this->score < n.score);
		}
	}

	string name;
	int wave, score;
};

class Highscore {
	/*
	/ If you adjust the HS_CAP constant, you will need to go to into highscores.txt, found
	/ in the defult directory, and add up to the new defualt number of lines. A defult
	/ line being "---.0..0". If you lower the HS_CAP, the program will still function
	/ properly, but with less highscore entrees.
	*/

	private:
		static const int HS_CAP = 8; 
		string path;
		fstream fs;
		static vector<entree> highscoreList;

	public:
		Highscore();

		void clearFile();
		void rewrite();
		void getUserName();
		bool checkIfHighscore(int, int);
		void insertRecord(string, int, int);
		const int getCap();
		vector<entree> getHighscores();
};

/* The following line is needed in order to use non-constant static data types in classes */
vector<entree> Highscore::highscoreList;

//*************************************************
// constructor
//*************************************************
Highscore::Highscore() {
	this->path = "Highscores.txt";
	string data;

	fs.open(path, fstream::in | fstream::app);

	/* Read information from file */
	if (highscoreList.empty()) { /* Because highscoreList is static, if another object of type Highscore was created highscoreList would be unwantedly modified */
		for (int i = 0; i < HS_CAP; ++i) {
			getline(fs, data);
			highscoreList.push_back(entree(data)); 
		}
	}

	fs.close();
}

//*************************************************
// clearFile
//*************************************************
void Highscore::clearFile() {
	fs.open(path, fstream::out | fstream::trunc);
	fs.close();
}

//*************************************************
// rewrite
//*************************************************
void Highscore::rewrite() {
	string newData;
	for(int i = 0; i < HS_CAP; ++i) {
		newData += highscoreList[i].name + "." + to_string(highscoreList[i].wave) + ".." + to_string(highscoreList[i].score) + "\n";
	}

	fs.open(path, fstream::out);
	fs << newData.c_str();
	fs.close();
}

//*************************************************
// checkIfHighscore
//*************************************************
bool Highscore::checkIfHighscore(int wave, int score) {
	entree dataCheck("TEST DATA", wave, score);
	
	for (int i = 0; i < HS_CAP && score != 0; ++i) {
		if (highscoreList[i] < dataCheck) {
			return true;
		}
	}

	return false;
}

//*************************************************
// insertRecord
//*************************************************
void Highscore::insertRecord(string name, int wave, int score) {
	entree newData(name, wave, score);

	highscoreList.push_back(newData);
	stable_sort(highscoreList.rbegin(), highscoreList.rend());
	highscoreList.erase(highscoreList.begin() + highscoreList.size() - 1);

	rewrite();
}

//*************************************************
// getCap
//*************************************************
const int Highscore::getCap() {
	return HS_CAP;
}

//*************************************************
// getHighscore
//*************************************************
vector<entree> Highscore::getHighscores() {
	return highscoreList;
}

#endif