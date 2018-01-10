#include "StdAfx.h"
#include "LevelControl.h"
#include "GridControl.h"
#include "BallControl.h"

void CLevelControl::Initialize()
{
	CryLogAlways("Level Controller Spawned");
	GetEntity()->LoadGeometry(0, "objects/myobjects/Wooden Crate.cgf");
	GetEntity()->SetName("LevelControlObject");

	randomSelectedCube = rand() % 10;

	//SpawnEnemy(Vec3(518.0f, 518.0f, 36.0f));
	CreateEmptyGrid(3, Vec3(518.0f, 518.0f, 33.0f));
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

void CLevelControl::ProcessEvent(SEntityEvent& event)
{
	FrameUpdate();
}

void CLevelControl::FrameUpdate()
{
	//gameloop for levelcontrol here <<<>>>
	
}

void CLevelControl::SelectGrid(int selectedGrid)
{
	if (selectedGrid == randomSelectedCube)
	{
		
	}
	else
	{

	}
}

void CLevelControl::CreateEmptyGrid(int gridSize, Vec3 anchorPosition)
{
	int currentGrid = 1;
	int currentLine = 0;
	Vec3 spawnPosition = Vec3(0, 0, 0);
	float xPos = anchorPosition.x;
	float initialXPos = anchorPosition.x;
	float yPos = anchorPosition.y;
	float zPos = anchorPosition.z;


	for (int i = 0; i < gridSize*gridSize; i++)
	{
		spawnPosition = Vec3(xPos, yPos, zPos);

		SEntitySpawnParams sGridControlParams;
		sGridControlParams.pClass = gEnv->pEntitySystem->GetClassRegistry()->GetDefaultClass();
		sGridControlParams.vPosition = spawnPosition;

		IEntity* pSpawnedGridControl = gEnv->pEntitySystem->SpawnEntity(sGridControlParams);
		pSpawnedGridControl->GetOrCreateComponentClass<CGridControl>();
		pSpawnedGridControl->GetComponent<CGridControl>()->gridId = gridCounter;
		pSpawnedGridControl->GetComponent<CGridControl>()->InitAfterSpawn();
		pSpawnedGridControl->PrePhysicsActivate(true);

		xPos += spaceBtwCubes;

		if (i == randomSelectedCube)
		{
			//placing ball here

			SEntitySpawnParams sBallControlParams;
			sBallControlParams.pClass = gEnv->pEntitySystem->GetClassRegistry()->GetDefaultClass();
			sBallControlParams.vPosition = spawnPosition;

			IEntity* pSpawnedBallControl = gEnv->pEntitySystem->SpawnEntity(sBallControlParams);
			pSpawnedBallControl->GetOrCreateComponentClass<CBallControl>();
		}

		if (currentGrid >= gridSize)
		{
			currentLine += 1;
			currentGrid = 0;
			xPos = initialXPos;
			yPos += spaceBtwCubes;
		}

		

		currentGrid += 1;
		gridCounter += 1;
	
	}
}

void CLevelControl::LevelOver(bool isGameOver)
{
	if (!isGameOver)
	{
		//level completed

	}
	else
	{
		//level failed

	}

}

