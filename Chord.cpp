/** @file Chords.cpp
 *
 * Harmony implements Notes, Scales, Modes, Chords
 * the intent is to keep this library as clean
 * as possible to allow implementation on hardware
 * platforms such as ARM MBED OS.
 * TODO: Chords, Inversions, Progressions
 *
 * @author Jan-Willem Smaal <usenet@gispen.org>
 * @date 13/12/2020
 * @copyright APACHE-2.0
 */
#include "Chord.hpp"


/** Chord constructor
 * for now it's not scale aware yet (work in progress)
 */
Chord::Chord(Chord::Type chordTypeArg,
			 uint8_t bassnoteArg,
			 uint8_t rootnoteArg ) noexcept {
	
	chordType = chordTypeArg;
	bassnote = bassnoteArg;
	rootnote = rootnoteArg;
	
	// Find out the type of chord we are asked to become.
	switch(chordTypeArg) {
		case Type::MAJOR:
			privText = "Major";
			shortPrivText = "";
			chordVect = majorVect;
			break;
		case Type::MAJOR_6:
			privText = "Major 6'th";
			shortPrivText = "6";
			chordVect = major_6_Vect;
			break;
		case Type::MAJOR_7:
			privText = "Major 7'th";
			shortPrivText = "maj7";
			chordVect = major_7_Vect;
			break;
		case Type::MAJOR_9:
			privText = "Major 9'th";
			shortPrivText = "maj9";
			chordVect = major_9_Vect;
			break;
		case Type::MAJOR_7_SHARP11:
			privText = "Major 7'th #11";
			shortPrivText = "maj7#11";
			chordVect = major_7_sharp11_Vect;
			break;
		case Type::MINOR:
			privText = "Minor";
			shortPrivText = "m";
			chordVect = minorVect;
			break;
		case Type::MINOR_6:
			privText = "Minor 6'th";
			shortPrivText = "m6";
			chordVect = minor_6_Vect;
			break;
		case Type::MINOR_FLAT6:
			privText = "Minor b6";
			shortPrivText = "mb6";
			chordVect = minor_flat6_Vect;
			break;
		case Type::MINOR_7:
			privText = "Minor 7'th";
			shortPrivText = "m7";
			chordVect = minor_7_Vect;
			break;
		case Type::MINOR_9:
			privText = "Minor 9'th";
			shortPrivText = "m9";
			chordVect = minor_9_Vect;
			break;
		case Type::MINOR_MAJOR_7:
			privText = "Minor major 7'th";
			shortPrivText = "minMaj7";
			chordVect = minor_major_7_Vect;
			break;
		case Type::DOMINANT_7:
			privText = "Dominant 7'th";
			shortPrivText = "7";
			chordVect = dominant_7_Vect;
			break;
		case Type::DOMINANT_7_FLAT5:
			privText = "Dominant 7'th b5";
			shortPrivText = "7b5";
			chordVect = dominant_flat5_Vect;
			break;
		case Type::DOMINANT_7_SHARP5:
			privText = "Dominant 7'th #5";
			shortPrivText = "7#5";
			chordVect = dominant_sharp5_Vect;
			break;
		case Type::DOMINANT_7_SUS4:
			privText = "Dominant 7'th with suspended 4'th";
			shortPrivText = "7sus4";
			chordVect = dominant_7_sus4;
			break;
		case Type::DOMINANT_7_FLAT9:
			privText = "Dominant 7'th b9";
			shortPrivText = "7b9";
			chordVect = dominant_7_flat9;
			break;
		case Type::DOMINANT_7_SHARP9:
			privText = "Dominant 7'th #9";
			shortPrivText = "7#9";
			chordVect = dominant_7_sharp9;
			break;
		case Type::DOMINANT_7_SHARP5_FLAT9:
			privText = "Dominant 7'th #5 b9";
			shortPrivText = "7#5b9";
			chordVect = dominant_7_sharp5_flat9;
			break;
		case Type::DOMINANT_7_SHARP11:
			privText = "Dominant 7'th #11";
			shortPrivText = "7#11";
			chordVect = dominant_7_sharp11;
			break;
		case Type::DOMINANT_7_ADD9_FLAT5:
			privText = "Dominant 7'th add9 b5";
			shortPrivText = "7add9b5";
			chordVect = dominant_7_add9_flat5;
			break;
		case Type::DOMINANT_7_ADD9_SHARP11:
			privText = "Dominant 7'th add9 #11";
			shortPrivText = "7add9#11";
			chordVect = dominant_7_add9_sharp11;
			break;
		case Type::DOMINANT_7_ADD13:
			privText = "Dominant 7'th add13";
			shortPrivText = "7add13";
			chordVect = dominant_7_add13;
			break;
		case Type::DOMINANT_7_SHARP9_FLAT13:
			privText = "Dominant 7'th #9 b13";
			shortPrivText = "7#9b13";
			chordVect = dominant_7_sharp9_flat13;
			break;
		case Type::DOMINANT_7_SHARP11_ADD13:
			privText = "Dominant 7'th #11 add13";
			shortPrivText = "7#11add13";
			chordVect = dominant_7_sharp11_add13;
			break;
		case Type::DIMINISHED:
			privText = "Diminished";
			shortPrivText = "dim";
			chordVect = diminished;
			break;
		case Type::DIMINISHED_7:
			privText = "Diminished 7";
			shortPrivText = "dim7";
			chordVect = diminished_7;
			break;
		case Type::MINOR_7_FLAT5:
			privText = "Minor 7 b5";
			//shortPrivText = "m7b5";
			shortPrivText = "0";
			chordVect = minor_7_flat5;
			break;
		case Type::AUGMENTED:
			privText = "Augmented";
			shortPrivText = "+";
			chordVect = augmented;
			break;
		case Type::SUS4:
			privText = "Suspended 4'th";
			shortPrivText = "sus4";
			chordVect = sus4;
			break;
		case Type::SUS2:
			privText = "Suspended 2'nd";
			shortPrivText = "sus2";
			chordVect = sus2;
			break;
			//default:	//	Does not exist when using enum Classes!
			// break;
	}
	
	// Build the chord now that we know the recipe.
	Note note(rootnote);
	notes.push_back(note);
	uint8_t previousnote = rootnote;
	for (auto vect: chordVect) {
		// c style cast required on the Enum
		previousnote = previousnote + (uint8_t)vect;
		Note noteU(previousnote);
		notes.push_back(noteU);
	}
	// Default voicing is as in the constructor.
	voicing = notes;
};


/**
 * Chord voicings
 */
void Chord::setVoicing(VoicingType voicingTypeArg,
					   bool dropRootDown){
	
	// Drop the root note an octave when asked for.
	if (notes.front().number >= 12 && dropRootDown ) {
		voicing.front().number = notes.front().number - 12;
	}
	
	// Based on the requested voicing shuffle around the notes.
	switch (voicingTypeArg) {
		case VoicingType::DROP1:
			// Take the last note and drop an octave.
			if (voicing.back().number >= 12 ) {
				voicing.back().number = voicing.back().number - 12;
			}
			break;
		case VoicingType::DROP2:
			// Take the last note and drop an octave.
			if (voicing.back().number >= 12 ) {
				voicing.back().number = voicing.back().number - 12;
			}
			// Take the second to last note and drop an octave.
			Note tmpNote = voicing.back();
			voicing.pop_back(); // Remove the last one (put it back later).
			if (voicing.back().number >= 12 ) {
				voicing.back().number = voicing.back().number - 12;
			}
			// Not exactly in the right order anymore but that's ok.
			voicing.push_back(tmpNote);
			break;
	}
};
