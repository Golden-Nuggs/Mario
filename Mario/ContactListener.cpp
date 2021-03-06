#include "ContactListener.h"
#include <iostream>
#include "FixtureUserData.h"
#include "Constants.h"


void ContactListener::BeginContact(b2Contact* contact)
{
	FixtureUserData* fdA = (FixtureUserData*)contact->GetFixtureA()->GetUserData();
	FixtureUserData* fdB = (FixtureUserData*)contact->GetFixtureB()->GetUserData();

	void* udA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* udB = contact->GetFixtureB()->GetBody()->GetUserData();

	if (fdA != nullptr && fdB != nullptr && udA != nullptr && udB != nullptr)
	{
		std::string a = fdA->friendlyName;
		std::string b = fdB->friendlyName;

		// check for PLAYER-top - block collision 
		if (a == Constants::PLAYER_TOP_SENSOR_FIXTUREDATA_NAME && b == Constants::BLOCK_FIXTUREDATA_NAME)
		{
			HandleBlockContact((Block*)udB, (Guy*)udA);
		}
		else if (a == Constants::BLOCK_FIXTUREDATA_NAME && b == Constants::PLAYER_TOP_SENSOR_FIXTUREDATA_NAME)
		{
			HandleBlockContact((Block*)udA, (Guy*)udB);
		}
	}
}

void ContactListener::HandleBlockContact(Block* block, Guy* guy)
{
	if (block != nullptr)
	{
		block->hit(guy);
	}

}


void ContactListener::EndContact(b2Contact* contact)
{

}