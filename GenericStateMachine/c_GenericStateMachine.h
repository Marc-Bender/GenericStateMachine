#include <stdint.h>
#include <stdbool.h>

#include "c_State.h"

typedef struct 
{
	uint8_t currentStateIndex;
	const uint8_t initialStateIndex;
	State_t * const stateList;
} GenericStateMachine;

void GSM_traverse(GenericStateMachine * this); // steps the state machine one step further
void GSM_reset(GenericStateMachine * this); // resets the state machine to its initial state

