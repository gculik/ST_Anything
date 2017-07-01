/*
 *  Copyright 2017 Imprimis LLC
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License. You may obtain a copy of the License at:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 *  on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 *  for the specific language governing permissions and limitations under the License.
 *
 *  Authors: Jiri Culik
 *  Summary:  EX_MomentarySwitch is a class which implements the SmartThings "Momentary" and "Switch" device capability.
 */
#include "S_MomentarySwitch.h"

#include "Constants.h"
#include "Everything.h"

namespace st
{
//public
	//constructor
	S_MomentarySwitch::S_MomentarySwitch(const __FlashStringHelper *name, byte pin, bool startingState, bool invertLogic, unsigned long duration = 1000) :
		Sensor(name),
		m_nPin(pin),
		m_bCurrentState(startingState),
		m_bInvertLogic(invertLogic),
		m_duration(duration),
		m_start(0)

	{
        pinMode(m_nPin, OUTPUT);
        digitalWrite(m_nPin, m_bInvertLogic ? !m_bCurrentState : m_bCurrentState);
	}

	//destructor
	S_MomentarySwitch::~S_MomentarySwitch()
	{
	
	}
	
	void S_MomentarySwitch::init()
	{
        refresh();
	}

	void S_MomentarySwitch::beSmart(const String &str)
	{
		String s=str.substring(str.indexOf(' ')+1);
		if (st::Executor::debug) {
			Serial.print(F("S_MomentarySwitch::beSmart s = "));
			Serial.println(s);
		}
        if(s==F("push"))
        {
            m_start = millis();
            m_bCurrentState=HIGH;
        }
		else if(s==F("on"))
		{
			m_bCurrentState=HIGH;
		}
		else if(s==F("off"))
		{
			m_bCurrentState=LOW;
		}
        digitalWrite(m_nPin, m_bInvertLogic ? !m_bCurrentState : m_bCurrentState);
        Everything::sendSmartString(getName() + " " + (m_bCurrentState == HIGH ? F("on") : F("off")) + F(" true"));
	}
	
    //update function
    void S_MomentarySwitch::update()
    {
        if (m_start != 0)
        {
            if (millis() - m_start > m_duration)
            {
                m_start = 0;
                m_bCurrentState = LOW;
                digitalWrite(m_nPin, m_bInvertLogic ? !m_bCurrentState : m_bCurrentState);
                Everything::sendSmartString(getName() + " " + (m_bCurrentState == HIGH ? F("on") : F("off")) + F(" true"));
            }
        }
    }

	void S_MomentarySwitch::refresh()
	{
	    Everything::sendSmartString(getName() + " " + (m_bCurrentState == HIGH ? F("on") : F("off")) + F(" false"));
	}
}
