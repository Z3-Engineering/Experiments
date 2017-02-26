//
//  PlantXperiment.hpp
//  
//
//  Created by Shai Sabaroche on 2/6/17.
//
//

#ifndef PlantXperiment_hpp
#define PlantXperiment_hpp

#include <stdio.h>

#endif /* PlantXperiment_hpp */
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
    wheel_speeds(40,90);
    if (pixy.blocks[0].signature==markerColor){//Pixy read the corner at which it is intially aligned
        wallCounter+=1;
    }
    else if (pixy.blocks[0].signature==cornerColors[0]||cornerColors[1]||cornerColors[2]||cornerColors[3]){
        motospeed(0,0,0);
        pixyCheck();
    }
    else {
        Serial.println("Error detected, no color found; I dont know what to do...")
        if (anyCollision(10)){
            motospeed(0,0,0);
            
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



