#pragma once

#include <CryEntitySystem/IEntityComponent.h>
#include <CryEntitySystem/IEntitySystem.h>
#include "GamePlugin.h"

class CBallControl : public IEntityComponent
{
public:
	CBallControl(){};
	~CBallControl(){};

	static void ReflectType(Schematyc::CTypeDesc<CBallControl>& desc)
	{
		desc.SetGUID("{82449574-2093-48B2-900E-81D82200EFA5}"_cry_guid);
		desc.SetLabel("Ball");
	}

	virtual void Initialize() override;

};