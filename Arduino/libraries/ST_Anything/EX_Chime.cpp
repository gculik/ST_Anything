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
 *  Summary:  EX_Chime is a class which implements the SmartThings "Tone" device capability,
 *            and produces a door chime melody, or an arbitrary user defined melody.
 *            Additionally this chime allows for triggering of a continuous warning tone, when the system is armed.
 */
#include "EX_Chime.h"

#include "Constants.h"
#include "Everything.h"

namespace st
{
    const unsigned int EX_Chime::DEFAULT_NOTES[] = { NOTE_GS7, NOTE_GS7 };
    const unsigned int EX_Chime::DEFAULT_DURATIONS[] = { 6, 6 };
	bool EX_Chime::debug=false;

    /*
     * Constructs the EX_Chime instance.
     *    name - name of the device
     *    pin - pin number of the output pin that has a piezzo buzzer, or amplified speaker connected
     *    size - size of the note and duration arrays
     *    notes - an array of melody notes (optional, defaults to { NOTE_FS7, NOTE_D7 })
     *    durations - an array of note durations in note lengths (optional, defaults to { 3, 2 })
     *          e.g. 1 = full note, 2 = half note 4 = quarter note, 8 = eighth note
     */
    EX_Chime::EX_Chime(const __FlashStringHelper *name, byte pin, unsigned int size, unsigned int notes[], unsigned int durations[]) :
            EX_Tone(name, pin), m_size(size), m_notes(notes), m_durations(durations), m_armed(false)
    {
    }

    /*
     * Parse the command message from SmartThings.
     */
    void EX_Chime::beSmart(const String &str)
    {
        String s = str.substring(str.indexOf(' ') + 1);
        if (debug)
        {
            Serial.print(F("EX_Chime::beSmart s = "));
            Serial.println(s);
        }
        if ((s == F("chime")))
        {
            chime();
        }
        else if ((s == F("arm")))
        {
            arm();
        }
        else if ((s == F("warn")))
        {
            warn();
        }
        else if ((s == F("disarm")))
        {
            disarm();
        }

    }

    /*
     * Generate the standard chime melody.
     */
    void EX_Chime::chime() const
    {
    	// send a beep status
		Everything::sendSmartString(getName() + F(" chime"));

        // iterate over the notes of the melody
        for (unsigned int index = 0; index < m_size; index++)
        {
            // calculate the note duration
            unsigned int duration = MILLIS_PER_SECOND / (m_durations[index] * TEMPO_BPS);
            tone(getPin(), m_notes[index], duration);

            // pause between notes
            delay(duration);
        }
        if (debug)
        {
            Serial.println(F("EX_Chime: DING DONG"));
        }

    	// send an off status
        if (m_armed)
        {
    		Everything::sendSmartString(getName() + F(" armed"));
        }
        else
        {
    		Everything::sendSmartString(getName() + F(" off"));
        }
    }

    /*
     * Arm the chime, which will allow it to chime repeatedly.
     */
    void EX_Chime::arm()
    {
        m_armed = true;
  		Everything::sendSmartString(getName() + F(" armed"));
    }

    /*
     * Sounds an armed warning only if armed.
     */
    void EX_Chime::warn() const
    {
        if (m_armed)
        {
		    if(millis() % MILLIS_PER_SECOND == 0)
		    {
                EX_Tone::beep(WARN_FREQUENCY, WARN_DURATION);
		    }
        }
    }

    /*
     * Disarm the chime, which will stop it from chiming repeatedly.
     */
    void EX_Chime::disarm()
    {
        m_armed = false;
  		Everything::sendSmartString(getName() + F(" off"));
    }
}
