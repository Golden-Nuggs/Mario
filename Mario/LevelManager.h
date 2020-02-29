#pragma once

#include <SFML/Graphics.hpp>
#include "Guy.h"
#include "Tile.h"
#include <vector>
#include "Camera.h"
#include "Collider.h"
#include "Block.h"
#include <box2d/box2d.h>
#include <memory>


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

	sf::Texture level_spriteSheet;
	std::vector<Tile> levelTiles;
	std::vector<Collider> colliders_ground;
	//std::vector<std::unique_ptr<Block>> all_block_ptrs;
	std::vector<Block*> all_blocks;

	Camera camera;

	b2World* worldPtr = nullptr;

};