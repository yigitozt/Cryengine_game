#pragma once

#include <CryEntitySystem/IEntityComponent.h>
#include <CryEntitySystem/IEntitySystem.h>
#include "GamePlugin.h"

class CEnemyControl : public IEntityComponent {
public:
	CEnemyControl() {};
	~CEnemyControl() {};


	static void ReflectType(Schematyc::CTypeDesc<CEnemyControl>& desc)
	{
		desc.SetGUID("{75FC493C-A5CA-485B-952D-22784CFF527F}"_cry_guid);
		desc.SetLabel("EnemyControl");
	}

	virtual void Initialize() override;
	virtual uint64 GetEventMask() const override { return BIT64(ENTITY_EVENT_UPDATE); }
	virtual void ProcessEvent(SEntityEvent& event) override;

private:
	IEntity * pPlayer = nullptr;

private:
	void FrameUpdate();
	void ShootBullet(IEntity* bullet);
};