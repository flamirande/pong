#ifndef PONG_COMMANDS_H
#define PONG_COMMANDS_H

#include "Command.h"
#include "Paddle.h"
#include "GameState.h"

class UpCommand : public Command
{
	public:
		UpCommand( Paddle* p_paddle ): p_paddle_( p_paddle ) { }
		~UpCommand() { }
		void execute() { p_paddle_->move_up(); }
	private:
		Paddle* p_paddle_;
};

class DownCommand : public Command
{
	public:
		DownCommand( Paddle* p_paddle ): p_paddle_( p_paddle ) { }
		~DownCommand() { }
		void execute() { p_paddle_->move_down(); }
	private:
		Paddle* p_paddle_;
};

class StopCommand: public Command
{
	public:
		StopCommand( Paddle* p_paddle ): p_paddle_( p_paddle ) { }
		~StopCommand() { }
		void execute() { p_paddle_->stop(); }
	private:
		Paddle* p_paddle_;
};

class QuitCommand: public Command
{
	public:
		QuitCommand( StateMachine* p_state_machine ): p_state_machine_( p_state_machine ) { }
		~QuitCommand() { }
		void execute()
		{
			//Empty the state machine, which will end the program
			while ( !p_state_machine_->empty() )
			{
				p_state_machine_->pop();
			}
		}

	private:
		StateMachine* p_state_machine_;
};

#endif
