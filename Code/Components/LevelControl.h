#pragma once

#include <CryEntitySystem/IEntityComponent.h>
#include <CryEntitySystem/IEntitySystem.h>
#include "GamePlugin.h"

class CLevelControl : public IEntityComponent
{
public:
	CLevelControl() {};
	~CLevelControl() {};

	static void ReflectType(Schematyc::CTypeDesc<CLevelControl>& desc)
	{
		desc.SetGUID("{5C4C7138-830A-4B94-9EF4-AEC473B42506}"_cry_guid);
		desc.SetLabel("LevelControl");
	}

	virtual void Initialize() override;
	virtual uint64 GetEventMask() const override { return BIT64(ENTITY_EVENT_UPDATE); }
	virtual void ProcessEvent(SEntityEvent& event) override;
	void SpawnEnemy(Vec3 pos);
	void LevelOver(bool isGameOver);
	void SelectGrid(int selectedGrid);

private:

	void FrameUpdate();
	void CreateEmptyGrid(int gridSize, Vec3 anchorPosition);

private:

	int gridCounter = 0;
	const float spaceBtwCubes = 5.0f;
	int randomSelectedCube = 0;
};