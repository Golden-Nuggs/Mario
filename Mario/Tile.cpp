#include "Tile.h"
#include <iostream>
#include "LevelManager.h"


Tile::Tile()
{

}

void Tile::init(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int image_x, unsigned int image_y)
{
	sprite.setTexture(LevelManager::getInstance()->getLevelSpriteSheet());
	sprite.setTextureRect(sf::IntRect(image_x, image_y, width, height));
	sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);
	sprite.setPosition(x * width + (width / 2.f), y * height + (height / 2.f));

}

void Tile::update()
{
}

void Tile::draw(sf::RenderWindow& Window)
{
	Window.draw(sprite);
}



