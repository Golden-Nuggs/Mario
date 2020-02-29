#include "Block.h"

#include "Constants.h"

Block::Block()
{
	blockType = BlockType::UNINITIALIZED;
}

Block::~Block()
{
}

void Block::start(BlockType type, unsigned int x, unsigned int y, unsigned int width, unsigned int height, sf::Texture& texture, unsigned int image_x, unsigned int image_y, b2World* world)
{
	std::ios::sync_with_stdio(false);
	float hx = width / 2.f;
	float hy = height / 2.f;
	worldPtr = world;
	std::cout << "sprite (block StarT())=" << &sprite << "\n";
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(image_x, image_y, width, height));
	sprite.setOrigin(hx, hy);
	sprite.setPosition(x, y);
	startPosition = sprite.getPosition();

	bodyDef.position.Set(x, y);
	bodyPtr = worldPtr->CreateBody(&bodyDef);
	bodyPtr->SetUserData((void*)this); // <--- I guess this is wrong. Also compiles if I dont cast it. Tried both already
	std::cout << "(Block.cpp) bodyPtr set to: " << bodyPtr << "\n";
	std::cout << "(Block.cpp) bodyPtr (deref): " << &bodyPtr << "\n";
	std::cout << "Block.cpp bodysetuserdata. Result of body->getUd = " << bodyPtr->GetUserData() << "\n";
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


}

void Block::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Block::hit()
{
	if (bodyPtr != nullptr)
	{
		std::cout << "(Block.cpp) bblock::Hit(): bodyptr now equals:  " << bodyPtr << "\n";
	}
	else 
	{
		std::cout << "(Block.cpp) bblock::Hit(): bodyPtr == (nullptr)  " << "\n";
		return;
	}


	std::cout << "(Block.cpp) bblock::Hit(): this now equals:  " << this << "\n";

	std::cout << "Blocktype: " << (int)blockType << "\n"; // <<--- WHY DOES THIS NOT RETURN THE CORRECT INT (IT VARIES FROM 1 ~ 9999999)
	sprite.setColor(sf::Color::Blue); // <--- IT DOESN'T CHANGE COLOR WHEN FUNCTION IS CALLED.
}
