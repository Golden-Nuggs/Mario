#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "FixtureUserData.h"

class Block
{
public:
	enum class BlockType { UNINITIALIZED, BRICK, BRICK_UNBREAKABLE, QUESTION_MARK };
	Block();
	Block(const Block&) = delete;
	Block& operator= (const Block&) = delete;
	void start(BlockType type, unsigned int x, unsigned int y, unsigned int width, unsigned int height, sf::Texture& texture, unsigned int image_x, unsigned int image_y, b2World* world);
	void update();
	void draw(sf::RenderWindow& window);
	void hit();


private:
	sf::Sprite* sprite = nullptr;
	BlockType blockType;
	b2World* worldPtr = nullptr;
	b2BodyDef bodyDef;
	b2Body* bodyPtr = nullptr;
	b2PolygonShape box;
	b2FixtureDef mainFixture;
	FixtureUserData* fixtureData_main = nullptr;

	sf::Vector2f startPosition;


};

