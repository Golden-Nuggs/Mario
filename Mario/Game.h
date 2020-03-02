#pragma once

#include <SFML/Graphics.hpp>
#include "LevelManager.h"
#include "ContactListener.h"

class Game
{
public:
	void start(b2World* world);
	void update();
	void draw(sf::RenderWindow& window);

private:
	LevelManager* levelManager = nullptr;
	sf::Clock deltaClock;
	b2World* worldPtr = nullptr;
	ContactListener contactListener;
};