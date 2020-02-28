#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include "FixtureUserData.h"


class Guy
{
public:
	Guy();
	void start(b2World* world);
	void update(float deltaSeconds);
	void setCorrectAnimFrame(float deltaSeconds);
	void flipSpriteWhenTurning();
	void setCurrentMoveState();
	void jump(float deltaSeconds);
	void alignSpriteToBody();
	void moveSideways();
	void draw(sf::RenderWindow& window);
	const sf::Vector2<float> getPosition();

private:
	sf::Texture texture;
	sf::Sprite sprite;	
	b2World* worldPtr = nullptr;
	b2BodyDef bodyDef;
	b2Body* bodyPtr = nullptr;
	b2PolygonShape colliderBox;
	b2FixtureDef mainFixture;
	b2PolygonShape topSensorBox;
	b2FixtureDef topSensor;
	float powerJumpTimer;
	enum class MoveState { IDLE, WALKING, RUNNING, SKIDDING, JUMPING_UP, FLAG_POLE };
	MoveState currentMoveState;
	float animFrameDelay;
	float animFrameTimer;
	unsigned int frameIndex;
	FixtureUserData* fixtureData_main = nullptr;
	FixtureUserData* fixtureData_topSensor = nullptr;

};