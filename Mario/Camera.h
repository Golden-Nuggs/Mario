#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:
	void initView(unsigned int levelWidth, unsigned int levelHeight);
	void followTarget(sf::Vector2f target);
	sf::View& getGameView();
private:
	sf::View gameView;
	float minX;
	float maxX;
	float minY;
	float maxY;
};