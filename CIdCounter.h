#ifndef CIdCounter_HH
#define CIdCounter_HH

//falls nicht auskommentiert, werden mehr Bildschirmausgaben gemacht:
//#define CIdCounter_DEBUG

#include <string>
#include <fstream>
#include <iostream>

#include "types.h"

//! Ein Z�hler f�r bereits vergebene ID's
// Der Z�hlerstand wird in eine Datei gespeichert und bei
// Initialisierung wieder geladen.
class CIdCounter {
	public:
		//! Konstruktor
		// \param counterfile die Datei welche f�r die Speicherung der
		// zuletzt vergebenen ID genutzt wird
		CIdCounter( std::string counterfile );

		// create a new counter with the given starting ID
		CIdCounter(const std::string& counterfile, const TYPE_OF_CHARACTER_ID& startid);
		//! Destruktor
		~CIdCounter();

		//! liefert die n�chste freie ID zur�ck und h�lt diese als bereits verwendet fest
		// \return die n�chste freie ID
		TYPE_OF_CHARACTER_ID nextFreeId();

		//! setzt den Counter wieder auf 0 zur�ck
		// \return true falls Counter erfolgreich zur�ckgesetzt, false sonst
		bool reset();

		//! setzt den Counter
		// \param lastid die zuletzt vergebene ID
		// \return true falls Counter erfolgreich gesetzt, false sonst
		bool set( TYPE_OF_CHARACTER_ID lastid );

	private:
		//! der Name der Datei in dem die letzte bereits vergebene ID gespeichert ist
		std::string counterfile;

		//! die letzte bereits vergebene ID
		TYPE_OF_CHARACTER_ID counter;
};

#endif
