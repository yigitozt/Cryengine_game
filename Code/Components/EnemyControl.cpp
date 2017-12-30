#include "EnemyControl.h"
#include "StdAfx.h"

void CEnemyControl::Initialize()
{
	CryLogAlways("Enemy Spawned");
	GetEntity()->LoadGeometry(0, "objects/myobjects/simple/primitive_box.cgf");

	pPlayer = gEnv->pEntitySystem->FindEntityByName("Player");
}


void CEnemyControl::ProcessEvent(SEntityEvent& event)
{
	FrameUpdate();
}

void CEnemyControl::FrameUpdate()
{
	Vec3 curPos = GetEntity()->GetPos();
	Vec3 moveDir = Vec3(0.1f, 0, 0);

	GetEntity()->SetPos(curPos + moveDir);
}