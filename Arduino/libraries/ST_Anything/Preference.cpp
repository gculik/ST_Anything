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
#include "Preference.h"

namespace st
{
    Preference* Preference::s_preferences[MAX_PREFERENCES_COUNT] = {};
    const String Preference::UNDEFINED_STRING = String("UNDEFINED");

	// constructor
	Preference::Preference(String key, String value):
		m_key(key),
		m_value(value)
	{
	}

	// destructor
	Preference::~Preference()
	{
	}

	// gets the preference
	const String Preference::get(String key)
	{
	    for (byte index = 0; index < MAX_PREFERENCES_COUNT; index++)
	    {
	        if (s_preferences[index] != NULL)
	        {
	            // look for a matching key
	            if (s_preferences[index]->getKey() == key)
	            {
	            	return s_preferences[index]->getValue();
	            }
	        }
	    }
	    return UNDEFINED_STRING;
	}

	// sets the preference
	void Preference::set(String key, String value)
	{
	    int firstEmptyIndex = -1;
	    for (byte index = 0; index < MAX_PREFERENCES_COUNT; index++)
	    {
	        // keep track of the first empty slot
	        if (s_preferences[index] == NULL)
	        {
	        	if (firstEmptyIndex == -1)
	        	{
	        		firstEmptyIndex = index;
	        	}
	        }
	        else
	        {
	            // look for a matching key
	            if (s_preferences[index]->getKey() == key)
	            {
                    s_preferences[index]->setValue(value);
	                return;
	            }
	        }
	    }

	    // attempt to add a new preference
	    if (firstEmptyIndex != -1)
	    {
	        s_preferences[firstEmptyIndex] = new Preference(key, value);
	    }
	}

	// removes the preference
	void Preference::remove(String key)
	{
	    for (byte index = 0; index < MAX_PREFERENCES_COUNT; index++)
	    {
	        if (s_preferences[index] != NULL)
	        {
	            // look for a matching key
	            if (s_preferences[index]->getKey() == key)
	            {
	            	delete s_preferences[index];
	            	s_preferences[index] = NULL;
	            	return;
	            }
	        }
	    }
	}
}
