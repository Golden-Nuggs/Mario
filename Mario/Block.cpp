#include "Block.h"
#include "Constants.h"
#include "LevelManager.h"
#include "Coin.h"


Block::Block(BlockType type, int x, int y, int width, int height, std::vector<tmx::Tileset::Tile>& sourceTileList, b2World* world)
	: sourceTiles(sourceTileList)
{
	LevelManager* levelManager = LevelManager::getInstance();
	tileWidth = width;
	tileHeight = height;
	blockType = type;
	bHit = new bool;
	*bHit = false;
	numCoin = new int;
	*numCoin = 0;

	std::ios::sync_with_stdio(false);

	float hx = width / 2.f;
	float hy = height / 2.f;
	worldPtr = world;
	sprite = new sf::Sprite();
	sprite->setOrigin(hx, hy);
	sprite->setPosition(x, y);
	sprite->setTexture(levelManager->getLevelSpriteSheet());
	setCorrectTexFrame(false);

	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(x, y);
	bodyPtr = worldPtr->CreateBody(&bodyDef);
	bodyPtr->SetUserData(this);
	box.SetAsBox(hx, hy);
	mainFixture.shape = &box;
	fixtureData_main = new FixtureUserData;	fixtureData_main = new FixtureUserData;
	fixtureData_main->friendlyName = Constants::BLOCK_FIXTUREDATA_NAME;
	mainFixture.userData = fixtureData_main;
	bodyPtr->CreateFixture(&mainFixture);

	startPos = bodyPtr->GetPosition();

}

void Block::init()
{

}

void Block::update(float deltaSeconds)
{
	if (*bHit)
	{
		if (bodyPtr->GetPosition().y <= startPos.y - Constants::BLOCK_MOVEMENT_AMOUNT)
		{
			bodyPtr->SetLinearVelocity(b2Vec2(0, Constants::BLOCK_MOVEMENT_SPEED));
			*bHit = false;
		}
	}
	else
	{
		if (bodyPtr->GetPosition().y < startPos.y)
		{

		}
		else
		{
			bodyPtr->SetLinearVelocity(b2Vec2(0, 0));
		}
	}


	sprite->setPosition(sf::Vector2f(bodyPtr->GetPosition().x, bodyPtr->GetPosition().y));
}

void Block::draw(sf::RenderWindow& window)
{
	window.draw(*sprite);
}

void Block::hit(Guy* guy)
{
	LevelManager* levelManager = LevelManager::getInstance();
	switch (blockType)
	{
	case BlockType::QUESTION_MARK:
		*bHit = true;
		bodyPtr->SetLinearVelocity(b2Vec2(0, -Constants::BLOCK_MOVEMENT_AMOUNT));
		if (*numCoin > 0)
		{
			Coin* coin = levelManager->spawnCoin();
			coin->init(bodyPtr->GetPosition().x, bodyPtr->GetPosition().y, sourceTiles[Constants::SOURCETILESINDEX_COIN].imagePosition.x, sourceTiles[Constants::SOURCETILESINDEX_COIN].imagePosition.y, tileWidth, tileHeight);
			guy->addCoins(1);
			//*numCoin--; <- Doesn't work. Says dereferencing ignored TODO: Find out why.
			*numCoin -= 1;
			std::cout << "Coin taken from block\n";
		}
		if (*numCoin <= 0)
		{
			setCorrectTexFrame(true);
		}
		break;
	case BlockType::BRICK:
		break;
	}

}

void Block::setCoins(unsigned int amount)
{
	*numCoin = amount;

}

void Block::setCorrectTexFrame(bool used)
{
	switch (blockType)
	{
	case BlockType::QUESTION_MARK:
		if (used)
		{
			sprite->setTextureRect(sf::IntRect(sourceTiles[Constants::SOURCETILESINDEX_BLOCK_USED].imagePosition.x, sourceTiles[Constants::SOURCETILESINDEX_BLOCK_Q].imagePosition.y, tileWidth, tileHeight));

		}
		else
		{		
			sprite->setTextureRect(sf::IntRect(sourceTiles[Constants::SOURCETILESINDEX_BLOCK_Q].imagePosition.x, sourceTiles[Constants::SOURCETILESINDEX_BLOCK_Q].imagePosition.y, tileWidth, tileHeight));
		}
		break;
	case BlockType::BRICK:
		sprite->setTextureRect(sf::IntRect(sourceTiles[Constants::SOURCETILESINDEX_BLOCK_BRICK].imagePosition.x, sourceTiles[Constants::SOURCETILESINDEX_BLOCK_BRICK].imagePosition.y, tileWidth, tileHeight));
		break;
	}

}
