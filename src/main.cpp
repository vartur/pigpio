#include "GPIOManager.h"
#include <iostream>
#include <string>

///\file main.cpp
///\author Vincent Artur


///\brief Main method of PiGPIO
///\param argc The number of arguments.
///\param argv The array of arguments.
int main(int argc, const char* argv[])
{
	using namespace std;
	using namespace PiGPIO;
	
	unsigned int pinId = 0;
	PinValue val = Low;
	unsigned int time = 0;
	
	for(int argIndex = 0; argIndex < argc; ++argIndex)
	{
		string param = argv[argIndex];
		if(param.at(0) == '-')
		{
			switch(param.at(1))
			{
				case 'p':
					pinId = stoi(argv[argIndex + 1]);
					break;
					
				case 'v':
					val = (stoi(argv[argIndex + 1]) == 0) ? Low : High;
					break;
					
				case 't':
					time = stoi(argv[argIndex + 1]);
			}
			
			++argIndex;
		}
	}
	
	GPIOManager manager = GPIOManager();
	manager.registerPin(pinId, Output);
	
	if(time == 0)
	{
		manager.setPinValue(pinId, val);
	}
	else
	{
		manager.blinkPin(pinId, time);
	}
	
	
	return 0;
}
