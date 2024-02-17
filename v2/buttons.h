#ifndef BUTTONS
#define BUTTONS
extern int speed, var1, var2;
vector<pair<string, int>> variables = {make_pair("SPEEd", speed), make_pair("vAr1", var1), make_pair("vAr2", var2)}; //edit to your variables

int currentVar = 0;

vector<button_t> allButtons = {S1, S2, S3, S4, S5, S6, S7, S8};
vector<bool> oldStates      = {0,  0,  0,  0,  0,  0,  0,  0}; //for comparing old/new states to detect rising edges
vector<bool> risingEdges    = {0,  0,  0,  0,  0,  0,  0,  0}; //any rising edges only last for 1 loop

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

void ExecuteButtons(){
  int& varValue = variables.at(currentVar).second;
  if(risingEdges.at(7)){ //button 8
    varValue++;
  }
  if(risingEdges.at(6)){ //button 7
    varValue--;
  }
  if(risingEdges.at(5)){ //button 6
    varValue *= 2;
  }
  if(risingEdges.at(4)){ //button 5
    varValue /= 2;
  }
  if(risingEdges.at(3)){ //button 4
    varValue = 0;
  }

  if(risingEdges.at(2)){ //button 3, prints all values to serial monitor

    //vector<pair<string, int>> variables
    for(pair<string, int> eachPair : variables){
      //string temp = eachPair.first;
      Serial.write(eachPair.first.c_str());
      Serial.write('\t');
      Serial.write(to_string(eachPair.second).c_str());
      Serial.write('\n');
    }
    Serial.write('\n');
  }

  if(risingEdges.at(1)){ //button 2, changing variable to next var
    if(currentVar == variables.size()-1){ //if trying to go outside vector's range, loop back around to the beginning
      currentVar = 0;
    }
    else{
      currentVar++;
    }
  }

  if(risingEdges.at(0)){ //button 1, changing variable to previous var
    if(currentVar == 0){
      currentVar = variables.size()-1; //if trying to go below position 0, loop back around to other end
    }
    else{
      currentVar--;
    }
  }
}

#endif