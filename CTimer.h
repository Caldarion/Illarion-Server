#ifndef CTIMER_HH
#define CTIMER_HH

#include <ctime>

//! Timer f�r Sekundenabst�nde
class CTimer {

	public:

		//! Konstruktor
		// \param timegap Anzahl der Sekunden zwischen zwei Timer-Ereignissen
		CTimer( unsigned long int timegap );

		//! Destruktor
		~CTimer();

		//! pr�ft, ob schon gen�gend Zeit seit dem letzten Timer-Ereignis
		// (bzw. dem Konstruktor) vergangen ist
		// \return true, falls das n�chste Ereignis anliegt, false sonst
		bool next();

	private:

		//! Zeitpunkt der letzten Alterung (Anzahl der Sekunden seit 1.1.1970)
		time_t last;     //(32 Bit Integer)

		//! Anzahl der Sekunden zwischen den Schritten
		long gap;

		//! Sekunden seit dem letzten Ereignis
		long realgap;
};
#endif

