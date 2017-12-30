#pragma once

#include <CryEntitySystem/IEntityComponent.h>
#include <CryEntitySystem/IEntitySystem.h>
#include "GamePlugin.h"

class CBullet : public IEntityComponent 
{
public:
	CBullet() {};
	~CBullet() {};

	static void ReflectType(Schematyc::CTypeDesc<CBullet>& desc)
	{
		desc.SetGUID("{98E8BB26-417F-45B9-B96A-FD7B15CDEB44}"_cry_guid);
		desc.SetLabel("Bullet");
	}

	virtual void Initialize() override;
	virtual uint64 GetEventMask() const override { return BIT64(ENTITY_EVENT_UPDATE); }
	virtual void ProcessEvent(SEntityEvent& event) override;

private:
	IEntity * pPlayer = nullptr;

private:
	void FrameUpdate();
	void LookAt(IEntity* target);
};