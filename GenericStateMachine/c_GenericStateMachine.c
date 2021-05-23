#include "c_GenericStateMachine.h"
#include "c_State.h"
#include <stdint.h>

void GSM_traverse(GenericStateMachine * this)
{
	const State_t * const oldState = &(this->stateList[this->currentStateIndex]);
	const State_t * const currentState = State_getNextState(oldState);
	if (oldState != currentState)
	{
		oldState->onExit();
		currentState->onEntry();
	}
	else
	{
		// no transition
	}

	currentState->_do();
}

void GSM_reset(GenericStateMachine * this)
{
	this->currentStateIndex = this->initialStateIndex;
}

