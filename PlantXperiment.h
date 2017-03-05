//
//  PlantXperiment_h
//  
//
////

//#include "StandardCplusplus.h"
//#include <vector>
//#include <list>
#include <NewPing.h>
#include <TimeLib.h>
#ifndef PlantXperiment_h
#define PlantXperiment_h
#endif /* PlantXperiment_h */

class PlantXperiment{

public:    
	int  whichWall(int Signature);
	void findResources();
	void pixyCheck();
	void wallCount();
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
    void sonarInfoDisplay();
    void speedInfoDisplay();
    void motospd();
    bool anyCollision(int distance_cm);
    void rotate(float deg);
    
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
    int dimensions[2];
    char resourceNames[3]={'W','C','I'};
	int wallColors[4]={bluegreen,greenred,redyellow,yellowblue};
	char wallColorNames[4]={'bluegreen','greenred','redyellow','yellowblue'};
	int cornerColors[4] = {blue, red ,green, yellow}; //change later to signatures
	int roboColors= brown; //color markers on robots
	int resourceColors[3]={purple, orange, pink};//water, CO2, light
	int CurrentColor;
	int startCorner=0;
	int endCorner=0;
	int wallCounter=1;
    int wheel_pwm[3] = {5, 6, 7}; //pins on motor drive to control speed
    int wheel_direction[3] = {2, 3, 4}; //pins to control wheel direction
    double wheel_angles[3] = {270, 30, 150}; //wheel angles are defined
    double wheel_speed[3]; //speed of each wheel is stored in this array
    double max_speed = 70; //maximum speed
    double max_speedR = 40; //rotate speed
    double cm[4]; //sensed distance of sonar sensor : 2 represents array(2 sonar sensors)
    int trigger[4] = {30, 32, 34, 36}; //trigger pins assignment  (sends)
    int echo[4] = {31, 33, 35, 37}; //echo pins (receives)
    int colliDistance_cm = 25; //distances to define collision in cm/in
    int colliDistance_in = 12;
    int rotation_update_delay = 10;
    time_t timerTime; //Time after Arduino is powered on that timing starts
    time_t timerReading; //Time since timing starts
    int boxLocation [2] = {0,0}; //Location of the robot in the room, represented as grid, with origin and back left corner.
    float Compass = 0; //Angle the robot is facing, relative to the room with 0 deg straight back into room, assumes robot is facing 0 deg.
    const float velocity = 200; //velocity in cm/s. !!!!!!.!!!!!NEED TO CALIBRATE!!!!!!!!!!!
    float boxSize = 50; //Size of the gridsquares that make up the room
    void updateSonar();
    NewPing sonar[4] ={
        NewPing(trigger[0], echo[0], 500), //500 represents type of sensor
        NewPing(trigger[1], echo[1], 500),
        NewPing(trigger[2], echo[2], 500),
        NewPing(trigger[3], echo[3], 500)
    };
    
	//pixySignatures[8]={markerColor, counterColors[0], counterColors[1], counterColors[2], counterColors[3], roboColors[1],roboColors[2], roboColors[3],startCorner,endCorner
};
