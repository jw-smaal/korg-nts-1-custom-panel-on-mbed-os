/** @file Chords.hpp
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
#ifndef Chords_hpp
#define Chords_hpp

#include <vector>
//#include "Harmony.hpp"
#include "Note.hpp"




/** Implementation of Chords
 *
 * TODO: The difficulty is that some chords do not make sense in a certain
 * TODO: scale and that the notes varies as wel...
 * TODO: chords act in various degrees of the scale too.
 *
 * TODO: Music is not a hard science that will always follow a certain
 * TODO: algorithm.  However we can at least try to caputure some of the
 * TODO: basics that will be able to implemented in multiple scales.
 */
class Chord {
public:
	uint8_t rootnote;
	uint8_t bassnote;
	enum class Type {
		MAJOR,
		MAJOR_6,
		MAJOR_7,
		MAJOR_9,
		MAJOR_7_SHARP11,
		MINOR,
		MINOR_6,
		MINOR_FLAT6,
		MINOR_7,
		MINOR_9,
		MINOR_MAJOR_7,
		DOMINANT_7,
		DOMINANT_7_FLAT5,
		DOMINANT_7_SHARP5,
		DOMINANT_7_SUS4,
		DOMINANT_7_FLAT9,
		DOMINANT_7_SHARP9,
		DOMINANT_7_SHARP5_FLAT9,
		DOMINANT_7_SHARP11,
		DOMINANT_7_ADD9_FLAT5,
		DOMINANT_7_ADD9_SHARP11,
		DOMINANT_7_ADD13,
		DOMINANT_7_SHARP9_FLAT13,
		DOMINANT_7_SHARP11_ADD13,
		DIMINISHED,			// Double check!
		DIMINISHED_7,		// Double check!
		MINOR_7_FLAT5,
		// TODO: implement !!!
		AUGMENTED,
		SUS4,
		SUS2
	};
	Chord::Type chordType;
	
	const std::vector<Chord::Type> allChordTypes =  {
		Type::MAJOR,
		Type::MAJOR_6,
		Type::MAJOR_7,
		Type::MAJOR_9,
		Type::MAJOR_7_SHARP11,
		Type::MINOR,
		Type::MINOR_6,
		Type::MINOR_FLAT6,
		Type::MINOR_7,
		Type::MINOR_9,
		Type::MINOR_MAJOR_7,
		Type::DOMINANT_7,
		Type::DOMINANT_7_FLAT5,
		Type::DOMINANT_7_SHARP5,
		Type::DOMINANT_7_SUS4,
		Type::DOMINANT_7_FLAT9,
		Type::DOMINANT_7_SHARP9,
		Type::DOMINANT_7_SHARP5_FLAT9,
		Type::DOMINANT_7_SHARP11,
		Type::DOMINANT_7_ADD9_FLAT5,
		Type::DOMINANT_7_ADD9_SHARP11,
		Type::DOMINANT_7_ADD13,
		Type::DOMINANT_7_SHARP9_FLAT13,
		Type::DOMINANT_7_SHARP11_ADD13,
		Type::DIMINISHED,
		Type::DIMINISHED_7,
		Type::MINOR_7_FLAT5,
		// TODO: implement!!!
		Type::AUGMENTED,
		Type::SUS4,
		Type::SUS2
	};
	
	// Constructor
	Chord(Chord::Type chordTypeArg,
		  uint8_t bassnoteArg,
		  uint8_t rootnoteArg )
	noexcept;
	
public:
	// Vector of notes of the chord.
	// when constructed it's in the root position.
	std::vector<Note> notes;
	
public:
	/*
	 * Intervals in ENGLISH with the DUTCH equivalent
	 */
	enum class Iv: unsigned int {
		// Whole and halfs
		H  = 1,     // Half step    (minor second)
		W  = 2,     // Whole step	(major second)
		WH = 3,     // Whole + Half	(minor third)
		WW = 4,     // Whole + Whole	(major third)
		WWH = 5,	// Whole + Whole + Half	(perfect fourth)
		WWW = 6,	// Whole + Whole + Whole	(tritonus)
		WWWH = 7, 	// Whole  + Whole + Whole + Half (perfect fifth)
		
		// English names
		PERFECT_UNISON  = 0,
		AUGMENTED_UNISON = 1,
		MINOR_SECOND = 1,
		MAJOR_SECOND = 2,
		AUGMENTED_SECOND = 3,
		MINOR_THIRD = 3,
		MAJOR_THIRD = 4,
		PERFECT_FOURTH = 5,
		TRITONE = 6,
		DIMINISHED_FIFTH = 6,
		PERFECT_FIFTH = 7,
		AUGMENTED_FIFTH = 8,
		MINOR_SIXTH = 8,
		MAJOR_SIXTH = 9,
		AUGMENTED_SIXTH = 10,
		MINOR_SEVENTH = 10,
		MAJOR_SEVENTH = 11,
		PERFECT_OCTAVE = 12,
		
		// Dutch names
		PRIME             =  0,
		KLEINE_SECUNDE    =  1,
		GROTE_SECUNDE     =  2,
		KLEINE_TERTS      =  3,
		GROTE_TERTS       =  4,
		REINE_KWART       =  5,
		OVERMATIGE_KWART   = 6,
		VERMINDERDE_KWINT  = 6,
		TRITONUS          =  6,
		REINE_KWINT       =  7,
		KLEINE_SEXT       =  8,
		GROTE_SEXT        =  9,
		KLEINE_SEPTIEM    = 10,
		GROTE_SEPTIEM     = 11,
		OCTAAF           =  12
	};
	
	// Constrants
	const std::vector<enum Iv> majorVect =
	//{Iv::WW, Iv::WH};
	{Iv::MAJOR_THIRD, Iv::MINOR_THIRD};
	const std::vector<enum Iv> major_6_Vect =
	{Iv::WW, Iv::WH, Iv::W};
	const std::vector<enum Iv> major_7_Vect =
	//{Iv::WW, Iv::WH, Iv::WW};
	{Iv::MAJOR_THIRD, Iv::MINOR_THIRD, Iv::MAJOR_THIRD};
	const std::vector<enum Iv> major_9_Vect =
	{Iv::WW, Iv::WH, Iv::WW ,Iv::WH};
	const std::vector<enum Iv> major_7_sharp11_Vect =
	{Iv::WW, Iv::WH, Iv::WW ,Iv::WH, Iv::WW};
	const std::vector<enum Iv> minorVect =
	//{Iv::WH, Iv::WW};
	{Iv::MINOR_THIRD, Iv::MAJOR_THIRD};
	const std::vector<enum Iv> minor_6_Vect =
	{Iv::WH, Iv::WW, Iv::W};
	const std::vector<enum Iv> minor_flat6_Vect =
	{Iv::WH, Iv::WW, Iv::H};
	const std::vector<enum Iv> minor_7_Vect =
	//{Iv::WH, Iv::WW, Iv::WH};
	{Iv::MINOR_THIRD, Iv::MAJOR_THIRD, Iv::MINOR_THIRD};
	const std::vector<enum Iv> minor_9_Vect =
	{Iv::WH, Iv::WW, Iv::WH, Iv::WW};
	const std::vector<enum Iv> minor_major_7_Vect =
	{Iv::WH, Iv::WW, Iv::WW};
	const std::vector<enum Iv> dominant_7_Vect =
	//{Iv::WW, Iv::WH, Iv::WH};
	{Iv::MAJOR_THIRD, Iv::MINOR_THIRD, Iv::MINOR_THIRD};
	const std::vector<enum Iv> dominant_flat5_Vect =
	{Iv::WW, Iv::W, Iv::WW};
	const std::vector<enum Iv> dominant_sharp5_Vect =
	{Iv::WW, Iv::WW, Iv::W};
	const std::vector<enum Iv> dominant_7_sus4 =
	{Iv::WWH, Iv::W, Iv::WH};
	const std::vector<enum Iv> dominant_7_flat9 =
	{Iv::WW, Iv::WH, Iv::WH, Iv::WH};
	const std::vector<enum Iv> dominant_7_sharp9 = \
	{Iv::WW, Iv::WH, Iv::WH, Iv::WWH};
	// As the intervals are getting larger using the Dutch intervals for
	// the definitions instead of wholes and halfs.
	const std::vector<enum Iv> dominant_7_sharp5_flat9 =
	{Iv::GROTE_TERTS, Iv::GROTE_TERTS, Iv::GROTE_SECUNDE, Iv::KLEINE_TERTS};
	const std::vector<enum Iv> dominant_7_sharp11 =
	{Iv::GROTE_TERTS, Iv::KLEINE_TERTS, Iv::KLEINE_TERTS, Iv::KLEINE_SEXT};
	const std::vector<enum Iv> dominant_7_add9_flat5 =
	{Iv::GROTE_TERTS, Iv::GROTE_SECUNDE, Iv::GROTE_TERTS, Iv::GROTE_TERTS};
	const std::vector<enum Iv> dominant_7_add9_sharp11 =
	{Iv::GROTE_TERTS, Iv::KLEINE_TERTS, Iv::KLEINE_TERTS,
		Iv::GROTE_TERTS, Iv::GROTE_TERTS};
	const std::vector<enum Iv> dominant_7_add13 =
	{Iv::GROTE_TERTS, Iv::KLEINE_TERTS, Iv::KLEINE_TERTS,
		Iv::GROTE_SEPTIEM};
	const std::vector<enum Iv> dominant_7_sharp9_flat13 =
	{Iv::GROTE_TERTS, Iv::KLEINE_TERTS, Iv::KLEINE_TERTS,
		Iv::REINE_KWART, Iv::REINE_KWART};
	const std::vector<enum Iv> dominant_7_sharp11_add13 =
	{Iv::GROTE_TERTS, Iv::KLEINE_TERTS, Iv::KLEINE_TERTS,
		Iv::KLEINE_SEXT, Iv::KLEINE_TERTS};
	const std::vector<enum Iv> diminished =
	{Iv::KLEINE_TERTS, Iv::KLEINE_TERTS};
	const std::vector<enum Iv> diminished_7 =
	{Iv::KLEINE_TERTS, Iv::KLEINE_TERTS, Iv::KLEINE_TERTS};
	const std::vector<enum Iv> minor_7_flat5 =
	{Iv::KLEINE_TERTS, Iv::KLEINE_TERTS, Iv::GROTE_TERTS};
	const std::vector<enum Iv> augmented =
	{Iv::GROTE_TERTS, Iv::GROTE_TERTS};
	const std::vector<enum Iv> sus4 =
	{Iv::REINE_KWART, Iv::GROTE_SECUNDE};
	const std::vector<enum Iv> sus2 =
	{Iv::GROTE_SECUNDE, Iv::REINE_KWART};
	// TODO: Finish the rest of the chords.
	
	// Lists of alternative Voicing.
public: enum class VoicingType {
	DROP1,
	DROP2,
	// TODO: work in progress
};
public:
	void setVoicing(Chord::VoicingType voicingTypeArg,
					bool dropRootDown);
public: std::vector<Note> voicing;
	
	// Text representation of the Chords.
private: std::string privText;
public: std::string Text() {
	return Note::ToText(rootnote, false, false) + " " + privText;
};
	
private: std::string shortPrivText;
public: std::string ShortText() {
	return Note::ToText(rootnote, false, false) + shortPrivText;
};
	// Vector describing the Chord Recipe.
	// assigned in constructor.
private: std::vector<enum Iv> chordVect;
};



#endif /* Chords_hpp */
