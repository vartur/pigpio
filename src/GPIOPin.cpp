#include "GPIOPin.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace
{
	const std::string EXPORT_PATH = "/sys/class/gpio/export";
	const std::string UNEXPORT_PATH = "/sys/class/gpio/unexport";
	const std::string GPIO_PATH = "/sys/class/gpio/gpio";
}

using namespace PiGPIO;

GPIOPin::GPIOPin(unsigned int id)
:	m_id(id),
	m_state(Unexported),
	m_direction(Output)	
{
}

GPIOPin::GPIOPin(const GPIOPin& other)
:	m_id(other.m_id),
	m_state(other.m_state),
	m_direction(other.m_direction)
{
}

GPIOPin::GPIOPin(GPIOPin&& other) noexcept
:	m_id(other.m_id),
	m_state(other.m_state),
	m_direction(other.m_direction)
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
	switch(state)
	{
		case Exported:
			writeToFile(EXPORT_PATH, m_id);
			break;
			
		case Unexported:
		default:
			writeToFile(UNEXPORT_PATH, m_id);
			break;
	}
	
	m_state = state;
}

PinDirection GPIOPin::getDirection() const
{
	return m_direction;
}

void GPIOPin::setDirection(const PinDirection& direction)
{
	using namespace std;
	if(m_state == Unexported)
	{
		cerr << "Cannot set direction on an unexported pin!" << endl;
		return;
	}
	
	const string directionPath = GPIO_PATH + to_string(m_id) + "/direction";
	
	switch(direction)
	{
		case Input:
			writeToFile(directionPath, "in");
			break;
			
		case Output:
		default:
			writeToFile(directionPath, "out");
			break;
	}
	
	m_direction = direction;
}

PinValue GPIOPin::getValue() const
{
	using namespace std;
	if(m_state == Unexported)
	{
		cerr << "Cannot get value of an unexported pin!" << endl;
		return Low;
	}
	
	const string valuePath = GPIO_PATH + to_string(m_id) + "/value";
	
	string value = readFromFile(valuePath);
	if(value == "0")
	{
		return Low;
	}
	else
	{
		return High;
	}
}

void GPIOPin::setValue(const PinValue& value)
{
	using namespace std;
	if(m_state == Unexported)
	{
		cerr << "Cannot set value on an unexported pin!" << endl;
		return;
	}
	
	const string valuePath = GPIO_PATH + to_string(m_id) + "/value";
	
	switch(value)
	{
		case High:
			writeToFile(valuePath, 1);
			break;
			
		case Low:
		default:
			writeToFile(valuePath, 0);
			break;
	}

}

void GPIOPin::writeToFile(const std::string& path, const auto& value)
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

std::string GPIOPin::readFromFile(const std::string& path)
{
	using namespace std;
		
    ifstream fileStream(path.c_str());
    if (!fileStream)
    {
        cerr << "An error occurred whilst reading file '" << path << "'" << endl;
        return "";
    }

	string value = "";
    fileStream >> value ;
    fileStream.close();
    
    return value;
}
 





