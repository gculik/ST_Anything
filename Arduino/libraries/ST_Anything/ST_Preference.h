/**
 *  A preference which consists of a key value pair.
 *
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
 */
#ifndef ST_PREFERENCE_H_
#define ST_PREFERENCE_H_

#include <Arduino.h>

#define MAX_PREFERENCES_COUNT 8

namespace st
{
    class ST_Preference
    {
        private:
            const String m_key;
            String m_value;

            static ST_Preference* s_preferences[MAX_PREFERENCES_COUNT];

        public:
            ST_Preference(String& key, String& value);
            virtual ~ST_Preference();

            inline const String getKey() const { return m_key; }
            inline const String getValue() const { return m_value; }
            inline const String setValue(String& value) {  m_value = value; }

            static void setPreference(String& key, String& value);

    };
}
#endif /* ST_PREFERENCE_H_ */
