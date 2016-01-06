#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>
#include "Observer.h"

enum class GameEvent;

class Subject
{
	public:
		void addObserver( Observer* observer )
		{
			observers_.push_back( observer );
		}

		void removeObserver( Observer* observer )
		{
			observers_.remove( observer );
		}

		void notify( GameEvent event )
		{
			for ( std::list<Observer*>::iterator it = observers_.begin(); it != observers_.end(); ++it )
			{
				(*it)->onNotify( event );
			}
		}
		
	private:
		std::list<Observer*> observers_;
};

#endif
