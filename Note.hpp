/** @file Note.hpp
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
#ifndef Notes_hpp
#define Notes_hpp

#include <string>


class Note {
public:
	Note() noexcept {
		number = 60;
	};
	Note(uint8_t midinote) noexcept {
		if(midinote < 128) {
			number = midinote;
		}
	};
	Note(int midinote) noexcept {
		if(midinote < 128) {
			number = (uint8_t) midinote;
		}
	};
	
	uint8_t number;	// MIDI note 7 bits 0 --> 127
	bool flats;
	/**
	 * Various ways of displaying the note.
	 */
	const std::string Text() {
		return Note::ToText(number, flats, false);
	};
	const std::string Name() {
		return Note::ToText(number, flats, true);
	};
	const std::string FlatsName() {
		return Note::ToText(number, true, true);
	};
	const std::string SharpsName() {
		return Note::ToText(number, false, true);
	};
	/** Simply convert MIDI notenumber to a note (either using flats or sharps
	 */
	static const std::string ToText(uint8_t midinote,
									bool flats,
									bool showoctave);
	/** Convert string to MIDI note number
	 */
	static const uint8_t ToNote(std::string str);
private:
};




#endif /* Notes_hpp */
