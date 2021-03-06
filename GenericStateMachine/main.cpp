#include <iostream>
#include "GenericStateMachine.h"

int main(void)
{
	typedef enum
	{
		STATE_IDLE,
		STATE_INIT,
		STATE_ERROR,
		STATE_OPERATION
	} STATE_ENUMERATOR;
	
	State_t state_idle = State_t(STATE_IDLE, 1);
	State_t state_init = State_t(STATE_INIT, 2);
	State_t state_error = State_t(STATE_ERROR, 0);
	State_t state_operation = State_t(STATE_OPERATION, 2);

	bool returnValuesAddNextState[5];
	returnValuesAddNextState[0] = state_idle.addNextState(&state_init);
	
	returnValuesAddNextState[1] = state_init.addNextState(&state_error);
	returnValuesAddNextState[2] = state_init.addNextState(&state_operation);
	
	returnValuesAddNextState[3] = state_operation.addNextState(&state_operation);
	returnValuesAddNextState[4] = state_operation.addNextState(&state_error);

	GenericStateMachine statemachine = GenericStateMachine(&state_idle);
	return 0;
}
