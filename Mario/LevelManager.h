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
	void update(float deltaSeconds);
	void draw(sf::RenderWindow& window);
	sf::View& getGameView();

private:
	Guy* guy;

	std::unique_ptr<sf::Texture> level_spriteSheet;
	std::vector<std::unique_ptr<Tile>> levelTiles;
	std::vector<std::unique_ptr<Collider>> colliders_ground;
	std::vector<std::unique_ptr<Block>> all_blocks;

	Camera camera;

	b2World* worldPtr = nullptr;

};