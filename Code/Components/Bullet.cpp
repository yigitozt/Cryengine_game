#include "Bullet.h"
#include "StdAfx.h"

void CBullet::Initialize()
{
	pPlayer = gEnv->pEntitySystem->FindEntityByName("Player");
	GetEntity()->LoadGeometry(0, "objects/myobjects/simple/primitive_sphere.cgf");
	
}

void CBullet::ProcessEvent(SEntityEvent& event)
{
	FrameUpdate();
}

void CBullet::LookAt(IEntity* target)
{
	if (GetEntity()->GetPos() - target->GetPos() == Vec3(0, 0, 0))
		return;

	Vec3 direction = (GetEntity()->GetPos() - target->GetPos()).Normalize();

	GetEntity()->SetRotation(Quat::CreateRotationVDir(target->GetPos()));
}

void CBullet::FrameUpdate()
{
	if (pPlayer)
	{
		Vec3 curPos = GetEntity()->GetPos();
		Vec3 moveDir = Vec3(0.5f, 0, 0);

		GetEntity()->SetPos(curPos + moveDir);
	}
}
