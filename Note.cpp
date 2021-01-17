/** @file Note.cpp
 *
 * Harmony implements Notes, Scales, Modes
 * the intent is to keep this library as clean
 * as possible to allow implementation on hardware
 * platforms such as ARM MBED OS.
 * No exceptions are used as the platform does not
 * support it.
 *
 * TODO: Chords, Inversions, Progressions
 *
 * @author Jan-Willem Smaal <usenet@gispen.org>
 * @date 13/12/2020
 * @copyright APACHE-2.0
 */
#include "Note.hpp"


/** Convert string to midi note.
 * e.g. F#, G# Gb A
 * C3 C-2 Ab5 etc...
 */
const uint8_t Note::ToNote(std::string str) {
	uint8_t basenote = 60;  // If no basenote is given use 60 (middle C3)
	
	// TODO: find the last numeral in the string add 2
	// TODO: and then multiply by 12
	// TODO: implement .e.g C#3 ('3')
	// TODO: i.e. (3 + 2)  12 = 60
	
	
	// Uppercase:
	if(str == "C") 	basenote += 0;
	if(str == "C#") basenote += 1;
	if(str == "Db") basenote += 1;
	if(str == "D") 	basenote += 2;
	if(str == "D#") basenote += 3;
	if(str == "Eb") basenote += 3;
	if(str == "E") 	basenote += 4;
	if(str == "F")	basenote += 5;
	if(str == "F#") basenote += 6;
	if(str == "Gb") basenote += 6;
	if(str == "G") 	basenote += 7;
	if(str == "G#") basenote += 8;
	if(str == "Ab") basenote += 8;
	if(str == "A") 	basenote += 9;
	if(str == "A#")	basenote += 10;
	if(str == "Bb")	basenote += 10;
	if(str == "B")	basenote += 11;
	
	// Same with lowercase:
	if(str == "c") 	basenote += 0;
	if(str == "c#") basenote += 1;
	if(str == "db") basenote += 1;
	if(str == "d") 	basenote += 2;
	if(str == "d#") basenote += 3;
	if(str == "eb") basenote += 3;
	if(str == "e") 	basenote += 4;
	if(str == "f")	basenote += 5;
	if(str == "f#") basenote += 6;
	if(str == "gb") basenote += 6;
	if(str == "g") 	basenote += 7;
	if(str == "g#") basenote += 8;
	if(str == "ab") basenote += 8;
	if(str == "a") 	basenote += 9;
	if(str == "a#")	basenote += 10;
	if(str == "bb")	basenote += 10;
	if(str == "b")	basenote += 11;
	
	return basenote;
}


/** Simply convert MIDI notename to a note either using flats or sharps
 */
const std::string Note::ToText(uint8_t midinote,
							   bool flats,
							   bool showoctave)
{
	int octave;
	uint8_t note;
	std::string strng;
	
	// For MIDI note 0 is written down as "C-2" hence the -2 below
	octave = (midinote / 12) - 2;
	note = midinote - ((octave + 2) * 12);
	
	if(flats) {
		switch(note) {
			case 0:
				strng = "C";
				break;
			case 1:
				strng = "Db";
				break;
			case 2:
				strng = "D";
				break;
			case 3:
				strng = "Eb";
				break;
			case 4:
				strng = "E";
				break;
			case 5:
				strng = "F";
				break;
			case 6:
				strng = "Gb";
				break;
			case 7:
				strng = "G";
				break;
			case 8:
				strng = "Ab";
				break;
			case 9:
				strng = "A";
				break;
			case 10:
				strng = "Bb";
				break;
			case 11:
				strng = "B";
				break;
			default:
				strng = "!!";
				break;
		}
	}
	else {
		switch(note) {
			case 0:
				strng = "C";
				break;
			case 1:
				strng = "C#";
				break;
			case 2:
				strng = "D";
				break;
			case 3:
				strng = "D#";
				break;
			case 4:
				strng = "E";
				break;
			case 5:
				strng = "F";
				break;
			case 6:
				strng = "F#";
				break;
			case 7:
				strng = "G";
				break;
			case 8:
				strng = "G#";
				break;
			case 9:
				strng = "A";
				break;
			case 10:
				strng = "A#";
				break;
			case 11:
				strng = "B";
				break;
			default:
				strng = "!!";
				break;
		}
	}
	if (showoctave) {
		strng = strng + std::to_string(octave);
	}
	return strng;
}


