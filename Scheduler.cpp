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


#include "Scheduler.hpp"
#include <iostream>

//#define Scheduler_DEBUG

Scheduler::Scheduler(World * pworld) : cycle(0), world(pworld) {
#ifdef Scheduler_DEBUG
	std::cout<<"Scheduler Constructor Start \n";
#endif
	//Taskliste leeren;
	Tasks.clear();
#ifdef Scheduler_DEBUG
	std::cout<<"Scheduler Constructor Ende \n";
#endif
}

Scheduler::~Scheduler() {
	Tasks.clear();
}

void Scheduler::NextCycle() {
#ifdef Scheduler_DEBUG
	if( !Tasks.empty() )std::cout<<"Cycle anfang:"<<cycle<<" Liste front: "<<Tasks.front()->GetNextCycle()<<"\n";
	else std::cout<<"Cycle anfang:"<<cycle<<" Taskliste leer ";
#endif
	int emexit = 0;
	SchedulerObject * m_object;
	//Schleife solange emexit < 201, Der vorderste Task gr��er als der aktuelle Zyklus und die Taskliste nicht leer
	while ( !Tasks.empty() && ( emexit < 201 ) && ( Tasks.front()->GetNextCycle() <= cycle ) ) {
		//Notausstieg um Endlosschleife zu vermeiden
		m_object = NULL;
		++emexit;
		if (emexit>=199) {
			std::cout<<"Mehr als 199 Tasks zeitgeich ausgef�hrt. Ausf�hrung wird im n�chsten Zyklus fortgesetzt \n";
			break;
		}
		//Ende Notausstieg
#ifdef Scheduler_DEBUG
		std::cout<<"Notausstieg vorbei innerhalb Cycle Schleife\n";
#endif
		if (!Tasks.empty())m_object = Tasks.front(); //obersten Task in Zeiger schieben
#ifdef Scheduler_DEBUG
		std::cout<<"Nach m_object zuweisung\n";
#endif
		if (m_object!=NULL) {
#ifdef Scheduler_DEBUG
			std::cout<<" Task wird ausgef�hrt in Cycle:"<<cycle<<" Task ausf�hrung im Cycle: "<<m_object->GetNextCycle()<<"\n";
#endif
			if( (*m_object)(world) )AddTask(m_object); //Wenn ausf�hren der Funktion true dann Task erneut adden
		}
		Tasks.pop_front(); //Obersten Task l�schen
	}
	++cycle; //Zyklus um eins erh�hen
#ifdef Scheduler_DEBUG
	std::cout<<"Cycle ende \n";
#endif
}

void Scheduler::AddTask(SchedulerObject* sobject) {
#ifdef Scheduler_DEBUG
	std::cout<<"F�ge Task in den Scheduler ein erste ausf�hrung:"<<sobject->GetNextCycle()<<"\n";
#endif
	std::list<SchedulerObject*>::iterator it;
	bool inserted = false;
	if ( sobject->GetNextCycle() <= cycle) {
		//Verhindern das ein Task im aktuellen oder verg. Zyklus eingef�gt wird.
		sobject->SetNextCycle( cycle + 1 );
	}
	//Schleife der Tasks durchlaufen.
	for (it = Tasks.begin();it != Tasks.end(); ++it) {
		if( (*it)->GetNextCycle() > sobject->GetNextCycle() ) {
#ifdef Scheduler_DEBUG
			std::cout<<"Task einf�gen aktueller iterator: "<< (*it)->GetNextCycle() << " neues Objekt: "<< sobject->GetNextCycle() << "\n";
#endif
			//neuen Task vor aktuellen iterator einf�gen
			Tasks.insert( it, sobject );
			inserted = true;
#ifdef Scheduler_DEBUG
			std::cout<<"Task in der Liste eingef�gt!\n";
#endif
			break; //Schleife abbrechen wenn Task einmal eingef�gt wurde
		}
	}
	if (!inserted) {
		Tasks.push_back(sobject);
#ifdef Scheduler_DEBUG
		std::cout<<"Task am ende der Liste eingef�gt!\n";
#endif

	}
}
