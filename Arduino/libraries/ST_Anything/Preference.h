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
#ifndef PREFERENCE_H_
#define PREFERENCE_H_

#include <Arduino.h>

#define MAX_PREFERENCES_COUNT 8

namespace st
{
    class Preference
    {
        private:
            const String m_key;
            String m_value;

            static Preference* s_preferences[MAX_PREFERENCES_COUNT];

        public:
            static const String UNDEFINED_STRING;

            Preference(String key, String value);
            virtual ~Preference();

            inline const String getKey() const { return m_key; }
            inline String getValue() const { return m_value; }
            inline void setValue(String value) {  m_value = value; }

            static const String get(String key);
            static void set(String key, String value);
            static void remove(String key);
    };
}
#endif /* PREFERENCE_H_ */
