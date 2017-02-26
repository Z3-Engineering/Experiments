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
int bluegreen=13;
int redbrown=25;
int yellowred=42;
int bluered=12;
vector<char> resourceNames;
resourceNames.push_back('W');
resourceNames.push_back('C');
resourceNames.push_back('I');
static const int cornerColors[4] = {blue, red ,green, yellow}; //change later to signatures
static const int roboColors= brown; //color markers on robots
static const int resourceColors[3]={bluegreen, redbrown, yellowred};//water, CO2, light
static const int markerColor = bluered; //wall counter colors
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
        Pixy_Align();
        wheel_speed(40,0);
        Pixy_Align();
        
    }
    }
        else{
        Serial.println("Collision will occur if movement is continued");
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

//check if read block is contained in the blcok array
