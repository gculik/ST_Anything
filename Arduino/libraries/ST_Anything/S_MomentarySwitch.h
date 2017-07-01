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
#ifndef ST_S_MOMENTARY_SWITCH
#define ST_S_MOMENTARY_SWITCH

#include "Sensor.h"

namespace st
{
	class S_MomentarySwitch: public Sensor
	{
		private:
			bool m_bCurrentState;	//HIGH or LOW
			bool m_bInvertLogic;	//determines whether the Arduino Digital Output should use inverted logic
			byte m_nPin;			//Arduino Pin used as a Digital Output for the switch - often connected to a relay or an LED
            unsigned long m_start; // start of a momentary contact duration
		    unsigned long m_duration; // momentary contact duration in milliseconds
		
		public:
			//constructor - called in your sketch's global variable declaration section
			S_MomentarySwitch(const __FlashStringHelper *name, byte pin, bool startingState = LOW, bool invertLogic = false, unsigned long duration = 1000);
			
			//destructor
			virtual ~S_MomentarySwitch();

			//initialization routine
			virtual void init();

			//SmartThings Shield data handler (receives command to turn "on" or "off" the switch (digital output)
			virtual void beSmart(const String &str);
			
            //update function
            void update();

            //called periodically to ensure state of the switch is up to date in the SmartThings Cloud (in case an event is missed)
			virtual void refresh();
	};
}
#endif
