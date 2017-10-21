//******************************************************************************************
//  File: PS_SmokeCo2.h
//  Authors: Jiri Culik
//
//  Summary:  PS_SmokeCo2 is a class which implements the SmartThings "Smoke Detector" device capability.
//            It uses an analog input to measure the output voltage of a custom circuit that interfaces
//            with a FirstAlert/BKR wired interconnected Smoke and Smoke/CO2 detectors.
//
//			  st::PS_SmokeCo2() constructor requires the following arguments
//				- String &name - REQUIRED - the name of the object - must match the Groovy ST_Anything DeviceType tile name
//				- long interval - REQUIRED - the polling interval in milliseconds
//				- long offset - REQUIRED - the polling interval offset in milliseconds - used to prevent all polling sensors from executing at the same time
//				- byte pin - REQUIRED - the Arduino Pin to be used as a digital output
//              - int co2_threshold - OPTIONAL - the threshold (0 - 1024) above which CO2 has been detected.
//              - int smoke_threshold - OPTIONAL - the threshold (0 - 1024) above which smoke has been detected.
//
//******************************************************************************************
#include "PS_SmokeCo2.h"

#include "Constants.h"
#include "Everything.h"

namespace st
{
//private
	

//public
	//constructor
	PS_SmokeCo2::PS_SmokeCo2(const __FlashStringHelper *name, unsigned int interval, int offset, byte analogInputPin, int co2_threshold, int smoke_threshold):
		PollingSensor(name, interval, offset),
		m_nAnalogInputPin(analogInputPin),
		m_co2Threshold(co2_threshold),
		m_smokeThreshold(smoke_threshold),
		m_lastState(CLEAR)
	{
	}
	
	//destructor
	PS_SmokeCo2::~PS_SmokeCo2()
	{
	}

	void PS_SmokeCo2::init()
	{
		updateAndSendState(true);
	}

	void PS_SmokeCo2::refresh()
	{
		updateAndSendState(true);
	}

	// read the analog input pin and determine whether CO2 or Smoke have been triggered.
	void PS_SmokeCo2::getData()
	{
		updateAndSendState(false);
	}

	// updates the current state and send to the cloud, forceSend will send the update to the cloud regardless of any state changes
	void PS_SmokeCo2::updateAndSendState(bool forceSend)
	{
		int value = analogRead(m_nAnalogInputPin);
		if (value > m_smokeThreshold)
		{
			// only send an update if the state has changed or forceSend is enabled
			if (forceSend == true || m_lastState != SMOKE)
			{
				Everything::sendSmartString(getName() + F(" smoke detected"));
			}
		}
		else if (value > m_co2Threshold)
		{
			// only send an update if the state has changed or forceSend is enabled
			if (forceSend == true || m_lastState != CO2)
			{
				Everything::sendSmartString(getName() + F(" carbonMonoxide detected"));
			}
		}
		else
		{
			if (forceSend == true || m_lastState != CLEAR)
			{
				Everything::sendSmartString(getName() + F(" smoke clear"));
				Everything::sendSmartString(getName() + F(" carbonMonoxide clear"));
			}
		}
	}
}
