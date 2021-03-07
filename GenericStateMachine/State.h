#pragma once
#include <stdint.h>
#include <vector>
#include <stdbool.h>

typedef bool(*transitionConditionCheckerFunctionPtr)(void);
typedef void(*onEntryFunctionPtr)(void);
typedef void(*onExitFunctionPtr)(void);
typedef void(*doFunctionPtr)(void);
typedef void(*transitionActionFunctionPtr)(void);

class State_t
{
	private:
		uint8_t identifier;
		uint8_t numberOfNextStates;
		uint8_t numberOfAlreadyInsertedNextStates = 0;
		std::vector<State_t*> nextStates;
		std::vector<transitionConditionCheckerFunctionPtr> checkerFunctions;
	protected:
		friend class GenericStateMachine;
		onEntryFunctionPtr onEntry;
		onExitFunctionPtr onExit;
		doFunctionPtr _do;
	public:
		State_t(const uint8_t identifier, const uint8_t numberOfNextStates);
		~State_t(void);
		bool addNextState(State_t * const nextState, const transitionConditionCheckerFunctionPtr checkerFunction); // returns true if inserted, false if all possible next states are exhaused
		void setActions(const onEntryFunctionPtr onEntry, const onExitFunctionPtr onExit, const doFunctionPtr _do);
		State_t * getNextState(void);
		uint8_t getIdentifier(void);

};
