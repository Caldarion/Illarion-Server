#ifndef CCONTAINERSTACK_HH
#define CCONTAINERSTACK_HH

#include <vector>
#include <iterator>

#include "CContainer.h"


//! eine Darstellung offener Container eines Spielers
class CContainerStack {
	public:
		//! Konstruktor
		CContainerStack();

		//! Copy-Konstruktor
		CContainerStack( const CContainerStack& source );

		//! Destruktor
		~CContainerStack();

		//! Zuweisungsoperator
		CContainerStack& operator =( const CContainerStack& source );

		//! den Start - CContainer zuweisen, in dem man arbeiten kann
		// \param cc der Zeiger auf den Startcontainer
		// \param carry gibt an, ob der Spieler diesen Container tr�gt
		void startContainer( CContainer* cc, bool carry );

		//! entfernt alle Zeiger auf CContainer aus der Datenstruktur
		void clear();

		//! einen neuen Zeiger auf CContainer hinzuf�gen
		//
		// \param cc der Zeiger auf den CContainer der ge�ffnet werden soll
		void openContainer( CContainer* cc );

		//! entfernt den zuletzt hinzugef�gten Zeiger auf CContainer
		// \return true, falls noch Zeiger auf CContainer vorhanden sind, false sonst
		bool closeContainer();

		//! pr�ft, ob ein Spieler die CContainer tr�gt
		// \return true, falls ein Spieler die CContainer tr�gt, false sonst
		bool inInventory();

		//! pr�ft, ob der �bergebene Zeiger auf CContainer der zuletzt hinzugef�gte ist
		// \param cc Zeiger auf CContainer der �berpr�ft werden soll
		// \return true, falls cc zuletzt hinzugef�gt wurde, false sonst
		bool isOnTop( CContainer* cc );

		//! liefert den zuletzt hinzugef�gten Zeiger auf CContainer zur�ck
		// \param cc Zeiger auf CContainer der �berpr�ft werden soll
		// \return NULL, falls kein Eintrag vorhanden
		CContainer* top();

		//! pr�ft, ob der �bergebene Zeiger in dem Stack ist
		// \param cc Zeiger auf CContainer der �berpr�ft werden soll
		// \return true, falls cc in dem Stack ist, false sonst
		bool contains( CContainer* cc );

		//! gibt an, ob ein Spieler die Container tr�gt
		bool inventory;

	private:
		//! definiert eine Template-Klasse "std::vector f�r Zeiger auf CContainer"
		typedef std::vector < CContainer* > CONTAINERVECTOR;

		//! ein std::vector von Zeigern auf CContainer
		CONTAINERVECTOR opencontainers;
};

#endif
