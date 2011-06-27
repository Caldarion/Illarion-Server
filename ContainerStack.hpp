//  illarionserver - server for the game Illarion
//  Copyright 2011 Illarion e.V.
//
//  This file is part of illarionserver.
//
//  illarionserver is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  illarionserver is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with illarionserver.  If not, see <http://www.gnu.org/licenses/>.


#ifndef CONTAINERSTACK_HH
#define CONTAINERSTACK_HH

#include <vector>
#include <iterator>

#include "Container.hpp"


//! eine Darstellung offener Container eines Spielers
class ContainerStack {
	public:
		//! Konstruktor
		ContainerStack();

		//! Copy-Konstruktor
		ContainerStack( const ContainerStack& source );

		//! Destruktor
		~ContainerStack();

		//! Zuweisungsoperator
		ContainerStack& operator =( const ContainerStack& source );

		//! den Start - Container zuweisen, in dem man arbeiten kann
		// \param cc der Zeiger auf den Startcontainer
		// \param carry gibt an, ob der Spieler diesen Container tr�gt
		void startContainer( Container* cc, bool carry );

		//! entfernt alle Zeiger auf Container aus der Datenstruktur
		void clear();

		//! einen neuen Zeiger auf Container hinzuf�gen
		//
		// \param cc der Zeiger auf den Container der ge�ffnet werden soll
		void openContainer( Container* cc );

		//! entfernt den zuletzt hinzugef�gten Zeiger auf Container
		// \return true, falls noch Zeiger auf Container vorhanden sind, false sonst
		bool closeContainer();

		//! pr�ft, ob ein Spieler die Container tr�gt
		// \return true, falls ein Spieler die Container tr�gt, false sonst
		bool inInventory();

		//! pr�ft, ob der �bergebene Zeiger auf Container der zuletzt hinzugef�gte ist
		// \param cc Zeiger auf Container der �berpr�ft werden soll
		// \return true, falls cc zuletzt hinzugef�gt wurde, false sonst
		bool isOnTop( Container* cc );

		//! liefert den zuletzt hinzugef�gten Zeiger auf Container zur�ck
		// \param cc Zeiger auf Container der �berpr�ft werden soll
		// \return NULL, falls kein Eintrag vorhanden
		Container* top();

		//! pr�ft, ob der �bergebene Zeiger in dem Stack ist
		// \param cc Zeiger auf Container der �berpr�ft werden soll
		// \return true, falls cc in dem Stack ist, false sonst
		bool contains( Container* cc );

		//! gibt an, ob ein Spieler die Container tr�gt
		bool inventory;

	private:
		//! definiert eine Template-Klasse "std::vector f�r Zeiger auf Container"
		typedef std::vector < Container* > ONTAINERVECTOR;

		//! ein std::vector von Zeigern auf Container
		ONTAINERVECTOR opencontainers;
};

#endif
