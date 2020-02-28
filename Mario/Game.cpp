#include "Game.h"
#include <iostream>

void Game::start(b2World* world)
{
	worldPtr = world;
	levelManager.start(worldPtr);
	worldPtr->SetContactListener(&contactListener);
}

void Game::update()
{
	
	sf::Time time = deltaClock.restart();

	levelManager.update(time.asSeconds());
}

void Game::draw(sf::RenderWindow& window)
{
	window.clear();

	levelManager.draw(window);

	window.display();
}

LevelManager& Game::getLevelManager()
{
	return levelManager;
}
