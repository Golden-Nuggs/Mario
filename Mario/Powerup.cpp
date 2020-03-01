#include "Powerup.h"
#include "Constants.h"

Powerup::Powerup()
{
	texture = new sf::Texture();
	sprite = new sf::Sprite();
	bGravity = false;
	bCollectable = true;
	moveDirection = sf::Vector2f(0, 0);
	moveSpeed = Constants::POWERUP_BASE_MOVE_SPEED;

}

void Powerup::update(float deltaSeconds)
{

}

void Powerup::draw(sf::RenderWindow& window)
{
	window.draw(*sprite);
}
