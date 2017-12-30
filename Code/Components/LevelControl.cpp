#include "LevelControl.h"
#include "StdAfx.h"


void CLevelControl::Initialize()
{
	CryLogAlways("Level Controller Spawned");
	GetEntity()->LoadGeometry(0, "objects/myobjects/Wooden Crate.cgf");

	SpawnEnemy(Vec3(518.0f, 518.0f, 36.0f));
}

void CLevelControl::SpawnEnemy(Vec3 pos)
{
	SEntitySpawnParams sEnemyControlParams;
	sEnemyControlParams.pClass = gEnv->pEntitySystem->GetClassRegistry()->GetDefaultClass();
	sEnemyControlParams.vPosition = pos;

	IEntity* pSpawnedEnemyControl = gEnv->pEntitySystem->SpawnEntity(sEnemyControlParams);
	pSpawnedEnemyControl->GetOrCreateComponentClass<CEnemyControl>();
	pSpawnedEnemyControl->PrePhysicsActivate(true);
}

