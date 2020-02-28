#include "Collider.h"


Collider::Collider()
{
}

void Collider::start(tmx::FloatRect AABB, b2World* world)
{
	worldPtr = world;

	float hx = AABB.width / 2.f;
	float hy = AABB.height / 2.f;
	bodyDef.position.Set(AABB.left + hx, AABB.top + hy);

	box.SetAsBox(hx, hy);

	bodyPtr = worldPtr->CreateBody(&bodyDef);
	bodyPtr->CreateFixture(&box, 0.f);
}
