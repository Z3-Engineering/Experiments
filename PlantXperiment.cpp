//
//  PlantXperiment.cpp
//  
//
//  Created by Shai Sabaroche on 2/6/17.
//
//

#include "PlantXperiment.hpp"
#include "SPI.h"
#include "Pixy.h"

Pixy pixy; //create global instance of Pixy

//intialisation of a crucial variables with epononymous purposes
static const int cornerColors[4] = {blue, red ,green, yellow}; //change later to signatures
static const int roboColors[3]= {purple, brown, orange};
static const int markerColor = bluered;
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

//check if read block is contained in the blcok array

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
            motospd(20,20,20);                                          //rotate
            delay(rotation_update_delay);
            pixyCheck();                                     //run through pixyCheck again to see if corner color
        }
        i++;
    }
}
//move left, counting markers while moving

int wallCount(){
    moveLeft();
    motospd(0,0,0); //change later***********************************************************************
    if(pixy.blocks[0].signature==markerColor)//Pixy read the corner at which it is intially aligned
    {
        wallCounter+=1;
    }
}   //within wallCount or moveLeft, should include stop movement when sees corner color

//turn 90 degrees and move left routine again**************************************************************




void locateResources(){

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
