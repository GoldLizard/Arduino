This program is for fine tuning variables for a robot.
Instead of recompiling every time you want to change a variable, connect this board and adjust values with buttons.
Lets say the variables you want to change are globals in the main .ino file as:
	int speed = 1, var1 = 1, var2 = 1;

In buttons.h, redeclare those variables as external references, as:
	extern int speed, var1, var2;

In buttons.h, edit the variables vector to include text to display and that variable itself. 
	vector<pair<string, int>> variables = {make_pair("SPEEd", speed), 
					       make_pair("vAr1", var1),
					       make_pair("vAr2", var2)};

Left 2 buttons swap between the variables.
Button 3 prints all current values to serial monitor, if connected.
The right buttons are default increment, decrement, double, and half. 

To use this program and the TM1638, include the 3 header files in the main .ino and copy the 4 functions into your loop.
