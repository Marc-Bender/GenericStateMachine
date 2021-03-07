#include "GenericStateMachine.h"
#include <stdlib.h>
#include <assert.h>


GenericStateMachine::GenericStateMachine(State_t * const initialState)
{
	this->initialState = initialState;
	this->currentState = initialState;
}

void GenericStateMachine::traverse(void)
{
	const State_t * const oldState = this->currentState;
	this->currentState = this->currentState->getNextState();
	if (oldState != this->currentState)
	{
		oldState->onExit();
		this->currentState->onEntry();
	}
	else
	{
		// no transition
	}

	this->currentState->_do();
}

void GenericStateMachine::reset(void)
{
	this->currentState = this->initialState;
}

State_t * const GenericStateMachine::getState(void)
{
	return this->currentState;
}

uint8_t State_t::getIdentifier(void)
{
	return this->identifier;
}