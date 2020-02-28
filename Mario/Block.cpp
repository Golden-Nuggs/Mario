#include "Block.h"

#include "Constants.h"

Block::Block()
{
	blockType = BlockType::UNINITIALIZED;
}

void Block::start(BlockType type, unsigned int x, unsigned int y, unsigned int width, unsigned int height, sf::Texture& texture, unsigned int image_x, unsigned int image_y, b2World* world)
{
	float hx = width / 2.f;
	float hy = height / 2.f;
	worldPtr = world;
	//sprite = new sf::Sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(image_x, image_y, width, height));
	sprite.setOrigin(hx, hy);
	sprite.setPosition(x, y);
	startPosition = sprite.getPosition();

	bodyDef.position.Set(x, y);
	bodyPtr = worldPtr->CreateBody(&bodyDef);
	bodyPtr->SetUserData((void*)this); // <--- I guess this is wrong. Also compiles if I dont cast it. Tried both already

	box.SetAsBox(hx, hy);


	mainFixture.shape = &box;


	blockType = type;
	fixtureData_main = new FixtureUserData;	fixtureData_main = new FixtureUserData;
	fixtureData_main->friendlyName = Constants::BLOCK_FIXTUREDATA_NAME;
	mainFixture.userData = fixtureData_main;
	bodyPtr->CreateFixture(&mainFixture);

}

void Block::update()
{
	sprite.setPosition(bodyPtr->GetPosition().x, bodyPtr->GetPosition().y);
}

void Block::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Block::hit()
{
	sprite.setColor(sf::Color::Blue); // <--- IT DOESN'T CHANGE COLOR WHEN FUNCTION IS CALLED.
}
