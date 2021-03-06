#include "GenericStateMachine.h"
#include <stdlib.h>
#include <assert.h>


GenericStateMachine::GenericStateMachine(State_t * const initialState)
{
	this->initialState = initialState;
}

void GenericStateMachine::traverse(void)
{
	this->currentState = this->currentState->getNextState();
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