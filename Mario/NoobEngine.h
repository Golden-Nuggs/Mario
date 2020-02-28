#pragma once

#include "SFML/Graphics.hpp"
#include "Game.h"
#include "box2d/box2d.h"

#include "SFMLDebugDraw.h"



class NoobEngine
{
	

public:
	sf::RenderWindow window;
	void start();

	void CreateWindow();


private:
	Game game;
	b2Vec2 gravity; 
	b2World* world;
	
};