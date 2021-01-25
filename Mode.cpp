/** @file Mode.cpp
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
#include <algorithm>
//#include <random>
#include "Harmony.hpp"
#include "Mode.hpp"

/*
 * Constructor of 'Mode'
 * we need to know the Scale (hence the pointer)
 * otherwise we cannot create the
 * mode intervals.
 */
Mode::Mode(Scale *scaleParent,
		   unsigned int modeNumArg,
		   unsigned long numOfNotesArg,
		   std::string modeNameArg) noexcept {
	modeNum = modeNumArg;
	//privName = modeNumArg;
	numOfNotes = numOfNotesArg;
	privName = modeNameArg;
	uint8_t rootNote = scaleParent->rootNote;

	printf("Mode constructor");

	
	// Create the notes for this mode
	for(uint8_t j = 0, k = rootNote; j < numOfNotes; j++) {
			printf("Creating notes:%d --", j);
		Note note;
		// If the numOfNotes is bigger than the
		// const array we have a out of bounds issue.
		// TODO: change the array to a std:vector
		// TODO: or std:array
		
		if (j == 0) {	// Root note remains root
			note.number = rootNote;
		}
		else {
			note.number = k; // take the previous note number.
							 // Based on the type of scale we lookup the table
							 // We need to substract j - 1 otherwise
							 // we will be missing the first offset
							 // ( j == 0 is covered above)
			switch(scaleParent->typeOfScale) {
				case Scale::TypeOfScale::CHROMATIC:
					note.number = 	note.number + chromatic[j-1];
					//note.number += 	scaleParent->chromatic[j-1];
					break;
				case Scale::TypeOfScale::OCTATONIC:
					note.number = 	note.number +
					octatonic[this->modeNum][j-1];
					break;
				case Scale::TypeOfScale::DOMINANT_DIMINISHED:
					note.number = 	note.number +
					dominant_diminished[j-1];
					break;
				case Scale::TypeOfScale::DIMINISHED:
					note.number = 	note.number +
					diminished[j-1];
					break;
				case Scale::TypeOfScale::MAJOR:
					note.number = 	note.number +
					major_s[this->modeNum][j-1];
					break;
				case Scale::TypeOfScale::MINOR:
					note.number = 	note.number +
					minor_s[this->modeNum][j-1];
					break;
				case Scale::TypeOfScale::MELODIC_MINOR:
					note.number = 	note.number +
					melodic_minor[this->modeNum][j-1];
					break;
				case Scale::TypeOfScale::HARMONIC_MINOR:
					note.number = 	note.number +
					harmonic_minor[this->modeNum][j-1];
					break;
				case Scale::TypeOfScale::GYPSY:
					note.number = 	note.number +
					gypsy[j-1];
					break;
				case Scale::TypeOfScale::SYMETRICAL:
					note.number =	note.number +
					symetrical[j-1];
					break;
				case Scale::TypeOfScale::ENIGMATIC:
					note.number =	note.number +
					enigmatic[j-1];
					break;
				case Scale::TypeOfScale::ARABIAN:
					note.number =	note.number +
					arabian[j-1];
					break;
				case Scale::TypeOfScale::HUNGARIAN:
					note.number =	note.number +
					hungarian[j-1];
					break;
				case Scale::TypeOfScale::WHOLE_TONE:
					note.number =	note.number +
					whole_tone[j-1];
					break;
				case Scale::TypeOfScale::AUGMENTED:
					note.number =	note.number +
					augmented[this->modeNum][j-1];
					break;
				case Scale::TypeOfScale::BLUES_MAJOR:
					note.number =	note.number +
					blues_major[j-1];
					break;
				case Scale::TypeOfScale::BLUES_MINOR:
					note.number =	note.number +
					blues_minor[this->modeNum][j-1];
					break;
				case Scale::TypeOfScale::PENTATONIC:
					note.number =	note.number +
					pentatonic[j-1];
					break;
				case Scale::TypeOfScale::MINOR_PENTATONIC:
					note.number =	note.number +
					minor_pentatonic[j-1];
					break;
					// TODO: IMPLEMENT
				default:
					// Don't to anything.
					break;
			}
			k = note.number; 	// Save just calculated note number in 'k'
		}
		// 'notes' is a vector containing our 'note' objects itself
		this->notes.push_back(note);
	}
	
};


/** This function reorders the notes in the mode
 */
 #if 0
void Mode::Order(NoteOrder noteOrderArg) {
	std::random_device rd;
	switch(noteOrderArg) {
		case NoteOrder::LOW_TO_HIGH:
			sort(notes.begin(), notes.end(), Mode::privLowToHigh);
			break;
		case NoteOrder::HIGH_TO_LOW:
			sort(notes.begin(), notes.end(), Mode::privHighToLow);
			break;
		case NoteOrder::RANDOM:
			std::shuffle(notes.begin(), notes.end(), rd);
			break;
		default:
			break;
	}
}
#endif 


// EOF
