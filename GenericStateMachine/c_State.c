#include <stdbool.h>
#include "c_State.h"

State_t * State_getNextState(const State_t * const this)
{
	uint8_t i = 0;
	const uint8_t numberOfNextStates = this->numberOfNextStates;
	for (i; i < numberOfNextStates; i++)
	{
		transitionConditionCheckerFunctionPtr currentTesterFunction = *(this->checkerFunctions[i]);
		const bool result = currentTesterFunction();
		if (true == result)
		{
			break;
		}
		else
		{
			// try next state transition condition
		}
	}
	if (i == numberOfNextStates)
	{
		// no transition check successful
		// stay in state
		return (State_t * ) this;
	}
	else
	{
		return (State_t *) &(this->nextStates[i]);
	}
}
