#ifndef STATE_H
#define STATE_H
#include <stdint.h>
#include <stdbool.h>

	typedef bool(*transitionConditionCheckerFunctionPtr)(void);
	typedef void(*onEntryFunctionPtr)(void);
	typedef void(*onExitFunctionPtr)(void);
	typedef void(*doFunctionPtr)(void);
	typedef void(*transitionActionFunctionPtr)(void);

	typedef struct State_s
	{
			const uint8_t numberOfNextStates;
			const struct State_s * const nextStates;
			const transitionConditionCheckerFunctionPtr * const checkerFunctions;
			const onEntryFunctionPtr onEntry;
			const onExitFunctionPtr onExit;
			const doFunctionPtr _do;
	} State_t;

	State_t * State_getNextState(const State_t * const this);
#endif
