#ifndef GPIOPIN_H
#define GPIOPIN_H

#include "GPIODefs.h"
#include <string>

///\file GPIOPin.h
///\author Vincent Artur

namespace PiGPIO
{			
	///\class GPIOPin
	///\brief Object controlling a Raspberry Pi GPIO pin.
	class GPIOPin
	{
		public:
		
			///\brief Constructor.
			///\param id The ID of the pin.
			GPIOPin(unsigned int id);
			
			///\brief Copy constructor.
			///\param other The GPIOPin to copy into the current one.
			GPIOPin(const GPIOPin& other);
			
			///\brief Move constructor.
			///\param other The GPIOPin to move into the current one.
			GPIOPin(GPIOPin&& other) noexcept;
			
			///\brief Destructor.
			~GPIOPin() noexcept;
			
			///\brief Assignment operator.
			///\param other The GPIOPin from which to copy the data into the current one.
			GPIOPin& operator=(const GPIOPin& other);
			
			///\brief Move assignment operator.
			///\param other The GPIOPin from which to move the data into the current one.
			GPIOPin& operator=(GPIOPin&& other) noexcept;
			
			///\brief Gets the ID of the GPIO pin.
			unsigned int getID() const;
			
			///\brief Gets the export state of the pin.
			PinExportState getExportState() const;
		
			///\brief Sets the pin's export state.
			///\param state The new export state of the pin.
			void setExportState(const PinExportState& state);
			
			///\brief Gets the direction of the pin.
			PinDirection getDirection() const;
			
			///\brief Sets the direction of the pin.
			///\param direction The new direction of the pin.
			void setDirection(const PinDirection& direction);
			
			///\brief Gets the value of the pin.
			PinValue getValue() const;
			
			///\brief Sets the value of the pin.
			///\param value The new value of the pin.
			void setValue(const PinValue& value);
			
		private:
		
			unsigned int m_id; ///< The ID of the pin.
			
			PinExportState m_state; ///< The export state of the pin.
			
			PinDirection m_direction; ///< The direction of the pin.
			
			PinValue m_value; ///< The current value of the pin.		
			
			void writeToFile(const std::string& path, const auto& value) const;
			
	};
}

#endif
