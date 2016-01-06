#ifndef OBSERVER_H
#define OBSERVER_H

enum class GameEvent;

class Observer {
	public:
		virtual ~Observer() {}
		virtual void onNotify( GameEvent event ) = 0;
};

#endif
