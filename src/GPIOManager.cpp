#include "GPIOManager.h"
#include <chrono>
#include <iostream>

using namespace PiGPIO;

GPIOManager::GPIOManager()
{
}

GPIOManager::GPIOManager(const GPIOManager& other)
:	m_pins(other.m_pins)
{
}

GPIOManager::GPIOManager(GPIOManager&& other) noexcept
:	m_pins(other.m_pins)
{
}

GPIOManager::~GPIOManager() noexcept
{
	unregisterAllPins();
}

GPIOManager& GPIOManager::operator=(const GPIOManager& other)
{
	GPIOManager tmp = GPIOManager(other);
	*this = std::move(tmp);
	return *this;
}

GPIOManager& GPIOManager::operator=(GPIOManager&& other) noexcept
{
	if(this == &other)
	{
		return *this;
	}
	
	m_pins = other.m_pins;
	
	return *this;
}


void GPIOManager::registerPin(const unsigned int pinId, const PinDirection& pinDirection)
{
	GPIOPin newPin(pinId);
	newPin.setExportState(Exported);
	newPin.setDirection(pinDirection);
	
	m_pins.insert(std::pair<unsigned int, GPIOPin>(pinId, newPin));
}

void GPIOManager::unregisterPin(const unsigned int pinId)
{
	auto pinPosition = m_pins.find(pinId);
	if(pinPosition == m_pins.end())
	{
		std::cerr << "Cannot unregister pin '" << pinId << "', this pin has not been registered!" << std::endl;
		return;
	}
	
	pinPosition->second.setExportState(Unexported);
	m_pins.erase(pinPosition);
}

void GPIOManager::unregisterAllPins()
{
	for(auto pinPosition = m_pins.begin(); pinPosition != m_pins.end(); ++pinPosition)
	{
		const unsigned int pinId = pinPosition->first;
		unregisterPin(pinId);
	}
}
			

void GPIOManager::setPinValue(const unsigned int pinId, const PinValue& value)
{
	auto pinPosition = m_pins.find(pinId);
	if(pinPosition == m_pins.end())
	{
		std::cerr << "Cannot set value on pin '" << pinId << "', this pin has not been registered!" << std::endl;
		return;
	}
	
	GPIOPin pin = pinPosition->second;
	if(pin.getDirection() == Input)
	{
		std::cerr << "Cannot set value on pin '" << pinId << "', it is an input pin!" << std::endl;
		return;
	}
	
	pin.setValue(value);	
}

PinValue GPIOManager::getPinValue(const unsigned int pinId) const
{
	auto pinPosition = m_pins.find(pinId);
	if(pinPosition == m_pins.end())
	{
		std::cerr << "Cannot get value on pin '" << pinId << "', this pin has not been registered!" << std::endl;
		return Low;
	}
	
	return pinPosition->second.getValue();
}

void GPIOManager::blinkPin(const unsigned int pinId, const unsigned int time)
{
	using namespace std;
	
	auto pinPosition = m_pins.find(pinId);
	if(pinPosition == m_pins.end())
	{
		cerr << "Cannot blink pin '" << pinId << "', this pin has not been registered!" << endl;
		return;
	}
	
	GPIOPin pin = pinPosition->second;
	if(pin.getDirection() == Input)
	{
		cerr << "Cannot blink pin '" << pinId << "', it is an input pin!" << endl;
		return;
	}
	
	pin.setValue(High);
	
	chrono::steady_clock timeCounter;  
	auto start = timeCounter.now(); 

	double elapsedTime = 0;
	while(elapsedTime < time)
	{
		auto now = timeCounter.now();
		elapsedTime = chrono::duration_cast<chrono::milliseconds>(now - start).count();
	}
	
	pin.setValue(Low);
}
