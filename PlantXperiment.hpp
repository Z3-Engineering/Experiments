//
//  PlantXperiment.hpp
//  
//
//  Created by Shai Sabaroche on 2/6/17.
//
//
#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <vector>
//#include <Math.h>
#include <iostream>
#include <stdio.h>

#ifndef PlantXperiment_hpp
#define PlantXperiment_hpp
#endif /* PlantXperiment_hpp */

using namespace std;

Pixy pixy; //create global instance of Pixy

//intialisation of a crucial variables with epononymous purposes
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

vector<char> resourceNames;
resourceNames.push_back('W');
resourceNames.push_back('C');
resourceNames.push_back('I');
static const int wallColors[4]={bluegreen,greenred,redyellow,yellowblue};
static const int cornerColors[4] = {blue, red ,green, yellow}; //change later to signatures
static const int roboColors= brown; //color markers on robots
static const int resourceColors[3]={purple, orange, pink};//water, CO2, light

int startCorner=0;
int endCorner=0;
int wallCounter=1;
const char colorCombo [4][4]=
{
    {'BY','RY','GY', '0'},
    {'BG','RG', '0','YG'},
    {'BR', '0','GR','YR'},
    { '0','RB','GB','YB'}
}

pixySignatures[8]={markerColor, counterColors[0], counterColors[1], counterColors[2], counterColors[3], roboColors[1],roboColors[2], roboColors[3],startCorner,endCorner};

    


void findResources(){
    Serial.println("Looking for resources...");
    if (anyCollision(10)==false){
    motospd(20,20,20);
    int blocks=pixy.getBlocks(17);
    if (pixy.blocks[0].signature==bluegreen||redbrown||yellowred){
        int temp=pixy.block[0].signature;
        resourceNames
        Serial.println("Found a Resource");
        wheel_speed(40,0);
        if(anyCollision(10)==true){
        motospd(0,0,0);
        }
        Pixy_Align();
        rotate(180);
        int blocks=pixy.getBlocks(17);
        if (pixy.block[0].signature==markerColor)
        wheel_speed(40,0);
        if(anyCollision(10)==true){
            motospd(0,0,0);
        }
        Pixy_Align();
        wheel_speed(40,90);
        wallCount();
    }
    }
        else{
        Serial.println("Collision will occur if movement is continued");
        }
}
void pixyCheck(){
int i=0;
    while (i<4){
        if(pixy.blocks[0].signature==cornerColors[i]){      //loop through to check if color seen is corner color
            Pixy_Align();   //if it is a corner color, align with it and break
            startCorner=pixy.blocks[0].signature;
            break;
        }
        else if (pixy.blocks[0].signature!=cornerColors[i]){            //if its not a corner color
            Serial.println("Searching for Corner Colour \n Rotating CounterClockwise \n");
            motospd(40,40,40);                                          //rotate
            delay(rotation_update_delay);
            pixyCheck();                                     //run through pixyCheck again to see if corner color
        }
        i++;
    }
}

int wallCount(){
    if(anyCollision==false){
        wheel_speeds(40,90);
        if (pixy.blocks[0].signature==markerColor){//Pixy read the corner to which it is intially aligned
            wallCounter+=1;
        }
        else if (pixy.blocks[0].signature==cornerColors[0]||cornerColors[1]||cornerColors[2]||cornerColors[3]){
            motospeed(0,0,0);
            pixyCheck();
        }
        else {
            ;
        }
    }
    else{
        motospeed(0,0,0);
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(1000);                       // wait for a second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(1000);
    }
}
    
void Pixy_Align()
{
    Serial.println("-------------------------------------------------");
    Serial.println("-------------------------------------------------");
    get_coordinates();
    int rotation_update_delay = 10;
    int tolerance = 7;
    int blocks = pixy.getBlocks(17);
    if (pixy.blocks[0].x < (160 - tolerance) )
    {
        Serial.println("Rotating CoutnerClockwise...");
        motospd(20, 20, 20);
        delay(rotation_update_delay);
        Pixy_Align();
    }
    else if (pixy.blocks[0].x > (160 + tolerance) )
    {
        Serial.println("Rotating Clockwise...");
        motospd(-20, -20, -20);
        delay(rotation_update_delay);
        Pixy_Align();
    }
    else {
        //    Pixy_finetune();
        Serial.println("pixy has been aligned");
        motospd(0, 0, 0);
        return;
    }
}

void Pixy_finetune() { //taken for testing purposes from @Navigation-and-Pathfinding-codes (will return)
    Serial.println("------------||FINE TUNE IN PROGRESS||-----------");
    Serial.println("-------------------------------------------------");
    get_coordinates();
    int rotation_update_delay = 10;
    int tolerance = 5;
    int spd = 10;
    int blocks = pixy.getBlocks(17);
    if (pixy.blocks[0].x < (160 - tolerance) )
    {
        Serial.println("Rotating CoutnerClockwise...");
        motospd(spd, spd, spd);
        delay(rotation_update_delay);
        Pixy_finetune();
    }
    else if (pixy.blocks[0].x > (160 + tolerance) )
    {
        Serial.println("Rotating Clockwise...");
        motospd(-1 * spd, -1 * spd, -1 * spd);
        delay(rotation_update_delay);
        Pixy_finetune();
    }
    else {
        Serial.println("pixy has been aligned");
        motospd(0, 0, 0);
        return;
    }  
}

void get_coordinates() //see Pixy_align
{
    
    int blocks = pixy.getBlocks(17);
    for (int k = 0; k < blocks; k++) {
        if (pixy.blocks[k].signature == 1) {
            Serial.print("The X coordinate is:");
            Serial.print(pixy.blocks[k].x);
            Serial.println();
            Serial.print("The Y coordinate is:");
            Serial.print(pixy.blocks[k].y);
            Serial.println();
            
        }
    }  
}

void complexMove(int goalX, int goalY, float orientation){ //Robot winds up in a specified grid, facing a specified direction, measured in grid squares and degrees.  
  translateCart(goalX, goalY); //Robot moves to a specified location
  float dTheta = orientation - Compass;
  Compass = orientation; 
  rotate(dTheta); //Robot rotates to face a specified direction
}

void translatePolar(float azimuth, float destDistCm){ //Robot moves a specified distance and direction. 
  timerReset(); //Reset the timer. 
  float duration = 1000 * (destDistCm / velocity); //time needed to travel in ms.
  Serial.print("The Robot Will Now Move for ");
  Serial.print(duration/1000);
  Serial.println("Seconds");
  wheel_speeds(40,azimuth); //speed in "motospd units"
  while (timerReading < duration){
  boxUpdate(azimuth,timerReading,velocity);
  timerRead(); 
  Serial.print("The Robot is in Box: ");
  Serial.print(boxLocation[1]  );
  Serial.println(boxLocation[2]  );
  delay(10);
  }
  Serial.print("The Robot has Stopped");
  motospd(0,0,0); //Stop the robot
}

void translateCart(int goalX, int goalY){ //Determines the distance and direction the robot needs to move to reach a specified grid (X,Y);
  int destBox[2] = {goalX, goalY};
  int deltaBox[2];//How many boxes right/left, up/down the robot needs to move to reach desired location.
  float deltaCm[2]; //Distance in cm that the robot needs to move up/down/left/right. 
  for (int i = 0; i <3; ++i) //Math
  {
    deltaBox[i] = destBox[i]-boxLocation[i];
    deltaCm[i] = boxSize*deltaBox[i];
  }
  float destDistCm = sqrt(pow(deltaCm[1],2)+pow(deltaCm[2],2));
  float azimuth = atan2(deltaCm[2],deltaCm[1]);
  translatePolar(azimuth, destDistCm); //Once the robot determines the distance and 
}

void rotate(float deg){ //input the angle you want to face, relative to the direction the robot is currently facing. 
  
  while (deg >= 360){ //puts angle in correct range
  deg = deg - 360;
  }
  
  while (deg <= -360){ //puts angle in correct range
  deg = deg + 360;
  }
  
  if (deg > 0 && deg <=180){
    motospd(30,30,30);
  }
  else if (deg <= -180 && deg >-360){
    deg = 360 + deg;
    motospd(30,30,30);
  }
  else if(deg >180 && deg < 360){
    deg = 360-deg; 
    motospd(-30,-30,-30);
  }
  else if (deg <0 && deg > -180){
    deg = -1*deg;
    motospd(-30,-30,-30);
  }
  else if (deg = 0) {
    motospd(0,0,0);
  }
  float runtime = 1000*(0.0276*deg - 0.2101); //time it takes to rotate in milliseconds, based on calibration data.
  unsigned long longTime = (unsigned long) runtime;
  delay(longTime);
  motospd(0,0,0);
  delay(100); //extra delay to avoid errors. 
  
}

void wheel_speeds(float tot_spd, float ang){
  float results[4];
  Relative_ang(results,ang);

  float Motor_2 = ((((-1/sqrt(3))*tan((results[0]/180)*M_PI))-1)*(tot_spd/(1/cos((results[0]/180)*M_PI))));
  float Motor_1 = -1*((((1/sqrt(3))*tan((results[0]/180)*M_PI))-1)*(tot_spd/(1/cos((results[0]/180)*M_PI))));  

  float Motor_Comp = .0018*pow(results[0],3) - 0.1019*pow(results[0],2) + 2.446*results[0] + 0.8571;

  int a = abs(results[1])-1;
  int b = abs(results[2])-1;
  int c = abs(results[3])-1;

 float motors[3];
 motors[a]= (results[1]/(abs(results[1]))) * Motor_1;
 motors[b]= Motor_2;
 motors[c]= Motor_Comp;
}

void Relative_ang(float *ptr, float ang){
//float a,b,c,d;
// float new_config[4]={0,0,0,0};
// float *ptr[4];
 float new_ang;
    if(ang >= 0 && ang<= 30){
      new_ang = ang;
     //new_config = {new_ang, 3,2,1};
      ptr[0] = new_ang;
      ptr[1] = 3;
      ptr[2] = 2;
      ptr[3] = 1;      
    }
     else if(ang >= 330 && ang<= 360){
      new_ang = ang;
     //new_config = {new_ang, 3,2,1};
      ptr[0] = new_ang - 360;
      ptr[1] = 3;
      ptr[2] = 2;
      ptr[3] = 1;      
    }
    else if (ang > 30 && ang <= 90){
     new_ang = ang - 60;
    //new_config = {new_ang, -2,-1,3};
     ptr[0] = new_ang;
      ptr[1] = -2;
      ptr[2] = -1;
      ptr[3] = 3;
    }
    else if (ang > 90 && ang <= 150){
      new_ang = ang - 120;
     //new_config = {new_ang, 3,1,2};
      ptr[0] = new_ang;
      ptr[1] = 3;
      ptr[2] = 1;
      ptr[3] = 2;
    }
    else if(ang > 150 && ang<= 210){
      new_ang = ang - 180;
     // new_config = {new_ang, -3,-2,1};
      ptr[0] = new_ang;
      ptr[1] = -3;
      ptr[2] = -2;
      ptr[3] = 1;
    }
    else if(ang > 210 && ang<= 270){
      new_ang = ang - 240;
     // new_config = {new_ang, 2,1,3};
      ptr[0] = new_ang;
      ptr[1] = 2;
      ptr[2] = 1;
      ptr[3] = 3;
    }
    else if(ang > 270 && ang< 330){
      new_ang = ang - 300;
     // new_config = {new_ang, -3,-1,2};
      ptr[0] = new_ang;
      ptr[1] = -3;
      ptr[2] = -1;
      ptr[3] = 2;
    }
 //return 0;
}
void boxUpdate(float dirc, float dur, float spd){ //Take input direction, time, and speed of robot. Direction taken from some other function, time, from timer, and spd assumed to be absolute. 
      boxLocation [1] = (int) (spd*dur*10*cos(dirc))/boxSize;
      boxLocation [2] = (int) (spd*dur*10*sin(dirc))/boxSize;    
    }
  
//Timing Functions//
void timerReset(){
    timerTime = millis();   
    }

void timerRead(){
  timerReading = millis()-timerTime;
}
    
void timerTest() {
  timerReset();
  Serial.println("Start Exercise");
  delay(1000);
  for (int i=0; i<10; i++){
    timerRead();
  Serial.print("The Measured Time From Exercise Start is: ");
  Serial.print(timerReading);
  Serial.println("ms");
  Serial.print("The abssolute time is ");
  Serial.print(millis());
  Serial.println("ms");
  Serial.println("--------------------------------------------------------------------------");
  delay(1000);
  }
  Serial.println("Exercise End");
  delay(5000);
  }
//Timing Functions//
    
void motospd(int sp1,int sp2,int sp3){
 if(sp1>0){
  digitalWrite(wheel_direction[0],HIGH);
  }else{
    digitalWrite(wheel_direction[0],LOW);
  }
  if(sp2>0){
    digitalWrite(wheel_direction[1],HIGH);
  }else{
    digitalWrite(wheel_direction[1],LOW);
  }
  if(sp3>0){
    digitalWrite(wheel_direction[2],HIGH);
  }else{
    digitalWrite(wheel_direction[2],LOW);
  }
  analogWrite(wheel_pwm[0],abs(sp1));
  analogWrite(wheel_pwm[1],abs(sp2));
 analogWrite(wheel_pwm[2],abs(sp3));
}
