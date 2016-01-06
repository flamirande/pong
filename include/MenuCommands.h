#ifndef MENU_COMMANDS_H
#define MENU_COMMANDS_H

#include "Command.h"
#include "GameState.h"
#include "PongGame.h"
#include "PongMenu.h"

class Window;

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

class NewGameCommand: public Command
{
        public:
                NewGameCommand( StateMachine* p_state_machine, Window* p_window ): p_state_machine_( p_state_machine ), p_window_( p_window ) { }
                ~NewGameCommand() { }
                void execute()
                {
			p_state_machine_->pop();
			p_state_machine_->push( std::shared_ptr<GameState>( new PongGame( p_window_, p_state_machine_ ) ) );
                }

        private:
                StateMachine* p_state_machine_;
		Window* p_window_;
};

class ReturnToMenuCommand: public Command
{
        public:
                ReturnToMenuCommand( StateMachine* p_state_machine, Window* p_window ): p_state_machine_( p_state_machine ), p_window_( p_window ) { }
                ~ReturnToMenuCommand() { }
                void execute()
                {
			p_state_machine_->pop();
			p_state_machine_->push( std::shared_ptr<GameState>( new PongMenu( p_window_, p_state_machine_ ) ) );
                }

        private:
                StateMachine* p_state_machine_;
		Window* p_window_;
};

#endif
