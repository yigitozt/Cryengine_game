#pragma once

#include <CryEntitySystem/IEntityComponent.h>
#include <CryEntitySystem/IEntitySystem.h>
#include "GamePlugin.h"

class CGridControl:public IEntityComponent
{
public:
	CGridControl() {};
	~CGridControl() {};

	static void ReflectType(Schematyc::CTypeDesc<CGridControl>& desc)
	{
		desc.SetGUID("{00ADF9A9-61CE-44FE-9757-496C250DEE59}"_cry_guid);
		desc.SetLabel("LevelControl");
	}

	virtual void Initialize() override;
	virtual uint64 GetEventMask() const override { return BIT64(ENTITY_EVENT_UPDATE); }
	virtual void ProcessEvent(SEntityEvent& event) override;
	void InitAfterSpawn();

public:

	int gridId = 0;
	int currentState = 0;
	bool selected = false;
	bool startUpAnimation = false;

private:

	void FrameUpdate();

private:

	float scaleValue = 0;
	float rotationValue = 0;
	float animTimer = 0;
	bool startAnimating = false;
};