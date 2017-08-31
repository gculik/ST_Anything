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
 *  Summary:  EX_Preferences is a class which implements a SmartThings "preferences" map
 */
#include "EX_Preferences.h"

#include "Constants.h"
#include "Everything.h"

namespace st
{
    /*
     * Constructs the EX_Preferences instance.
     *    name - name of the device
     */
    EX_Preferences::EX_Preferences(const __FlashStringHelper *name) : Executor(name)
    {
    }

    /*
     * Initialize the preferences.
     */
    void EX_Preferences::init()
    {
    	// send a void message to SmartThings so it can autowire the device
		Everything::sendSmartString(getName() + F(" void"));
    }

    /*
     * Parse the command message from the SmartThings.
     */
    void EX_Preferences::beSmart(const String &str)
    {
        String keyValue = str.substring(str.indexOf(' ') + 1);
        String key = keyValue.substring(0, keyValue.indexOf(' '));
        String value = keyValue.substring(keyValue.indexOf(' ') + 1);
    	Preference::set(key, value);
        if (debug)
        {
            Serial.print(F("EX_Preferences::beSmart s = "));
            Serial.print(key);
            Serial.print(F("="));
            Serial.println(value);
        }
    }
}
