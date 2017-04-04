//
//  PlantXperiment_h
//  
//
////

#include "StandardCplusplus.h"
#include <vector>
#include <list>
#ifndef PlantXperiment_h
#define PlantXperiment_h
#endif /* PlantXperiment_h */

class PlantXperiment{

public:    
	int  whichWall(int Signature);
	void findResources();
	void pixyCheck();
	int  bwallCount();
	void Pixy_Align();
	void Pixy_finetune();
	void get_coordinates();
	void complexMove(int goalX, int goalY, float orientation);
	void translatePolar(float azimuth, float destDistCm);
	void translateCart(int goalX, int goalY);
	void wheel_speeds(float tot_spd, float ang);
	void Relative_ang(float *ptr, float ang);
	void boxUpdate(float dirc, float dur, float spd);
	void timerReset();
	void timerRead();
	void timerTest();
	void motospd(int sp1,int sp2,int sp3);
private:
	int blue=1;     
	int red=2;
	int green=3;
	int yellow=4;
	int brown=5;
	int purple=6;
	int orange=7;
	int pink=8;
	int bluegreen=13;
	int greenred=32;
	int redyellow=24;
	int yellowblue=41;
	std::list<int> dimensions;
	std::vector<char> resourceNames;
	//resourceNames.push_back('W');
	//resourceNames.push_back('C');
	//resourceNames.push_back('I');
	int wallColors[4]={bluegreen,greenred,redyellow,yellowblue};
	char wallColorNames[4]={'bluegreen','greenred','redyellow','yellowblue'};
	int cornerColors[4] = {blue, red ,green, yellow}; //change later to signatures
	int roboColors= brown; //color markers on robots
	int resourceColors[3]={purple, orange, pink};//water, CO2, light
	int CurrentColor;
	int startCorner=0;
	int endCorner=0;
	int wallCounter=1;
	//pixySignatures[8]={markerColor, counterColors[0], counterColors[1], counterColors[2], counterColors[3], roboColors[1],roboColors[2], roboColors[3],startCorner,endCorner
};