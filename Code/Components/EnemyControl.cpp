#include "StdAfx.h"
#include "EnemyControl.h"
#include "Bullet.h"

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

	spawnTimer -= 0.01f;

	if (spawnTimer <= 0)
	{
		ShootBullet(GetEntity()->GetPos());
		spawnTimer = 2.0f;
	}

	
}


void CEnemyControl::ShootBullet(Vec3 pos)
{
	SEntitySpawnParams sBulletParams;
	sBulletParams.pClass = gEnv->pEntitySystem->GetClassRegistry()->GetDefaultClass();
	sBulletParams.vPosition = pos;

	IEntity* pSpawnedBullet = gEnv->pEntitySystem->SpawnEntity(sBulletParams);
	pSpawnedBullet->GetOrCreateComponentClass<CBullet>();
	pSpawnedBullet->PrePhysicsActivate(true);
}

