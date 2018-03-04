#include "GPIOManager.h"
#include <iostream>

///\file main.cpp
///\author Vincent Artur


///\brief Main method of PiGPIO
///\param argc The number of arguments.
///\param argv The array of arguments.
int main(int argc, const char* argv[])
{
	using namespace std;
	using namespace PiGPIO;
	
	GPIOManager manager = GPIOManager();
	
	manager.registerPin(21, Output);
	
	manager.blinkPin(21, 3000);
	
	
	return 0;
}
