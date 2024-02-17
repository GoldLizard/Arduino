#include <TM1638.h> //github.com/dvarrel/TM1638/blob/main/src/TM1638.cpp
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct table{ //all because Arduino uses map for a class, so I cant just map<char, uint8_t>
    vector<pair<char, uint8_t>> map = {make_pair('0', 0x3F), make_pair('1', 0x06), make_pair('2', 0x5B), make_pair('3',0x4F), make_pair('4', 0x66),
                                       make_pair('5', 0x6D), make_pair('6', 0x7D), make_pair('7', 0x07), make_pair('8', 0x7F), make_pair('9', 0x6F),
                                       make_pair('-', 0x40)};
    uint8_t GetHex(char param){ //tableName.GetHex('2'); will loop through vector<pair<>>
      for(pair<char, uint8_t> eachPair : map){
        if(eachPair.first == param){ //once it finds make_pair('2', 0x5B), it returns 0x5B
          return eachPair.second;
        }
      }
      return 0xFF; //if character doesnt exist in lookup table, return 8 as an error
    }
};



//choose digital pins compatibles with your board
#define STB 21 // Strobe digital pin
#define CLK 20 // clock digital pin
#define DIO 19 // data digital pin

TM1638 tm(CLK,DIO,STB);
vector<uint8_t> text = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
table lookupTable;
int counter;
bool button;

void DisplayText();
void UpdateText(string param);
void CheckButtonPressed();
vector<button_t> allButtons = {S1, S2, S3, S4, S5, S6, S7, S8};
vector<bool> oldStates      = {0,  0,  0,  0,  0,  0,  0,  0}; //for comparing old/new states to detect rising edges
vector<bool> risingEdges    = {0,  0,  0,  0,  0,  0,  0,  0}; //any rising edges only last for 1 loop

void setup() {
  Serial.begin(115200);
  tm.reset();
  tm.test();
  counter = 1;
}

void loop() {
  
  CheckButtonPressed();
  if(risingEdges.at(7)){ //button 8
    counter++;
  }
  if(risingEdges.at(6)){ //button 7
    counter--;
  }
  if(risingEdges.at(5)){ //button 6
    counter *= 2;
  }
  if(risingEdges.at(4)){ //button 5
    counter /= 2;
  }
  if(risingEdges.at(3)){ //button 4
    counter = 0;
  }

  DisplayText();

  //string input is 8 characters long
  UpdateText(to_string(counter));
}



void UpdateText(string param){ //Ex. counter == 16 would load text[] with 0000 0016
  text = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   //clear previous text
  for(int i = param.size()-1; i >= 0; i--){     //probably wrong offsets
    text[i+(8-param.size())] = lookupTable.GetHex(param.at(i));  //convert '2' to 0x5B, then place that 0x5B in text[i]
  }
}

void DisplayText(){
  for (uint8_t i=0;i<sizeof(text);i++){
    tm.displayDig(7-i, text[i]);
  }
}

void CheckButtonPressed(){
  for(int i = 0; i <= 7; i++){ //check for rising edges by comparing current and previous loop
    if(tm.getButton(allButtons.at(i)) && !oldStates.at(i)){ //if rising edge, remember old state and flag rising edge
      oldStates.at(i) = true;
      risingEdges.at(i) = true;
    }
    else if(tm.getButton(allButtons.at(i)) && oldStates.at(i)){ ///if the button is still pressed next loop, set rising edge to 0
      risingEdges.at(i) = false;
    }
    else if(!tm.getButton(allButtons.at(i))){ //remember old state if button isnt pressed
      oldStates.at(i) = false;
    }
  }
}
