#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <Pixy.h>
#include <SPI.h>


using namespace std;

namespace std {
  ohserialstream cout(Serial);
}

Pixy pixy;
uint16_t blocks;
int bluegreen = 12;
int counter;
static int i=0;
int j;

void counterbasic(){
  blocks=pixy.getBlocks();
  if (blocks){
    i++;
    if (i%75==0){
      for (j=0; j<blocks; j++){
        if (pixy.blocks[j].signature==10){
          counter+=1;
          cout<<"counter: "<<counter<<endl;
        }
      }
    }
  }
}

void printer(int startnum, int endnum){
  int octo;
  int deco;
  cout<<"int\t\toctal"<<endl;
  for (int i=startnum;i<endnum;i++){
    octo=toOctalFromDecimal(i);
    cout<<i<<"\t\t"<<octo<<endl;
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixy.init();

  //printer(0,35);
}

void loop() {
   counterbasic();

  // put your main code here, to run repeatedly:

}

string ToString(int val)
{
    basic_stringstream<char> stream;
    stream << val;
    return stream.str();
}


int toOctalFromDecimal (int num) {
    basic_ostringstream<char> o;
    o << std::oct << num;
    return atoi((o.str()).c_str());
}

int toDecimalFromOctal (int num) {
    int rem, i = 1, octo = 0;
    while (num != 0)
    {
        rem = num % 8;
        num /= 8;
        octo += rem * i;
        i *= 10;
    }
    return octalNumber;
}




