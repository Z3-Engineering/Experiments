//
//  PlantXperiment.cpp
//  
//
//  Created by Shai Sabaroche on 2/6/17.
//
//

#include "PlantXperiment.hpp"
#include "SPI.h"    //hi
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

