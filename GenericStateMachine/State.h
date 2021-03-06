#pragma once
#include <stdint.h>
#include <vector>
#include <stdbool.h>

typedef bool(*fptr)(void);

class State_t
{
	private:
		uint8_t identifier;
		uint8_t numberOfNextStates;
		uint8_t numberOfAlreadyInsertedNextStates=0;
		std::vector<State_t*> nextStates;
		std::vector<fptr> testerFunctions;
	public:
		State_t(const uint8_t identifier, const uint8_t numberOfNextStates);
		~State_t(void);
		bool addNextState(State_t * const nextState); // returns true if inserted, false if all possible next states are exhaused
		State_t * getNextState(void);
		uint8_t getIdentifier(void);
};
