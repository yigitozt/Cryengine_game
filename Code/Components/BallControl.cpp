#include "BallControl.h"

void CBallControl::Initialize()
{
	CryLogAlways("BAll Spawned");
	GetEntity()->LoadGeometry(0, "objects/myobjects/simple/primitive_sphere.cgf");
	GetEntity()->SetName("Ball");
	//GetEntity()->SetScale(Vec3(0.5f,0.5f,0.5f));
}