#include "Block.h"

#include "Constants.h"

Block::Block()
{
	blockType = BlockType::UNINITIALIZED;
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

}

void Block::update(float deltaSeconds)
{
	if (sprite->getPosition().y < bodyPtr->GetPosition().y)
	{
		sprite->move(sf::Vector2f(0, Constants::BLOCK_MOVEMENT_SPEED * deltaSeconds));
	}

}

void Block::draw(sf::RenderWindow& window)
{
	window.draw(*sprite);
}

void Block::hit()
{
	std::cout << "block hit\n";
	sprite->move(sf::Vector2f(0, -8)); // TODO Magic number
}
