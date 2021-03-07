#include <iostream>
#include <time.h>
#include "GenericStateMachine.h"

static uint8_t timeInState = 0;
static volatile bool initSuccessful = false;
static volatile bool fault = false;

bool tcf_idle2init(void)
{
	return true; // unconditional transition
}

bool tcf_init2error(void)
{
	static const uint8_t timeout = 30;
	if (timeInState > timeout)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool tcf_init2operation(void)
{
	if (initSuccessful == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool tcf_operation2error(void)
{
	if (fault == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void dummy(void)
{

}

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
	State_t state_operation = State_t(STATE_OPERATION, 1);

	bool returnValuesAddNextState[4];
	returnValuesAddNextState[0] = state_idle.addNextState(&state_init, &tcf_idle2init);
	
	returnValuesAddNextState[1] = state_init.addNextState(&state_error, &tcf_init2error);
	returnValuesAddNextState[2] = state_init.addNextState(&state_operation, &tcf_init2operation);
	
	returnValuesAddNextState[3] = state_operation.addNextState(&state_error, &tcf_operation2error);
	
	state_idle.setActions(&dummy, &dummy, &dummy);
	state_init.setActions(&dummy, &dummy, &dummy);
	state_error.setActions(&dummy, &dummy, &dummy);
	state_operation.setActions(&dummy, &dummy, &dummy);

	GenericStateMachine statemachine = GenericStateMachine(&state_idle);
	time_t lastTickAt = time(NULL);

	while (true)
	{
		time_t currentTime = time(NULL);
		statemachine.traverse();
		if  (
					(difftime(currentTime, lastTickAt) > 1)
				&&	(statemachine.getState()->getIdentifier() == (uint8_t)STATE_INIT)
			)
		{
			timeInState++;
			lastTickAt = currentTime;
		} 
	}

	return 0;
}
