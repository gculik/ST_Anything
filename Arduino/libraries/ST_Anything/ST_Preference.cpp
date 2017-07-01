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
#include "ST_Preference.h"

namespace st
{
    ST_Preference* ST_Preference::s_preferences[MAX_PREFERENCES_COUNT];

	// constructor
	ST_Preference::ST_Preference(String& key, String& value):
		m_key(key),
		m_value(value)
	{
	}

	// destructor
	ST_Preference::~ST_Preference()
	{
	}

	// sets the preference
	void ST_Preference::setPreference(String& key, String& value)
	{
	    byte firstEmptyIndex = -1;
	    for (byte index = 0; index < MAX_PREFERENCES_COUNT; index++)
	    {
	        // keep track of the first empty slot
	        if (s_preferences[index] == NULL && firstEmptyIndex == -1)
	        {
	            firstEmptyIndex = index;
	        }
	        else
	        {
	            // look for a matching key
	            if (s_preferences[index]->getKey() == key)
	            {
	                // when the value is non NULL set the value on an existing preference
	                if (value)
	                {
	                    s_preferences[index]->setValue(value);
	                }
                    // when the value is NULL we remove the preference
	                else
	                {
	                    delete s_preferences[index];
	                    s_preferences[index] = NULL;
	                }
	                return;
	            }
	        }
	    }

	    // attempt to add a new preference
	    if (firstEmptyIndex != -1)
	    {
	        s_preferences[firstEmptyIndex] = new ST_Preference(key, value);
	    }
	}
}
