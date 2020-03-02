#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "FixtureUserData.h"

class Powerup
{
public:
	Powerup();
	virtual void init(unsigned int x, unsigned int y, unsigned int atlas_x, unsigned int atlas_y, unsigned int textureWidth, unsigned int textureHeight);
	virtual void init(unsigned int x, unsigned int y, unsigned int atlas_x, unsigned int atlas_y, unsigned int textureWidth, unsigned int textureHeight, b2World* world);
	virtual void update(float deltaSeconds);
	virtual void draw(sf::RenderWindow& window);
	bool bGravity;
	bool bCollectable;
	sf::Vector2f moveDirection;
	float moveSpeed;
	

protected:
	b2World* worldPtr = nullptr;
	sf::Texture* texture = nullptr;
	sf::Sprite* sprite = nullptr;
	b2Body* bodyPtr = nullptr;
	b2BodyDef bodyDef;
	b2PolygonShape box;
	b2FixtureDef* mainFixture = nullptr;
	FixtureUserData* fixtureData_Main = nullptr;
	int start_x;
	int start_y;
	
};