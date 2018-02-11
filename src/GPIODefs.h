#ifndef GPIODEFS_H
#define GPIODEFS_H

///\file GPIODefs.h
///\author Vincent Artur

///\namespace PiGPIO
///\brief Objects related to the Raspberry Pi GPIO pin handling.
namespace PiGPIO
{
	///\brief GPIO pin export states.
	enum PinExportState
	{
		Unexported,
		Exported
	};
	
	///\brief GPIO pin directions.
	enum PinDirection
	{
		Input,
		Output
	};
	
	///\brief GPIO pin values.
	enum PinValue
	{
		Low,
		High
	};
}

#endif
