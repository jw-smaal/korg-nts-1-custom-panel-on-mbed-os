/** @file Harmony.cpp
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
#include "Harmony.hpp"
#include "Mode.hpp"


// Given a scale find the first, third and fifth note of that scale in
// each mode.

// First select the mode
// then iterate over the notes.


ChordProgression::ChordProgression
 (
	Scale &scl,
	unsigned int modenum,
	Type progType )
: scale(scl), fullrangemode(scl.modes[modenum])
{
	 Mode mode = scale.modes[modenum];
	
#ifndef TARGET_LIKE_MBED
	 std::cout << "ChordProgression::"
				<< scale.Text()
				<< "|" << mode.Name() << "|"
				<< std::endl;
#endif
	
	 // We need to add another octave to the modes of this scale
	std::vector<Note> secondoctave;
	for(Note note: mode.notes) {
		 Note note2{note.number + 12};	//	octave is 12 semi-tones.
		 secondoctave.push_back(note2);
	 }
	 // append the vector we just created to the existing mode.
	 mode.notes.insert(mode.notes.end(),
					   secondoctave.begin(),
					   secondoctave.end());
	
	 // What mode to choose?  
	 switch(progType) {
		 case Type::II_V_I:
#ifndef TARGET_LIKE_MBED
			 std::cout << "II V I progression" << std::endl;
			 std::cout << "|"
			 << mode.notes[Offset::II + 0].Name() << "|"
			 << mode.notes[Offset::II + Offset::III].Name() << "|"
			 << mode.notes[Offset::II + Offset::V].Name() << "|"
			 << mode.notes[Offset::II + Offset::VII].Name() << std::endl;
			 
			 // In order to do these progressions we need
			 // to have two octaves at least in the scale.
			 std::cout << "|"
			 << mode.notes[Offset::V + 0].Name() << "|"
			 << mode.notes[Offset::V + Offset::III].Name() << "|"
			 << mode.notes[Offset::V + Offset::V].Name() << "|"
			 << mode.notes[Offset::V + Offset::VII].Name() << std::endl;
			 
			 std::cout << "|"
			 << mode.notes[Offset::I + 0].Name() << "|"
			 << mode.notes[Offset::I + Offset::III].Name() << "|"
			 << mode.notes[Offset::I + Offset::V].Name() << "|"
			 << mode.notes[Offset::I + Offset::VII].Name() << std::endl;
#endif
			 break;
		 case Type::V_of_V:
			 break;
		 case Type::I_VI_II_V:
			 break;
		 case Type::III_VI_II_V:
			 break;
		 case Type::I_II_III_IV:
			 break;
		 default:
			 break;
	 };
	 
	// Find the lowest note number in the scale mode used
	// e.g. for a D major scale C# is the lowest note in the octave.
	// This can be found by substracting 12 (an octave) from
	// every note in the scale mode and making sure it's higher than 0.
	for(Note note: mode.notes) {
	//	int j = (unsigned int)note.number % 12;
	//	std::cout << "[" << j << "](" << (unsigned int) note.number;
		note.number = (unsigned int)note.number % 12;
	//	std::cout << "[" << j << "]"<< note.Name() << ".";
	}
	
	mode.Order(Mode::NoteOrder::LOW_TO_HIGH);
#ifndef TARGET_LIKE_MBED
	for(Note note: mode.notes) {
		std::cout << note.Text()
		<< "(" << (unsigned int) note.number  << ").";
	}
	std::cout << std::endl;
#endif 	

 };

	
/* EOF */
