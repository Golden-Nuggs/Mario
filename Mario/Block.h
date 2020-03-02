#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "FixtureUserData.h"
#include "Guy.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>


class Block
{
public:
	enum class BlockType { BRICK, QUESTION_MARK };
	Block(BlockType type, int x, int y, int width, int height, std::vector<tmx::Tileset::Tile>& sourceTileList, b2World* world);
	void init();
	void update(float deltaSeconds);
	void draw(sf::RenderWindow& window);
	void hit(Guy* guy);
	void setCoins(unsigned int amount);
	void setCorrectTexFrame(bool used);
private:
	sf::Sprite* sprite = nullptr;
	int tileWidth;
	int tileHeight;
	BlockType blockType;
	std::vector<tmx::Tileset::Tile>& sourceTiles;
	b2World* worldPtr = nullptr;
	b2BodyDef bodyDef;
	b2Body* bodyPtr = nullptr;
	b2PolygonShape box;
	b2FixtureDef mainFixture;
	FixtureUserData* fixtureData_main = nullptr;
	int* numCoin;

	b2Vec2 startPos;
	
	bool* bHit;
	
};

