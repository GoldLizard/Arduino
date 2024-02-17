TM1638 is an 8 character hex display with buttons
    Library at github.com/dvarrel/TM1638/blob/main/src/TM1638.cpp
    The main problem is that button reads will return true for every loop it's pressed.
    CheckButtonPressed() updates the vector risingEdges so that buttons only execute code for 1 loop, then ignore button presses until a falling edge.
    UpdateText(string param) uses a hex lookup table to print any string 0<size<=8, aligned on the right side of the hex display.
