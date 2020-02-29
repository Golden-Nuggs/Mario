#include "Constants.h"
#include <iostream>
#include "ViewTools.h"
#include "LevelManager.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>


void LevelManager::start(b2World* world)
{
	guy = new Guy();
	level_spriteSheet = new sf::Texture();
	worldPtr = world;

	tmx::Map map;
	unsigned int level_width = 0;
	unsigned int level_height = 0;
	unsigned int tile_width = 0;
	unsigned int tile_height = 0;
	if (map.load("LevelTmx/1-1.tmx"))
	{
		level_width = map.getTileCount().x;
		level_height = map.getTileCount().y;
		tile_width = map.getTileSize().x;
		tile_height = map.getTileSize().y;
		std::vector<tmx::Tileset::Tile> sourceTiles;
		const auto& tilesets = map.getTilesets(); // only needed when using more than 1 spritesheet (i will...)
		for (const auto& tileset : tilesets) // as above
		{
			//read out tile set properties, load textures etc...

			// TODO: Will need to use First GID in the formula to work out level width and current tile (if I want to support multiple spritesheets (i do!) see: https://discourse.mapeditor.org/t/how-is-texture-data-represented-in-tmx-file-and-how-to-get-that-data-in-c/4360
			sourceTiles = tileset.getTiles();
			for (int i = 0; i < sourceTiles.size(); i++)
			{
				//std::cout << "TILESET: i:" << i << " || sourceTile ID:" << sourceTiles[i].ID << "\n";
				//std::cout << "TILESET: Image position: " << sourceTiles[i].imagePosition.x << " , " << sourceTiles[i].imagePosition.y << "\n";
			}
			if (level_spriteSheet->loadFromFile(tileset.getImagePath()))
			{
				std::cout << "Level sprite sheet path: " << tileset.getImagePath() << "\n";
			}
			else
			{
				std::cout << "Texture Not Loaded!" << "\n";
			}
		}

		const auto& layers = map.getLayers();
		for (const auto& layer : layers)
		{
			if (layer->getType() == tmx::Layer::Type::Object)
			{
				const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
				if (objectLayer.getName() == "solid")
				{
					const auto& objects = objectLayer.getObjects();
					for (const auto object : objects)
					{
						Collider* collider = new Collider();
						collider->start(object.getAABB(), worldPtr);
						colliders_ground.push_back(collider);
					}
				}			
				if (objectLayer.getName() == "blocks_?")
				{
					const auto& objects = objectLayer.getObjects();
					for (const auto object : objects)
					{
						Block* block = new Block();
						tmx::FloatRect aabb = object.getAABB();
						block->start(Block::BlockType::QUESTION_MARK, aabb.left, aabb.top, tile_width, tile_height, *level_spriteSheet, sourceTiles[Constants::BLOCK_Q_ID].imagePosition.x, sourceTiles[Constants::BLOCK_Q_ID].imagePosition.y, worldPtr);
						all_blocks.push_back(std::make_unique<Block>(*block));
					}
				}
				if (objectLayer.getName() == "blocks_brick")
				{
					const auto& objects = objectLayer.getObjects();
					for (const auto object : objects)
					{
						Block* block = new Block();
						tmx::FloatRect aabb = object.getAABB();
						block->start(Block::BlockType::BRICK, aabb.left, aabb.top, tile_width, tile_height, *level_spriteSheet, sourceTiles[Constants::BLOCK_BRICK_ID].imagePosition.x, sourceTiles[Constants::BLOCK_BRICK_ID].imagePosition.y, worldPtr);
						all_blocks.push_back(std::make_unique<Block>(*block));
					}
				}
			}
			else if (layer->getType() == tmx::Layer::Type::Tile)
			{
				const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
				// read out the layer properties etc...

				auto& tiles = tileLayer.getTiles();
				for (int i = 0; i < tiles.size(); i++)
				{
					uint32_t tileID = tiles[i].ID;
					uint8_t flipFlag = tiles[i].flipFlags;
					unsigned long long tile_x = i % level_width;
					unsigned long long tile_y = i / level_width;
					if (tileID <= 0)
						continue;
					Tile* tile = new Tile();
					// NOTE: Here is where i added minus 1, but couldnt quite understand why i needed it (it was from trial and error)
					tile->start(tile_x, tile_y, tile_width, tile_height, *level_spriteSheet, sourceTiles[tileID - 1].imagePosition.x, sourceTiles[tileID - 1].imagePosition.y);
					levelTiles.push_back(tile);
				}
			}
		}
	}
	else
	{
		std::cout << "Failed to load map" << "\n";
	}

	camera.initView(level_width * tile_width, level_height * tile_height);
	guy->start(worldPtr);
}

void LevelManager::update(float deltaSeconds)
{
	guy->update(deltaSeconds);
	camera.followTarget(guy->getPosition());
	for (int i = 0; i < all_blocks.size(); i++)
	{
		all_blocks[i]->update(deltaSeconds);
	}
}

void LevelManager::draw(sf::RenderWindow& window)
{
	window.setView(camera.getGameView());
	for (int i = 0; i < levelTiles.size(); i++)
	{
		levelTiles[i]->draw(window);
	}

	for (int i = 0; i < all_blocks.size(); i++)
	{

		all_blocks[i]->draw(window);
	}
	guy->draw(window);
}

sf::View& LevelManager::getGameView()
{
	return camera.getGameView();
}
