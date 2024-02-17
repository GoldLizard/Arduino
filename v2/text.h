#ifndef TEXT
#define TEXT

#include <string>
using namespace std;

//choose digital pins compatibles with your board
#define STB 21 // Strobe digital pin
#define CLK 20 // clock digital pin
#define DIO 19 // data digital pin
TM1638 tm(CLK,DIO,STB);

vector<uint8_t> text = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
table lookupTable;

void UpdateText(string param){
  text = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   //clear previous text
  for(int i = param.size()-1; i >= 0; i--){     //probably wrong offsets
    text[i+(8-param.size())] = lookupTable.GetHex(param.at(i));  //convert '2' to 0x5B, then place that 0x5B in text[i]
  }
}

void UpdateText(string varName, string varValue){
  text = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   //clear previous text
  for(int i = 0; i < varName.size(); i++){
    text[i] = lookupTable.GetHex(varName.at(i)); //prints varName on the left
  }
  
  for(int i = varValue.size()-1; i >= 0; i--){     //probably wrong offsets
    text[i+(8-varValue.size())] = lookupTable.GetHex(varValue.at(i)); //prints varValue on the right
  }
}

void DisplayText(){
  for (uint8_t i=0;i<sizeof(text);i++){
    tm.displayDig(7-i, text[i]);
  }
}

#endif