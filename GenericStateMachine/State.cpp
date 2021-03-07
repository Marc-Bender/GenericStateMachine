#include <assert.h>
#include <vector>
#include <stdbool.h>

#include "State.h"

bool dummyTester(void)
{
	return false;
}

State_t::State_t(const uint8_t identifier, const uint8_t numberOfNextStates)
{
	this->identifier = identifier;
	this->numberOfNextStates = numberOfNextStates;
	this->nextStates.reserve(sizeof(State_t*) * numberOfNextStates);
	this->checkerFunctions.reserve(sizeof(&dummyTester) * numberOfNextStates);
}

State_t::~State_t(void)
{
	this->nextStates.~vector();
	this->checkerFunctions.~vector();
}

bool State_t::addNextState(State_t * const nextState, const transitionConditionCheckerFunctionPtr transitionCheckerFunction)
{
	bool returnValue = false;
	assert((nextState != NULL)&&(transitionCheckerFunction != NULL));
	if (this->numberOfAlreadyInsertedNextStates < this->numberOfNextStates)
	{
		this->nextStates.push_back(nextState);
		this->numberOfAlreadyInsertedNextStates++;
		this->checkerFunctions.push_back(transitionCheckerFunction);

		returnValue = true;
	}
	else
	{
		// can not insert
		returnValue = false;
	}
	return returnValue;
}

void State_t::setActions(const onEntryFunctionPtr onEntry, const onExitFunctionPtr onExit, const doFunctionPtr _do)
{
	this->onEntry = onEntry;
	this->onExit = onExit;
	this->_do = _do;
}

State_t * State_t::getNextState(void)
{
	uint8_t i = 0;
	for (i; i < this->numberOfNextStates; i++)
	{
		transitionConditionCheckerFunctionPtr currentTesterFunction = *(this->checkerFunctions.at(i));
		assert(currentTesterFunction != NULL);
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
	if (i == this->numberOfNextStates)
	{
		// no transition check successful
		// stay in state
		return this;
	}
	else
	{
		return this->nextStates[i];
	}
}
