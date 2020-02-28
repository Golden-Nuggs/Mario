#include "Guy.h"
#include "Constants.h"
#include <iostream>
#include "RaycastCallBack.h"
#include <cmath>


Guy::Guy()
{
	powerJumpTimer = 0.f;
	currentMoveState = MoveState::IDLE;
	animFrameDelay = Constants::BASE_ANIM_FRAME_DELAY;
	animFrameTimer = 0.f;
	frameIndex = 0;
}

void Guy::start(b2World* world)
{
	worldPtr = world;
	texture.loadFromFile("Textures/mario-small.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(Constants::MARIO_SMALL_IDLE_ATLAS_X, 0, Constants::SPRITE_WIDTH, Constants::SPRITE_HEIGHT));
	float hx = sprite.getTextureRect().width / 2.f;
	float hy = sprite.getTextureRect().height / 2.f;
	sprite.setOrigin(hx, hy);

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(5 * Constants::PPU, 13 * Constants::PPU);
	bodyPtr = worldPtr->CreateBody(&bodyDef);
	bodyPtr->SetUserData(this);

	colliderBox.SetAsBox(hx / 2.f, hy / 1.15f); 
	mainFixture.shape = &colliderBox;
	mainFixture.density = 70.f; // TODO Magic numbers
	mainFixture.friction = 0.05f;
	fixtureData_main = new FixtureUserData;
	fixtureData_main->friendlyName = Constants::MARIO_MAIN_FIXTURE_FIXTUREDATA_NAME;
	mainFixture.userData = fixtureData_main;
	bodyPtr->CreateFixture(&mainFixture);

	topSensorBox.SetAsBox(sprite.getTextureRect().width / 4.f, 10.f, b2Vec2(sprite.getPosition().x, sprite.getPosition().y - hy), 0.f);
	topSensor.shape = &topSensorBox;
	topSensor.isSensor = true;
	fixtureData_topSensor = new FixtureUserData;
	fixtureData_topSensor->friendlyName = Constants::MARIO_TOP_SENSOR_FIXTUREDATA_NAME;
	topSensor.userData = fixtureData_topSensor;
	bodyPtr->CreateFixture(&topSensor);

	bodyPtr->SetFixedRotation(true);
	
}

void Guy::update(float deltaSeconds)
{
	moveSideways();
	jump(deltaSeconds);
	alignSpriteToBody();
	setCurrentMoveState();
	setCorrectAnimFrame(deltaSeconds);
	flipSpriteWhenTurning();
}

void Guy::setCorrectAnimFrame(float deltaSeconds)
{
	b2Vec2 vel = bodyPtr->GetLinearVelocity();
	animFrameTimer += deltaSeconds;
	switch (currentMoveState)
	{
	case MoveState::IDLE:
		sprite.setTextureRect(sf::IntRect(Constants::MARIO_SMALL_IDLE_ATLAS_X * Constants::SPRITE_WIDTH, 0, Constants::SPRITE_WIDTH, Constants::SPRITE_HEIGHT));
		break;
	case MoveState::WALKING:
		if (animFrameTimer >= animFrameDelay)
		{
			animFrameTimer = 0.f;
			if (++frameIndex >= Constants::MARIO_SMALL_WALK_FRAME_COUNT)
			{
				frameIndex = 0;
			}
		}
		sprite.setTextureRect(sf::IntRect((Constants::MARIO_SMALL_RUN_ATLAS_X + frameIndex) * Constants::SPRITE_WIDTH, 0, Constants::SPRITE_WIDTH, Constants::SPRITE_HEIGHT));
		break;
	case MoveState::RUNNING:
		if (animFrameTimer >= animFrameDelay / 2.f)
		{
			animFrameTimer = 0.f;
			if (++frameIndex >= Constants::MARIO_SMALL_WALK_FRAME_COUNT)
			{
				frameIndex = 0;
			}

		}
		sprite.setTextureRect(sf::IntRect((Constants::MARIO_SMALL_RUN_ATLAS_X + frameIndex) * Constants::SPRITE_WIDTH, 0, Constants::SPRITE_WIDTH, Constants::SPRITE_HEIGHT));
		break;
	case MoveState::JUMPING_UP:
		sprite.setTextureRect(sf::IntRect(Constants::MARIO_SMALL_JUMP_ATLAS_X * Constants::SPRITE_WIDTH, 0, Constants::SPRITE_WIDTH, Constants::SPRITE_HEIGHT));
		break;
	case MoveState::FLAG_POLE:
		sprite.setTextureRect(sf::IntRect(Constants::MARIO_SMALL_FLAG_POLE_1_ATLAS_X * Constants::SPRITE_WIDTH, 0, Constants::SPRITE_WIDTH, Constants::SPRITE_HEIGHT));
		break;
	}
}

void Guy::setCurrentMoveState()
{
	b2Vec2 vel = bodyPtr->GetLinearVelocity();
	if (vel.y != 0)
	{
		currentMoveState = MoveState::JUMPING_UP;
	}
	if (vel.x != 0 && vel.y == 0)
	{
		if (abs(vel.x) > Constants::MAX_WALK_SPEED)
		{
			currentMoveState = MoveState::RUNNING;
		}
		else 
		{
			currentMoveState = MoveState::WALKING;
		}

	}
	if (vel.x == 0 && vel.y == 0)
	{
		currentMoveState = MoveState::IDLE;
	}
}

void Guy::moveSideways()
{
	b2Vec2 vel = bodyPtr->GetLinearVelocity();
	float currentMaxWalkSpeed = Constants::MAX_WALK_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		currentMaxWalkSpeed = Constants::MAX_SPRINT_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		vel.x = b2Max(vel.x - Constants::WALK_FORCE, -currentMaxWalkSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		vel.x = b2Min(vel.x + Constants::WALK_FORCE, currentMaxWalkSpeed);
	}
	else
	{
		vel.x *= 0.999999f;
	}
	bodyPtr->SetLinearVelocity(vel);


	//// TODO : Remove this debug move code below and turn gravity back on.
	// DEBUG ONLY MOVEMENT ALLOW ALL DIRECTIONS
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//{
	//	vel.y = b2Max(vel.y - Constants::WALK_FORCE, -currentMaxWalkSpeed);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//{
	//	vel.y = b2Min(vel.y + Constants::WALK_FORCE, currentMaxWalkSpeed);
	//}
	//bodyPtr->SetLinearVelocity(vel); 
	//// ^^^ REMOVE ^^^
}

void Guy::jump(float deltaSeconds)
{
	RayCastCallback callback_ground;
	b2Vec2 p1 = bodyPtr->GetPosition();
	b2Vec2 p2 = bodyPtr->GetPosition() + b2Vec2(0, 0.51f * sprite.getTextureRect().height);
	worldPtr->RayCast(&callback_ground, p1, p2);
	bool bGrounded = callback_ground.bHit;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		powerJumpTimer += deltaSeconds;
		if (bGrounded)
		{
			powerJumpTimer = 0.f;
			bodyPtr->ApplyLinearImpulseToCenter(b2Vec2(0, Constants::JUMP_FORCE), true);
		}
		else if (powerJumpTimer <= Constants::JUMP_BOOST_TIMER)
		{
			bodyPtr->ApplyLinearImpulseToCenter(b2Vec2(0, Constants::JUMP_BOOST_FORCE), true);
		}
		else 
		{
			return;
		}
	}
	// TODO: Experiment by making this similar function to this but changing vel directly.
}

void Guy::alignSpriteToBody()
{
	sprite.setPosition(bodyPtr->GetPosition().x, bodyPtr->GetPosition().y);
}



void Guy::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

const sf::Vector2<float> Guy::getPosition()
{
	sf::Vector2<float> pos = sf::Vector2<float>(bodyPtr->GetPosition().x, bodyPtr->GetPosition().y);
	return pos;
}

void Guy::flipSpriteWhenTurning()
{
	b2Vec2 vel = bodyPtr->GetLinearVelocity();
	if (vel.x < 0)
	{
		sprite.setScale(-1.f, 1.f);
	}
	if (vel.x > 0)
	{
		sprite.setScale(1.f, 1.f);
	}
}

