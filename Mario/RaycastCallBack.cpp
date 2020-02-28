#include "RaycastCallBack.h"

RayCastCallback::RayCastCallback()
{
	bHit = false;
	out_fraction = 0;
}

float RayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
	bHit = true;
	out_fixture = fixture;
	out_point = point;
	out_normal = normal;
	out_fraction = fraction;
	return 0; // there a different options for return here that allow the ray to continue or stop etc (see notes in base class) 
}
