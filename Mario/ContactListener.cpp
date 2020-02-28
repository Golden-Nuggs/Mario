#include "ContactListener.h"
#include <iostream>
#include "FixtureUserData.h"
#include "Constants.h"


void ContactListener::BeginContact(b2Contact* contact)
{
	FixtureUserData* fdA = (FixtureUserData*)contact->GetFixtureA()->GetUserData();
	FixtureUserData* fdB = (FixtureUserData*)contact->GetFixtureB()->GetUserData();
	std::cout << "fdA = " << fdA << std::endl;
	std::cout << "fdB = " << fdB << std::endl;

	void* udA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* udB = contact->GetFixtureB()->GetBody()->GetUserData();
	std::cout << "udA = " << udA << std::endl;
	std::cout << "udB = " << udB << std::endl;

	if (fdA != nullptr && fdB != nullptr && udA != nullptr && udB != nullptr)
	{
		std::string a = fdA->friendlyName;
		std::string b = fdB->friendlyName;
		std::cout << a << " has collided with " << b << std::endl;
		if (a == Constants::MARIO_TOP_SENSOR_FIXTUREDATA_NAME && b == Constants::BLOCK_FIXTUREDATA_NAME)
		{
			HandleBlockContact(static_cast<Block*>(udB));
		}
		else if (a == Constants::BLOCK_FIXTUREDATA_NAME && b == Constants::MARIO_TOP_SENSOR_FIXTUREDATA_NAME)
		{
			HandleBlockContact(static_cast<Block*>(udA));
		}
	}
}

void ContactListener::HandleBlockContact(Block* block)
{
	if (block != nullptr)
	{
		std::cout << "Block* (passed in to HandleBlockContact(Block*) is: " << block << std::endl;
		block->hit();
	}

}


void ContactListener::EndContact(b2Contact* contact)
{

}