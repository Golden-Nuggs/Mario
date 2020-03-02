#include "Powerup.h"
#include "Constants.h"
#include "LevelManager.h"

Powerup::Powerup()
{
	sprite = new sf::Sprite();
	bGravity = true;
	bCollectable = true;
	moveDirection = sf::Vector2f(0, 0);
	moveSpeed = Constants::POWERUP_BASE_MOVE_SPEED;
	std::cout << "powerup constructor\n";
}

void Powerup::init(unsigned int x, unsigned int y, unsigned int atlas_x, unsigned int atlas_y, unsigned int textureWidth, unsigned int textureHeight)
{
	sprite->setPosition(x, y);
	start_x = sprite->getPosition().x;
	start_y = sprite->getPosition().y;
	std::cout << "start pos set: " << start_y << '\n';
	unsigned int hx = textureWidth / 2;
	unsigned int hy = textureHeight / 2;
	sprite->setOrigin(hx, hy);
	sprite->setTexture(LevelManager::getInstance()->getLevelSpriteSheet());
	sprite->setTextureRect(sf::IntRect(atlas_x, atlas_y, textureWidth, textureHeight));


}

void Powerup::init(unsigned int x, unsigned int y, unsigned int atlas_x, unsigned int atlas_y, unsigned int textureWidth, unsigned int textureHeight, b2World* world)
{
	sprite->setPosition(x, y);
	unsigned int hx = textureWidth / 2;
	unsigned int hy = textureHeight / 2;
	sprite->setOrigin(hx, hy);
	sprite->setTexture(LevelManager::getInstance()->getLevelSpriteSheet());
	sprite->setTextureRect(sf::IntRect(atlas_x, atlas_y, textureWidth, textureHeight));
	worldPtr = world;


}

void Powerup::update(float deltaSeconds)
{

}

void Powerup::draw(sf::RenderWindow& window)
{
	window.draw(*sprite);
}

