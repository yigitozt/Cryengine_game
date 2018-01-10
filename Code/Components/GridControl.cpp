#include "StdAfx.h"
#include "GridControl.h"

void CGridControl::Initialize()
{
	//gridName = std::string("Grid" + std::to_string(gridId));
	

	GetEntity()->LoadGeometry(0, "objects/myobjects/box/box_fbx.cgf");
	

	

	gEnv->pRenderer->SetMaterialColor(0.8f,0.7f,0.2f,1.0f);

	//IMaterial* pMyMaterial = GetEntity()->GetMaterial();
	//gEnv->p3DEngine->GetMaterialManager()->CloneMaterial(pMyMaterial);
}

void CGridControl::InitAfterSpawn() 
{
	animTimer = gridId * 0.1f;

	std::string gridName = std::to_string(gridId);
	const char* chr = gridName.c_str();

	GetEntity()->SetName(chr);

	CryLogAlways("Grid : %s is spawned", GetEntity()->GetName());
}

void CGridControl::ProcessEvent(SEntityEvent& event)
{
	FrameUpdate();
}

void CGridControl::FrameUpdate()
{
	//gameloop for gridcontrol here <<<>>>

	if (animTimer <= 0)
	{
		startAnimating = true;
	}
	else
	{
		animTimer -= 0.1f;
	}

	if (startAnimating)
	{
		if (scaleValue < 10.0f)
		{
			scaleValue += 0.1f;
		}
		else
		{
			scaleValue = 10.0f;
		}

		GetEntity()->SetScale(Vec3(scaleValue, scaleValue, scaleValue));

		if (rotationValue < 15.0f)
		{
			rotationValue += 0.1f;
		}
		else {
			rotationValue = 15.0f;
		}


		Quat qRotate = Quat::CreateRotationXYZ(Ang3(Vec3(0, 0, rotationValue)));
		GetEntity()->SetRotation(qRotate);
	}


	if (startUpAnimation)
	{
		Vec3 curPos = GetEntity()->GetPos();

		if (GetEntity()->GetPos().z < 38.0f)
		{
			GetEntity()->SetPos(curPos + Vec3(0,0,0.1f));
		}
	}
	
}