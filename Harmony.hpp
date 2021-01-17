/** @file Harmony.hpp
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
#ifndef Harmony_hpp
#define Harmony_hpp

//#include <stdio.h>
//#include <iostream>

// This is the top level include file for the following Class implementations
#include "Chord.hpp"
#include "Note.hpp"
#include "Mode.hpp"
#include "Scale.hpp"


/*
 * ChordProgression only makes sense if we know
 * the scale that we are using.
 * Otherwise we need to expand way to much down here
 * to find all the chord qualities based on the progression
 * mode and scale used. Therefore the constructor of the progression
 * requires a reference to a scale. 
 */
class ChordProgression {
public:
	enum Offset: int {
		// Computers start counting at 0 not 1.
		I = 0,
		II = 1,
		III = 2,
		IV = 3,
		V  = 4,
		VI = 5,
		VII = 6,
		VIII = 7,
	};
	enum class Type: int{
		II_V_I,
		V_of_V,
		I_VI_II_V,
		III_VI_II_V,
		I_II_III_IV
	};
	ChordProgression(Scale &scl,
					 unsigned int modenum, 
					 Type progType);
	Mode fullrangemode;
private:
	std::vector<Chord> chords;
	Scale &scale;
};


#endif /* Harmony_hpp */
/* EOF */
