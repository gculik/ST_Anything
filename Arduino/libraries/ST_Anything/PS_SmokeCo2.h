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
#ifndef ST_PS_VOLTAGE_H
#define ST_PS_VOLTAGE_H

#include "PollingSensor.h"

namespace st
{
	class PS_SmokeCo2: public PollingSensor
	{
		private:
			enum State { CLEAR, CO2, SMOKE };

			byte m_nAnalogInputPin;
			int m_co2Threshold;
			int m_smokeThreshold;
			State m_lastState;
			void updateAndSend(bool forceSend);

		public:
			PS_SmokeCo2(const __FlashStringHelper *name, unsigned int interval, int offset, byte analogInputPin, int co2_threshold=300, int smoke_threshold=600);
			virtual ~PS_SmokeCo2();

			virtual void init();
			virtual void refresh();
			virtual void getData();
	};
}
#endif
