#include <assert.h>
#include <vector>
#include <stdbool.h>

#include "State.h"

bool dummyTester(void)
{
	return false;
}

State_t::State_t(const uint8_t identifier,const uint8_t numberOfNextStates)
{
	this->identifier = identifier;
	this->numberOfNextStates = numberOfNextStates;
	this->nextStates.reserve(sizeof(State_t*) * numberOfNextStates);
	this->testerFunctions.reserve(sizeof(&dummyTester) * numberOfNextStates);
}

State_t::~State_t(void)
{
	this->nextStates.~vector();
	this->testerFunctions.~vector();
}

bool State_t::addNextState(State_t * const nextState)
{
	bool returnValue = false;
	assert(nextState != NULL);
	if(this->numberOfAlreadyInsertedNextStates < this->numberOfNextStates)
	{
		this->nextStates.push_back(nextState);
		this->numberOfAlreadyInsertedNextStates++;
		returnValue = true;
	}
	else
	{
		// can not insert
		returnValue = false;
	}
	return returnValue;
}

State_t * State_t::getNextState(void)
{
	uint8_t i=0;
	for (i; i < this->numberOfNextStates; i++)
	{
		fptr currentTesterFunction = *(this->testerFunctions.at(i));
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
	return this->nextStates[i];
}
