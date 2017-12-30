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
	void SpawnEnemy(Vec3 pos);

	

private:



};