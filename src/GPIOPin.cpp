#include "GPIOPin.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace
{
	const std::string EXPORT_PATH = "/sys/class/gpio/export";
	const std::string UNEXPORT_PATH = "/sys/class/gpio/unexport";
}

using namespace PiGPIO;

GPIOPin::GPIOPin(unsigned int id)
:	m_id(id),
	m_state(Unexported),
	m_direction(Output),
	m_value(Low)	
{
}

GPIOPin::GPIOPin(const GPIOPin& other)
:	m_id(other.m_id),
	m_state(other.m_state),
	m_direction(other.m_direction),
	m_value(other.m_value)
{
}

GPIOPin::GPIOPin(GPIOPin&& other) noexcept
:	m_id(other.m_id),
	m_state(other.m_state),
	m_direction(other.m_direction),
	m_value(other.m_value)
{
}

GPIOPin::~GPIOPin() noexcept
{
}

GPIOPin& GPIOPin::operator=(const GPIOPin& other)
{
	GPIOPin tmp = GPIOPin(other);
	*this = std::move(tmp);
	return *this;
}

GPIOPin& GPIOPin::operator=(GPIOPin&& other) noexcept
{
	if(this == &other)
	{
		return *this;
	}
	
	m_id = other.m_id;
	m_state = other.m_state;
	m_direction = other.m_direction;
	m_value = other.m_value;
	
	return *this;
}

unsigned int GPIOPin::getID() const
{
	return m_id;
}

PinExportState GPIOPin::getExportState() const
{
	return m_state;
}

void GPIOPin::setExportState(const PinExportState& state)
{
	using namespace std;
	string exportPath = "";
	
	switch(state)
	{
		case Exported:
			exportPath = EXPORT_PATH;
			break;
			
		case Unexported:
		default:
			exportPath = UNEXPORT_PATH;
			break;
	}
	
	writeToFile(exportPath, m_id);
	m_state = state;
}

PinDirection GPIOPin::getDirection() const
{
	return m_direction;
}



void GPIOPin::writeToFile(const std::string& path, const auto& value) const
{
	using namespace std;
	
	ofstream fileStream(path);
	if(!fileStream)
	{
		cerr << "An error occurred whilst writing to file '" << path << "'" << endl;
		return;
	}
	
	fileStream << value;
	fileStream.close();
}






