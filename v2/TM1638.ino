#include <TM1638.h> //github.com/dvarrel/TM1638/blob/main/src/TM1638.cpp
#include "table.h"
#include "text.h"
#include "buttons.h"
using namespace std;

int speed = 1, var1 = 1, var2 = 1;

void setup() {
  Serial.begin(115200);
  tm.reset();
}

void loop() {
  CheckButtonPressed();
  ExecuteButtons();
  UpdateText(variables.at(currentVar).first, to_string(variables.at(currentVar).second));
  DisplayText();
}
