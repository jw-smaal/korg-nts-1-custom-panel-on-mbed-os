/** @file Mode.hpp
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
#ifndef Mode_hpp
#define Mode_hpp

#include <vector>
#include <array>

#include "Note.hpp"
//#include "Harmony.hpp"


class Mode {
public:
	Mode(class Scale *scaleParent,
		 unsigned int modeNumArg,
		 unsigned long numOfNotesArg,
		 std::string modeNameArg) noexcept;
	unsigned int modeNum;
	unsigned long numOfNotes;

#ifndef TARGET_LIKE_MBED
	enum class NoteOrder : int {
		LOW_TO_HIGH,
		HIGH_TO_LOW,
		RANDOM
	};
#else
	// <random> causes code to be too large for the MCU
	// that is why we leave that option out.
	enum class NoteOrder : int {
		LOW_TO_HIGH,
		HIGH_TO_LOW
	};
#endif
	void Order(NoteOrder noteOrderArg);
	
	const std::string Name(){
		return privName;
	}
	const std::string Text() {
		return "Mode::" + privName;
	}
	
	std::vector<Note> notes;
	unsigned long NumOfNotes() {
		return notes.size();
	};
private:
	std::string privName;
	
	// Used to sort notes e.g.
	// sort(notes.begin(), notes.end(), Mode::CompareInterval);
	static bool privLowToHigh(Note note1, Note note2) {
		return (note1.number < note2.number);
	};
	static bool privHighToLow(Note note1, Note note2) {
		return (note1.number > note2.number);
	};
private:
	/*
	 * Scales are listed below as arrays of
	 * uint8_t indicating the either a 1/2 step as 1
	 * or a whole step as 2.
	 * minor 3'rd as 3
	 */
	// -----------------------------------------------------------------------
	enum interVal {
		H = 1,
		W = 2,
		WH = 3,
		WW = 4,
		I2H = 2,
		I3H = 3,
		I2W = 4
	};
	
	/*
	 * CHROMATIC Scale 12 note
	 */
	const uint8_t  chromatic[12]  = {
		H,H,H,H,H,H,H,H,H,H,H,H,
	};
	
	/*
	 * OCTATONIC 8 notes (of course)
	 */
	const uint8_t  octatonic[2][8]  = {
		{H,W,H,W,H,W,H,W},
		{W,H,W,H,W,H,W,H}
	};
	
	/*
	 * Dominant Diminished (Dom13, b9,#9, b5)   8 note scale
	 * same as "first mode of OCTATONIC" see above
	 */
	const uint8_t  dominant_diminished[8]  = {
		H,W,H,W,H,W,H,W
	};
	
	/*
	 * Diminished (Dim7, Maj/b9)  8 note scale
	 * same as "second mode of OCTATONIC" see above
	 */
	const uint8_t  diminished[8]  = {
		W,H,W,H,W,H,W,H
	};
	
	
	/*
	 * HEPTATONIC scales used by the
	 * majority of western music
	 */
	
	/*
	 * MAJOR Scale modes  7 notes
	 */
	/*
	 * For ATMEL AVR implementations.
	 * Be aware when putting these things in PROGMEM
	 * we need a MACRO to access them e.g. like below
	 * uint8_t (*scale)[7] = pgm_read_ptr(&major[0]);
	 */
	const uint8_t major_s[7][7]  = {
		{W,W,H,W,W,W,H}, // IONIAN   	: Happy
		{W,H,W,W,W,H,W}, // DORIAN		: Jazzy,
		{H,W,W,W,H,W,W}, // PHRYGIAN	: Exotic, latin
		{W,W,W,H,W,W,H}, // LYDIAN		: Hopefull
		{W,W,H,W,W,H,W}, // MIXOLYDIAN	: Positive
		{W,H,W,W,H,W,W}, // AEOLIAN		: Sad
		{H,W,W,H,W,W,W}  // LOCRIAN		:
	};
	
	/*
	 * MINOR Scale modes  7 notes
	 */
	const uint8_t  minor_s[7][7]  = {
		{W,H,W,W,H,W,W}, // AEOLIAN		: Sad
		{H,W,W,H,W,W,W}, // LOCRIAN
		{W,W,H,W,W,W,H}, // IONIAN		: Happy
		{W,H,W,W,W,H,W}, // DORIAN		: Jazzy,
		{H,W,W,W,H,W,W}, // PHRYGIAN
		{W,W,W,H,W,W,H}, // LYDIAN
		{W,W,H,W,W,H,W}  // MIXOLYDIAN
	};
	
	/*
	 * MELODIC MINOR Scale modes  7 notes
	 */
	const uint8_t  melodic_minor[7][7]  = {
		{W,H,W,W,W,W,H}, // Melodic minor     (minor major7)
		{H,W,W,W,W,H,W}, // DORIAN bW         (minor7 sus4 b9)
		{W,W,W,W,H,W,H}, // LYDIAN augmented  (major7 #4 #5)
		{W,W,W,H,W,H,W}, // MIXOLYDIAN #HH    (dominant7 b5)
		{W,W,H,W,H,W,W}, // MIXOLYDIAN b6     (dominant7 b6)
		{W,H,W,H,W,W,W}, // LOCRIAN natural 9 (minor9 b6)
		{H,W,H,W,W,W,W}  // Altered Dominant  (dominant7, #9, b5, #5)
	};
	
	/*
	 * HARMONIC MINOR Scale modes  7 notes
	 */
	const uint8_t  harmonic_minor[7][7]  = {
		{W,H,W,W,H,WH,H}, // Harmonic minor    (minor major7)
		{H,W,W,H,WH,H,W}, // LOCRIAN Nat.6     (minor7 b5)
		{W,W,H,WH,H,W,H}, // IONIAN Augmented  (major7 sus4, #5)
		{W,H,WH,H,W,H,W}, // DORIAN #HH        (minor7 #HH)
		{H,WH,H,W,H,W,W}, // PHRYGIAN major    (dominant7 sus4, b9, #5
		{WH,H,W,H,W,W,H}, // LYDIAN #9         (major7 #9,#HH)
		{H,W,H,W,W,H,WH} // ALTERED DOM bb7   (dim7)
	};
	
	/*
	 * Gypsy scale
	 */
	const uint8_t  gypsy[7]   = 	{
		W,H,WH,H,H,WH,H
	};
	
	
	/*
	 * Symetrical scale
	 */
	const uint8_t  symetrical[7]  = {
		H,W,W,WH,H,H,W
	};
	
	/*
	 * Enigmatic scale
	 */
	const uint8_t  enigmatic[7]  = {
		H,WH,W,W,W,H,H
	};
	
	/*
	 * Arabian scale
	 */
	const uint8_t  arabian[7]  = {
		W,W,H,H,W,W,W
	};
	
	/*
	 * Hungarian scale
	 */
	const uint8_t  hungarian[7]  = {
		WH,H,W,H,W,H,W
	};
	
	/*
	 * Whole tone (Dom7 #5, b6)   6 note scale
	 */
	const uint8_t  whole_tone[6]  = {
		W,W,W,W,W,W
	};
	//  uint8_t *hexatonic  = whole_tone;
	
	
	/*
	 * Augmented (Aug)   6 note scale
	 * (two modes? how does one call this second one then)
	 */
	const uint8_t  augmented[2][6]  = {
		{WH,H,WH,H,WH,H},
		{H,WH,H,WH,H,WH}	//	 Augmented inverse ?
	};
	
	/*
	 * Blues major  6 note scale
	 */
	const uint8_t  blues_major[6]  = {
		W,H,H,WH,W,WH
	};
	
	/*
	 * Blues minor  6 note scale
	 * not sure if these are called "modes"
	 */
	const uint8_t  blues_minor[6][6]  = {
		{WH,W,H,H,WH,W},
		{W,H,H,WH,W,WH},      // Same as blues major scale
		{H,H,WH,W,WH,W},
		{H,WH,W,WH,W,H},
		{WH,W,WH,W,H,H},
		{W,WH,W,H,H,WH}
	};
	
	/*
	 * Major Pentatonic  5 note scale
	 */
	const uint8_t  pentatonic[5]  = {
		W,W,WH,W,WH
	};
	
	/*
	 * Minor Pentatonic  5 note scale
	 */
	const uint8_t  minor_pentatonic[5]  = {
		WH,W,W,WH,W
	};
	
	// TODO: implement scales below
	/*
	 * "In scale" scale
	 */
	const uint8_t in_scale[5] = {
		H,I2W,W,H,I2W
	};
	
	/*
	 * "Insen" scale
	 */
	const uint8_t insen[5] = {
		H,I2W,W,I2W,W
	};
	
	/*
	 * Hirajoshi scale
	 */
	const uint8_t hirajoshi[5] = {
		I2W,W,H,I2W,H
	};
	
	/*
	 * Iwato scale
	 */
	const uint8_t iwato[5] = {
		H,I2W,H,I2W,W
	};
	
	/*
	 * Yo scale
	 */
	const uint8_t yo[5] = {
		I3H,W,W,I3H,W
	};
	
	// -----------------------------------------------------------------------
private:
#ifndef TARGET_LIKE_MBED
	/*
	 * Scales definition in intervals.
	 * TODO: work in progress
	 * TODO: getting rid of the c style arrays.
	 */
	// -----------------------------------------------------------------------
	enum class Iv: unsigned int { // Interval
		H  = 1,     // Half step
		W  = 2,     // Whole step
		WH = 3,     // Whole + Half
		WW = 4,      // Whole + Whole
		I3H = 3
		
	};
	/*
	 * MAJOR Scale modes  7 notes
	 */
	const std::vector<std::array<enum Iv, 7>> majorScaleVect = { {
		{Iv::W, Iv::W, Iv::H, Iv::W, Iv::W, Iv::W, Iv::H}, // IONIAN
		{Iv::W, Iv::H, Iv::W, Iv::W, Iv::W, Iv::H, Iv::W}, // DORIAN
		{Iv::H, Iv::W, Iv::W, Iv::W, Iv::H, Iv::W, Iv::W}, // PHRYGIAN
		{Iv::W, Iv::W, Iv::W, Iv::H, Iv::W, Iv::W, Iv::H}, // LYDIAN
		{Iv::W, Iv::W, Iv::H, Iv::W, Iv::W, Iv::H, Iv::W}, // MIXOLYDIAN
		{Iv::W, Iv::H, Iv::W, Iv::W, Iv::H, Iv::W, Iv::W}, // AEOLIAN
		{Iv::H, Iv::W, Iv::W, Iv::H, Iv::W, Iv::W, Iv::W}  // LOCRIAN
	} };
	
	/*
	 * MINOR Scale modes  7 notes
	 */
	const std::vector<std::array<enum Iv, 7>> minorScaleVect  = { {
		{Iv::W, Iv::H, Iv::W, Iv::W, Iv::H, Iv::W, Iv::W}, 	// AEOLIAN
		{Iv::H, Iv::W, Iv::W, Iv::H, Iv::W, Iv::W, Iv::W}, 	// LOCRIAN
		{Iv::W, Iv::W, Iv::H, Iv::W, Iv::W, Iv::W, Iv::H}, 	// IONIAN
		{Iv::W, Iv::H, Iv::W, Iv::W, Iv::W, Iv::H, Iv::W}, 	// DORIAN
		{Iv::H, Iv::W, Iv::W, Iv::W, Iv::H, Iv::W, Iv::W}, 	// PHRYGIAN
		{Iv::W, Iv::W, Iv::W, Iv::H, Iv::W, Iv::W, Iv::H},	// LYDIAN
		{Iv::W, Iv::W, Iv::H, Iv::W, Iv::W, Iv::H, Iv::W}	// MIXOLYDIAN
	} };
#endif 
};



#endif /* Mode_hpp */
