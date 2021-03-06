#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <vector>

#include "State.h"

class GenericStateMachine
{
	private:
		State_t * initialState;
		State_t * currentState;
	public:
		GenericStateMachine(State_t * const initialState);
		void traverse(void);
		void reset(void);
		State_t * const getState(void);
};

