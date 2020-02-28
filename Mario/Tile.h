#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>


class Tile
{
public:
	Tile();
	void start(unsigned int x, unsigned int y, unsigned int width, unsigned int height, sf::Texture& texture, unsigned int image_x, unsigned int image_y);
	void update();
	void draw(sf::RenderWindow& Window);
private:
	sf::Texture texture;
	sf::Sprite sprite;



};
