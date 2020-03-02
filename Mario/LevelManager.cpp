#include "Constants.h"
#include <iostream>
#include "ViewTools.h"
#include "LevelManager.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>

LevelManager* LevelManager::instance = nullptr;

LevelManager* LevelManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new LevelManager();
	}

	return instance;
}

LevelManager::LevelManager() 
{
	guy = new Guy();
}

void LevelManager::init(b2World* world)
{

	sf::Texture* tex = new sf::Texture();
	level_spriteSheet = std::make_unique<sf::Texture>(*tex);
	worldPtr = world;

	tmx::Map map;
	unsigned int level_width = 0;
	unsigned int level_height = 0;
	unsigned int tile_width = 0;
	unsigned int tile_height = 0;
	if (map.load("LevelTmx/1-1-d.tmx"))
	{
		level_width = map.getTileCount().x;
		level_height = map.getTileCount().y;
		tile_width = map.getTileSize().x;
		tile_height = map.getTileSize().y;
		const auto& tilesets = map.getTilesets(); // only needed when using more than 1 spritesheet (i will!)
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
						colliders_ground.push_back(std::make_unique<Collider>(*collider));
					}
				}			
				if (objectLayer.getName() == Constants::OBJECT_LAYER_NAME_BLOCKS_Q)
				{
					const auto& objects = objectLayer.getObjects();
					for (const auto object : objects)
					{
						tmx::FloatRect aabb = object.getAABB();
						Block* block = new Block(Block::BlockType::QUESTION_MARK, aabb.left, aabb.top, tile_width, tile_height, sourceTiles, worldPtr);
						std::vector<tmx::Property> properties = object.getProperties();
						if (properties.size() > 0)
						{
							for (int i = 0; i < properties.size(); i++)
							{
								std::string propName = properties[i].getName();
								if (propName == Constants::TILED_PROPERTIES_BLOCK_NUMCOIN)
								{
									block->setCoins(properties[i].getIntValue());
									std::cout << "coins added to block: " << properties[i].getIntValue() << '\n'; 
								}
							}
						}
						all_blocks.push_back(std::make_unique<Block>(*block));
					}
				}
				if (objectLayer.getName() == Constants::OBJECT_LAYER_NAME_BLOCKS_BRICK)
				{
					const auto& objects = objectLayer.getObjects();
					for (const auto object : objects)
					{
						tmx::FloatRect aabb = object.getAABB();
						Block* block = new Block(Block::BlockType::BRICK, aabb.left, aabb.top, tile_width, tile_height, sourceTiles, worldPtr);
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
					tile->init(tile_x, tile_y, tile_width, tile_height, sourceTiles[tileID - 1].imagePosition.x, sourceTiles[tileID - 1].imagePosition.y);
					levelTiles.push_back(std::make_unique<Tile>(*tile));
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
	for (int i = 0; i < coin_objects.size(); i++)
	{
		coin_objects[i]->update(deltaSeconds);
	}

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
	for (int i = 0; i < coin_objects.size(); i++)
	{
		coin_objects[i]->draw(window);
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

Coin* LevelManager::spawnCoin()
{
	coin_objects.push_back(std::make_unique<Coin>(*new Coin));
	return coin_objects[coin_objects.size() -1].get();
}

sf::Texture& LevelManager::getLevelSpriteSheet()
{
	return *level_spriteSheet;
}
