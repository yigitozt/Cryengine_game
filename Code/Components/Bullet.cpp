#include "Bullet.h"
#include "StdAfx.h"

void CBullet::Initialize()
{
	pPlayer = gEnv->pEntitySystem->FindEntityByName("Player");
	GetEntity()->Physicalize() {

	};
	
}

void CBullet::ProcessEvent(SEntityEvent& event)
{
	FrameUpdate();
}

void CBullet::FrameUpdate()
{

}