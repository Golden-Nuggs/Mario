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
#include "Powerup.h"
#include "Coin.h"

class LevelManager
{
public:
	static LevelManager* getInstance();
	void init(b2World* world);
	void update(float deltaSeconds);
	void draw(sf::RenderWindow& window);
	sf::View& getGameView();
	Coin* spawnCoin();
	sf::Texture& getLevelSpriteSheet();

private:
	LevelManager();
	static LevelManager* instance;
	Guy* guy = nullptr;

	std::unique_ptr<sf::Texture> level_spriteSheet;
	std::vector<tmx::Tileset::Tile> sourceTiles;

	std::vector<std::unique_ptr<Tile>> levelTiles;
	std::vector<std::unique_ptr<Collider>> colliders_ground;
	std::vector<std::unique_ptr<Block>> all_blocks;
	std::vector<std::unique_ptr<Coin>> coin_objects;

	Camera camera;

	b2World* worldPtr = nullptr;

};