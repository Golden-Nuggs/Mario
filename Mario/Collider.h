#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>

class Collider
{
public:
	Collider();
	void start(tmx::FloatRect AABB, b2World* world);


private:
	b2World* worldPtr = nullptr;
	b2BodyDef bodyDef;
	b2Body* bodyPtr = nullptr;
	b2PolygonShape box;
};