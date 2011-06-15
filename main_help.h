#ifndef MAIN_HELP_H
#define MAIN_HELP_H

#include <signal.h>
#include <vector>

#include "globals.h"

class CWorld;

//! falls false beendet sich das Programm
extern volatile bool running;

// in diesen std::vector f�gen CFields die numbers der gel�schten containeritems ein,
// damit die zugeh�rige Map die containerinhalte l�schen kann
extern std::vector<int>* erasedcontainers;

// Koordinaten von gel�schten Containern, ben�tigt zum Schlie�en offener Showcases
extern std::vector<position>* contpos;

// some forward declarations to not include unecessary headers
class CPlayer;

void logout_save( CPlayer* who, bool forced, unsigned long int thistime );

void login_save( CPlayer* who );

//! Das Initialisieren von Logoptionen
void InitLogOptions();

//! Die Initialisierung des Servers mit Daten aus einer Datei
bool Init( const std::string& initfile);

//! zur Pr�fung der Kommandozeilenargumente
void checkArguments( int argc, char* argv[]);

//! setup file positions
bool setup_files();

// Itemdefinitionen laden //
void loadData();

//! initialise signal handlers
bool init_sighandlers();

//! reset signal handlers
void reset_sighandlers();

#endif
