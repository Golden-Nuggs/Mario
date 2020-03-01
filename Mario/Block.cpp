#include "Block.h"

#include "Constants.h"

Block::Block()
{
	blockType = BlockType::UNINITIALIZED;
	bHit = new bool;
	*bHit = false;
}

void Block::start(BlockType type, unsigned int x, unsigned int y, unsigned int width, unsigned int height, sf::Texture& texture, unsigned int image_x, unsigned int image_y, b2World* world)
{
	std::ios::sync_with_stdio(false);

	float hx = width / 2.f;
	float hy = height / 2.f;
	worldPtr = world;
	sprite = new sf::Sprite();
	sprite->setTexture(texture);
	sprite->setTextureRect(sf::IntRect(image_x, image_y, width, height));
	sprite->setOrigin(hx, hy);
	sprite->setPosition(x, y);
	startPosition = sprite->getPosition();

	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(x, y);


	bodyPtr = worldPtr->CreateBody(&bodyDef);
	bodyPtr->SetUserData(this); 

	box.SetAsBox(hx, hy);
	mainFixture.shape = &box;
	
	blockType = type;
	fixtureData_main = new FixtureUserData;	fixtureData_main = new FixtureUserData;
	fixtureData_main->friendlyName = Constants::BLOCK_FIXTUREDATA_NAME;
	mainFixture.userData = fixtureData_main;
	bodyPtr->CreateFixture(&mainFixture);

	startPos = bodyPtr->GetPosition();

}

void Block::update(float deltaSeconds)
{

	if (*bHit)
	{
		if (bodyPtr->GetPosition().y <= startPos.y - Constants::BLOCK_MOVEMENT_AMOUNT)
		{
			bodyPtr->SetLinearVelocity(b2Vec2(0, Constants::BLOCK_MOVEMENT_SPEED));
			*bHit = false;
		}
	}
	else
	{
		if (bodyPtr->GetPosition().y < startPos.y)
		{

		}
		else
		{
			bodyPtr->SetLinearVelocity(b2Vec2(0, 0));
		}
	}


	sprite->setPosition(sf::Vector2f(bodyPtr->GetPosition().x, bodyPtr->GetPosition().y));
}

void Block::draw(sf::RenderWindow& window)
{
	window.draw(*sprite);
}

void Block::hit()
{
	*bHit = true;
	bodyPtr->SetLinearVelocity(b2Vec2(0, -Constants::BLOCK_MOVEMENT_AMOUNT));
}
