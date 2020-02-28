#pragma once

#include <SFML/Graphics.hpp>
#include "Guy.h"
#include "Tile.h"
#include <vector>
#include "Camera.h"
#include "Collider.h"
#include "Block.h"

#include <box2d/box2d.h>


class LevelManager
{
public:
	void start(b2World* world);
	//void BuildLevelFromString();
	void update(float deltaSeconds);
	void draw(sf::RenderWindow& window);
	sf::View& getGameView();

private:
	Guy guy;

	std::string level1;
	sf::Texture level_spriteSheet;
	std::vector<Tile> levelTiles;
	std::vector<Collider> colliders_ground;
	std::vector<Block> all_blocks;

	Camera camera;

	b2World* worldPtr = nullptr;

};