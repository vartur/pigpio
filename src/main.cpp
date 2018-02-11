#include "GPIOPin.h"
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
	
	GPIOPin test(14);
	test.setExportState(Exported);
	
	test.setDirection(Output);
	
	cout<< "Pin 14 value: " << (test.getValue() == High ? "1" : "0") <<endl;
	cout << "Setting value to 1 on pin 14..." <<endl;
	test.setValue(High);
	cout<< "Pin 14 value: " << (test.getValue() == High ? "1" : "0") <<endl;
	
	
	test.setExportState(Unexported);
	return 0;
}
