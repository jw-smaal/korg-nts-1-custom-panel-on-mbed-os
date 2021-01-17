/** @file scale.cpp
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
#include "Scale.hpp"


/*
 * Default constructor for Scale
 * create a major scale starting at
 * middle C (rootNote=60)
 */
Scale::Scale() noexcept{
	kindOfScale = Scale::KindOfScale::HEPTATONIC;
	typeOfScale = Scale::TypeOfScale::MAJOR;
	numOfModes = 7; // 7 modes in this scale
	numOfNotes = 7; // Heptatonic = 7 notes.
	rootNote = 60;
	
	//	 Create 7 (i) modes object in the vector
	//	 We give a pointer to ourselves as the mode
	//	 must know what kind of scale it is a mode of.
	for(unsigned int i = 0; i < numOfModes; i++) {
		Mode mode(this, i, numOfNotes, "major scale mode");
		modes.push_back(mode);
	}
};


/*
 * Scale::Scale constructs a scale with modes
 * and notes based on the typeOfScaleArg argument given
 * starting at the rootnote (midi note numbers are used).
 */
Scale::Scale(TypeOfScale typeOfScaleArg,
			 uint8_t rootNoteArg) noexcept{
	// MIDI notes cannot be higher than 128
	// instead of throwing an exception we just truncate it to the
	// higest value.
	if(rootNoteArg > 128 ) {
		rootNoteArg = 127;
	}
	rootNote = rootNoteArg;
	typeOfScale = typeOfScaleArg;
	
	switch(typeOfScaleArg) {
		case Scale::TypeOfScale::CHROMATIC:
			scaleText = "CHROMATIC";
			kindOfScale = Scale::KindOfScale::CHROMATIC;
			numOfModes = 1; // only 1 mode in this scale
			numOfNotes = 12;
			break;
			// ---==== 8 NOTE scale's ====----
		case Scale::TypeOfScale::OCTATONIC:
			scaleText ="OCTATONIC";
			kindOfScale = Scale::KindOfScale::OCTATONIC;
			numOfModes = 2; // only 2 modes in this scale
			numOfNotes = 8;
			break;
		case Scale::TypeOfScale::DOMINANT_DIMINISHED:
			scaleText ="DOMINANT_DIMINISHED";
			kindOfScale = Scale::KindOfScale::OCTATONIC;
			numOfModes = 1; // only 1 mode in this scale
			numOfNotes = 8;
			break;
		case Scale::TypeOfScale::DIMINISHED:
			scaleText ="DIMINISHED";
			kindOfScale = Scale::KindOfScale::OCTATONIC;
			numOfModes = 1; // only 1 mode in this scale
			numOfNotes = 8;
			break;
			// ---==== 7 NOTE scale's ====----
		case Scale::TypeOfScale::MAJOR:
			scaleText ="MAJOR";
			kindOfScale = Scale::KindOfScale::HEPTATONIC;
			numOfModes = 7; // 7 modes in this scale
			numOfNotes = 7; // Heptatonic = 7 notes.
			break;
		case Scale::TypeOfScale::MINOR:
			scaleText ="MINOR";
			kindOfScale = Scale::KindOfScale::HEPTATONIC;
			numOfModes = 7; // 7 modes in this scale
			numOfNotes = 7; // Heptatonic = 7 notes.
			break;
		case Scale::TypeOfScale::MELODIC_MINOR:
			scaleText ="MELODIC_MINOR";
			kindOfScale = Scale::KindOfScale::HEPTATONIC;
			numOfModes = 7; // 7 modes in this scale
			numOfNotes = 7; // Heptatonic = 7 notes.
			break;
		case Scale::TypeOfScale::HARMONIC_MINOR:
			scaleText ="HARMONIC_MINOR";
			kindOfScale = Scale::KindOfScale::HEPTATONIC;
			numOfModes = 7; // 7 modes in this scale
			numOfNotes = 7; // Heptatonic = 7 notes.
			break;
		case Scale::TypeOfScale::GYPSY:
			scaleText ="GYPSY";
			kindOfScale = Scale::KindOfScale::HEPTATONIC;
			numOfModes = 1; // only 1 mode in this scale
			numOfNotes = 7; // Heptatonic = 7 notes.
			break;
		case Scale::TypeOfScale::SYMETRICAL:
			scaleText ="SYMETRICAL";
			kindOfScale = Scale::KindOfScale::HEPTATONIC;
			numOfModes = 1; // only 1 mode in this scale
			numOfNotes = 7; // Heptatonic = 7 notes.
			break;
		case Scale::TypeOfScale::ENIGMATIC:
			scaleText ="ENIGMATIC";
			kindOfScale = Scale::KindOfScale::HEPTATONIC;
			numOfModes = 1; // only 1 mode in this scale
			numOfNotes = 7; // Heptatonic = 7 notes.
			break;
		case Scale::TypeOfScale::ARABIAN:
			scaleText ="ARABIAN";
			kindOfScale = Scale::KindOfScale::HEPTATONIC;
			numOfModes = 1; // only 1 mode in this scale
			numOfNotes = 7; // Heptatonic = 7 notes.
			break;
		case Scale::TypeOfScale::HUNGARIAN:
			scaleText ="HUNGARIAN";
			kindOfScale = Scale::KindOfScale::HEPTATONIC;
			numOfModes = 1; // only 1 mode in this scale
			numOfNotes = 7; // Heptatonic = 7 notes.
			break;
			// ---==== 6 NOTE scale's ====----
		case Scale::TypeOfScale::WHOLE_TONE:
			scaleText ="WHOLE_TONE";
			kindOfScale = Scale::KindOfScale::HEXATONIC;
			numOfModes = 1; // only 1 mode in this scale
			numOfNotes = 6; // Hexatonic 6 notes.
			break;
		case Scale::TypeOfScale::AUGMENTED:
			scaleText ="AUGMENTED";
			kindOfScale = Scale::KindOfScale::HEXATONIC;
			numOfModes = 2;
			numOfNotes = 6; // Hexatonic 6 notes.
			break;
		case Scale::TypeOfScale::BLUES_MAJOR:
			scaleText ="BLUES MAJOR";
			kindOfScale = Scale::KindOfScale::HEXATONIC;
			numOfModes = 1;
			numOfNotes = 6; // Hexatonic 6 notes.
			break;
		case Scale::TypeOfScale::BLUES_MINOR:
			scaleText ="BLUES_MINOR";
			kindOfScale = Scale::KindOfScale::HEXATONIC;
			numOfModes = 6;
			numOfNotes = 6; // Hexatonic 6 notes.
			break;
			// ---==== 5 NOTE scale's ====----
		case Scale::TypeOfScale::PENTATONIC:
			scaleText ="PENTATONIC";
			kindOfScale = Scale::KindOfScale::PENTATONIC;
			numOfModes = 1;
			numOfNotes = 5; // Hexatonic 6 notes.
			break;
		case Scale::TypeOfScale::MINOR_PENTATONIC:
			scaleText ="MINOR_PENTATONIC";
			kindOfScale = Scale::KindOfScale::PENTATONIC;
			numOfModes = 1;
			numOfNotes = 5; // Hexatonic 6 notes.
			break;
			// TODO: implement other type of scales.
		default:
			numOfModes = 0;
			numOfNotes = 0;
			break;
	}
	
	//	 Create (i) modes object in the vector
	//	 We give a pointer to ourselves 'this' as the mode
	//	 must know what kind of scale it is a mode of.
	for(unsigned int i = 0; i < numOfModes; i++) {
		Mode mode(this, i, numOfNotes, "mode" + std::to_string(i + 1));
		modes.push_back(mode);
	}
	
};


