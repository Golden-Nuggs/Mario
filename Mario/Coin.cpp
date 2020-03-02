#include "Coin.h"
#include "Constants.h"

Coin::Coin()
{
	std::cout << "Coin constructor\n";
	startY = -999.f;
}

void Coin::update(float deltaSeconds)
{
	Powerup::update(deltaSeconds);
	startY = Powerup::start_y;
	if (sprite->getPosition().y > startY - Constants::COIN_MAX_Y)
	{
		sprite->move(0, -Constants::COIN_MOVE_SPEED * deltaSeconds);
	}
}

void Coin::draw(sf::RenderWindow& window)
{
	Powerup::draw(window);


}
