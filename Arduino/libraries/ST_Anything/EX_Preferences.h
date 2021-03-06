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
#ifndef ST_EX_Preferences_H
#define ST_EX_Preferences_H

#include "Executor.h"
#include "Preference.h"

namespace st
{
    class EX_Preferences: public Executor
    {
        public:
            // constructor
            EX_Preferences(const __FlashStringHelper *name);

            // virtuals
            virtual void init();
            virtual void beSmart(const String &str);
    };
}
#endif
