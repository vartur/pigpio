#ifndef GPIOMANAGER_H
#define GPIOMANAGER_H

#include <map>
#include "GPIOPin.h"

///\file GPIOManager.h
///\author Vincent Artur

namespace PiGPIO
{
	///\class GPIOManager
	///\brief Manages one or several GPIO pins.
	class GPIOManager
	{
		public:
		
			///\brief Constructor.
			GPIOManager();
			
			///\brief Copy constructor.
			///\param other The GPIOManager to copy into the current one.
			GPIOManager(const GPIOManager& other);
			
			///\brief Move constructor.
			///\param other The GPIOManager to move into the current one.
			GPIOManager(GPIOManager&& other) noexcept;
			
			///\brief Destructor.
			~GPIOManager() noexcept;
			
			///\brief Assignment operator.
			///\param other The GPIOManager from which to copy the data into the current one.
			GPIOManager& operator=(const GPIOManager& other);
			
			///\brief Move assignment operator.
			///\param other The GPIOManager from which to move the data into the current one.
			GPIOManager& operator=(GPIOManager&& other) noexcept;
			
			///\brief Registers a new pin on the manager.
			///\param pinId The ID of the pin to register.
			///\param pinDirection The direction of the pin to register.
			void registerPin(const unsigned int pinId, const PinDirection& pinDirection);
			
			///\brief Unregisters a pin from the manager.
			///\param pinId the ID of the pin to unregister.
			void unregisterPin(const unsigned int pinId);
			
			///\brief Unregisters all pins registered from the manager.
			void unregisterAllPins();
			
			///\brief Sets a pin's value.
			///\param pinId The pin's ID.
			///\param value The new value of the pin.
			void setPinValue(const unsigned int pinId, const PinValue& value);
			
			///\brief Gets a pin's value.
			///\param pinId The pin's ID.
			///\return The pin's value.
			PinValue getPinValue(const unsigned int pinId) const;
			
			///\brief Sets a pin to high for a given amount of time.
			///\param pinId The pin's ID.
			///\param time The amount of time during which the pin will stay high, in milliseconds.
			void blinkPin(const unsigned int pinId, const unsigned int time);
			
		private:
		
			std::map<unsigned int, GPIOPin> m_pins; ///< All registered pins.
				
	};
}

#endif
