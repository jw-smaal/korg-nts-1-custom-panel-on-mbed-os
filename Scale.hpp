/** @file Scale.hpp
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
#ifndef Scale_hpp
#define Scale_hpp

#include <vector>
#include <array>
#include <deque>


#include "Mode.hpp"
//#include "Harmony.hpp"



class Scale {
public:
	enum class KindOfScale {	// How many notes.
		CHROMATIC,		// 12
		PENTATONIC,		// 5
		HEXATONIC,		// 6
		HEPTATONIC,		// 7
		OCTATONIC,		// 8
	};
	enum KindOfScale kindOfScale;
	
	enum class TypeOfScale: int {
		CHROMATIC,
		OCTATONIC,
		DOMINANT_DIMINISHED,
		DIMINISHED,
		MAJOR,
		MINOR,
		MELODIC_MINOR,
		HARMONIC_MINOR,
		GYPSY,
		SYMETRICAL,
		ENIGMATIC,
		ARABIAN,
		HUNGARIAN,
		WHOLE_TONE,
		AUGMENTED,
		BLUES_MAJOR,
		BLUES_MINOR,
		PENTATONIC,
		MINOR_PENTATONIC
	};
	enum TypeOfScale typeOfScale;
	
	// This is just to facilitate some iterations
	const std::vector<TypeOfScale> allScaleKinds = {
		TypeOfScale::CHROMATIC,
		TypeOfScale::OCTATONIC,
		TypeOfScale::DOMINANT_DIMINISHED,
		TypeOfScale::DIMINISHED,
		TypeOfScale::MAJOR,
		TypeOfScale::MINOR,
		TypeOfScale::MELODIC_MINOR,
		TypeOfScale::HARMONIC_MINOR,
		TypeOfScale::GYPSY,
		TypeOfScale::SYMETRICAL,
		TypeOfScale::ENIGMATIC,
		TypeOfScale::ARABIAN,
		TypeOfScale::HUNGARIAN,
		TypeOfScale::WHOLE_TONE,
		TypeOfScale::AUGMENTED,
		TypeOfScale::BLUES_MAJOR,
		TypeOfScale::BLUES_MINOR,
		TypeOfScale::PENTATONIC,
		TypeOfScale::MINOR_PENTATONIC
	};
	
public:
	// Constructors
	Scale() noexcept;
	Scale(TypeOfScale typeOfScaleArg,
		  uint8_t rootNoteArg) noexcept;
	
	unsigned int rootNote;
	unsigned int numOfNotes;
	std::vector<Mode> modes;
	unsigned int numOfModes;
	
	const std::string Text() {
		return "Scale::TypeOfScale::" + scaleText;
	}
	enum class Iv { // Interval
		H  = 1,     // Half step
		W  = 2,     // Whole step
		WH = 3,     // Whole + Half
		WW = 4      // Whole + Whole
	};
private:
	// We don't want Scale to be copied untill we
	// implement a deep copy.
	Scale(const Scale&);
	Scale& operator=(const Scale&);
	
	//
	std::string scaleText;
};


/*
 * TODO: work in progress
 * TODO: see if we can rid of the c style arrays in the
 * TODO: scale definitions.
 */
class NewScale {
public:
	NewScale() noexcept;
	//~MajorScale() noexcept;
	//  std::vector<Mode> modes;
	//  unsigned int numOfModes;
	//  unsigned int numOfNotes;
private:
	/*
	 * MAJOR Scale modes  7 notes
	 */
	enum interVal {	// Private member scope
		H = 1,
		W = 2,
		WH = 3,
		WW = 4
	};
	const uint8_t major_s[7][7]  = {
		{W,W,H,W,W,W,H}, // IONIAN
		{W,H,W,W,W,H,W}, // DORIAN
		{H,W,W,W,H,W,W}, // PHRYGIAN
		{W,W,W,H,W,W,H}, // LYDIAN
		{W,W,H,W,W,H,W}, // MIXOLYDIAN
		{W,H,W,W,H,W,W}, // AEOLIAN
		{H,W,W,H,W,W,W}  // LOCRIAN
	};
	enum class Iv: unsigned int { // Interval
		H  = 1,     // Half step
		W  = 2,     // Whole step
		WH = 3,     // Whole + Half
		WW = 4      // Whole + Whole
	};
	const std::vector<std::array<enum Iv, 7>> majorScaleVect = { {
		{Iv::W, Iv::W, Iv::H, Iv::W, Iv::W, Iv::W, Iv::H}, // IONIAN
		{Iv::W, Iv::H, Iv::W, Iv::W, Iv::W, Iv::H, Iv::W}, // DORIAN
		{Iv::H, Iv::W, Iv::W, Iv::W, Iv::H, Iv::W, Iv::W}, // PHRYGIAN
		{Iv::W, Iv::W, Iv::W, Iv::H, Iv::W, Iv::W, Iv::H}, // LYDIAN
		{Iv::W, Iv::W, Iv::H, Iv::W, Iv::W, Iv::H, Iv::W}, // MIXOLYDIAN
		{Iv::W, Iv::H, Iv::W, Iv::W, Iv::H, Iv::W, Iv::W}, // AEOLIAN
		{Iv::H, Iv::W, Iv::W, Iv::H, Iv::W, Iv::W, Iv::W}  // LOCRIAN
	} };
	
	
	// Just playing around below with ADT's.
	// Best way to describe a list of bits?
	std::deque<bool> myBitstr = {
		1,0,1,1,0,1,1,1,
		1,0,0,0,0,1,1,0,
		1,0,0,0,0,1
	};
	std::deque<bool> myBitstr2 = {
		true, false, true, true, false, true, true, true
	};
	std::array<std::string, 4> arr = {
		{"the", "quick", "brown", "fox"}
	};
	std::array<std::array<int, 3>, 3> twodim = {
		{
			{5, 8, 2},
			{8, 3, 1},
			{5, 3, 9}
		}
	};
	std::array<std::array<int, 3>, 2> twodim2 = {
		{ // 2
			{5, 8, 2},   // 3
			{8, 3, 1}
		}
	};
	
};



#endif /* Scale_hpp */
