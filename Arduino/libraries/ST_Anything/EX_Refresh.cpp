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
 *  Summary:  EX_Refresh is a class which implements the SmartThings "Refresh" device capability.
 */
#include "EX_Refresh.h"

#include "Constants.h"
#include "Everything.h"

namespace st
{
    /*
     * Constructs the EX_Refresh instance.
     *    name - name of the device
     */
    EX_Refresh::EX_Refresh(const __FlashStringHelper *name) : Executor(name)
    {
    }

    /*
     * Parse the command messages from the SmartThings shield.
     */
    void EX_Refresh::beSmart(const String &str)
    {
        String s = str.substring(str.indexOf(' ') + 1);
        if (debug)
        {
            Serial.print(F("EX_Refresh::beSmart s = "));
            Serial.println(s);
        }
        if ((s == F("refresh")))
        {
            Everything::refresh();
        }
    }
}
