#include "StdAfx.h"
#include "Player.h"
#include "LevelControl.h"
#include "GridControl.h"

#include <CryRenderer/IRenderAuxGeom.h>

void CPlayerComponent::Initialize()
{
	// Create the camera component, will automatically update the viewport every frame
	m_pCameraComponent = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CCameraComponent>();

	// Get the input component, wraps access to action mapping so we can easily get callbacks when inputs are triggered
	m_pInputComponent = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CInputComponent>();

	// Register an action, and the callback that will be sent when it's triggered
	m_pInputComponent->RegisterAction("player", "moveleft", [this](int activationMode, float value) { HandleInputFlagChange((TInputFlags)EInputFlag::MoveLeft, activationMode);  });
	// Bind the 'A' key the "moveleft" action
	m_pInputComponent->BindAction("player", "moveleft", eAID_KeyboardMouse, EKeyId::eKI_A);

	m_pInputComponent->RegisterAction("player", "moveright", [this](int activationMode, float value) { HandleInputFlagChange((TInputFlags)EInputFlag::MoveRight, activationMode);  });
	m_pInputComponent->BindAction("player", "moveright", eAID_KeyboardMouse, EKeyId::eKI_D);

	m_pInputComponent->RegisterAction("player", "moveforward", [this](int activationMode, float value) { HandleInputFlagChange((TInputFlags)EInputFlag::MoveForward, activationMode);  });
	m_pInputComponent->BindAction("player", "moveforward", eAID_KeyboardMouse, EKeyId::eKI_W);

	m_pInputComponent->RegisterAction("player", "moveback", [this](int activationMode, float value) { HandleInputFlagChange((TInputFlags)EInputFlag::MoveBack, activationMode);  });
	m_pInputComponent->BindAction("player", "moveback", eAID_KeyboardMouse, EKeyId::eKI_S);

	m_pInputComponent->RegisterAction("player", "mouse_rotateyaw", [this](int activationMode, float value) { m_mouseDeltaRotation.x -= value; });
	m_pInputComponent->BindAction("player", "mouse_rotateyaw", eAID_KeyboardMouse, EKeyId::eKI_MouseX);

	m_pInputComponent->RegisterAction("player", "mouse_rotatepitch", [this](int activationMode, float value) { m_mouseDeltaRotation.y -= value; });
	m_pInputComponent->BindAction("player", "mouse_rotatepitch", eAID_KeyboardMouse, EKeyId::eKI_MouseY);

	m_pInputComponent->RegisterAction("player", "spawnall", [this](int activationMode, float value) { HandleInputFlagChange((TInputFlags)EInputFlag::SpawnAll, activationMode);  });
	m_pInputComponent->BindAction("player", "spawnall", eAID_KeyboardMouse, EKeyId::eKI_Space);

	m_pInputComponent->RegisterAction("player", "press1", [this](int activationMode, float value) { HandleInputFlagChange(activationMode, value, EInputType::Press1); });
	m_pInputComponent->BindAction("player", "press1", eAID_KeyboardMouse, EKeyId::eKI_1);

	m_pInputComponent->RegisterAction("player", "press2", [this](int activationMode, float value) { HandleInputFlagChange(activationMode, value, EInputType::Press2); });
	m_pInputComponent->BindAction("player", "press2", eAID_KeyboardMouse, EKeyId::eKI_2);

	m_pInputComponent->RegisterAction("player", "press3", [this](int activationMode, float value) { HandleInputFlagChange(activationMode, value, EInputType::Press3); });
	m_pInputComponent->BindAction("player", "press3", eAID_KeyboardMouse, EKeyId::eKI_3);

	m_pInputComponent->RegisterAction("player", "press4", [this](int activationMode, float value) { HandleInputFlagChange(activationMode, value, EInputType::Press4); });
	m_pInputComponent->BindAction("player", "press4", eAID_KeyboardMouse, EKeyId::eKI_4);

	m_pInputComponent->RegisterAction("player", "press5", [this](int activationMode, float value) { HandleInputFlagChange(activationMode, value, EInputType::Press5); });
	m_pInputComponent->BindAction("player", "press5", eAID_KeyboardMouse, EKeyId::eKI_5);

	m_pInputComponent->RegisterAction("player", "press6", [this](int activationMode, float value) { HandleInputFlagChange(activationMode, value, EInputType::Press6); });
	m_pInputComponent->BindAction("player", "press6", eAID_KeyboardMouse, EKeyId::eKI_6);

	m_pInputComponent->RegisterAction("player", "press7", [this](int activationMode, float value) { HandleInputFlagChange(activationMode, value, EInputType::Press7); });
	m_pInputComponent->BindAction("player", "press7", eAID_KeyboardMouse, EKeyId::eKI_7);

	m_pInputComponent->RegisterAction("player", "press8", [this](int activationMode, float value) { HandleInputFlagChange(activationMode, value, EInputType::Press8); });
	m_pInputComponent->BindAction("player", "press8", eAID_KeyboardMouse, EKeyId::eKI_8);

	m_pInputComponent->RegisterAction("player", "press9", [this](int activationMode, float value) { HandleInputFlagChange(activationMode, value, EInputType::Press9); });
	m_pInputComponent->BindAction("player", "press9", eAID_KeyboardMouse, EKeyId::eKI_9);

	m_pInputComponent->RegisterAction("player", "pressEsc", [this](int activationMode, float value) { HandleInputFlagChange(activationMode, value, EInputType::PressEsc); });
	m_pInputComponent->BindAction("player", "pressEsc", eAID_KeyboardMouse, EKeyId::eKI_R);

	Revive();
}

uint64 CPlayerComponent::GetEventMask() const
{
	return BIT64(ENTITY_EVENT_START_GAME) | BIT64(ENTITY_EVENT_UPDATE);
}

void CPlayerComponent::ProcessEvent(SEntityEvent& event)
{
	switch (event.event)
	{
	case ENTITY_EVENT_START_GAME:
	{
		// Revive the entity when gameplay starts
		Revive();
	}
	break;
	case ENTITY_EVENT_UPDATE:
	{
		SEntityUpdateContext* pCtx = (SEntityUpdateContext*)event.nParam[0];

		const float moveSpeed = 20.5f;
		Vec3 velocity = ZERO;

		// Check input to calculate local space velocity
		if (m_inputFlags & (TInputFlags)EInputFlag::MoveLeft)
		{
			velocity.x -= moveSpeed * pCtx->fFrameTime;
		}
		if (m_inputFlags & (TInputFlags)EInputFlag::MoveRight)
		{
			velocity.x += moveSpeed * pCtx->fFrameTime;
		}
		if (m_inputFlags & (TInputFlags)EInputFlag::MoveForward)
		{
			velocity.y += moveSpeed * pCtx->fFrameTime;
		}
		if (m_inputFlags & (TInputFlags)EInputFlag::MoveBack)
		{
			velocity.y -= moveSpeed * pCtx->fFrameTime;
		}

		if (m_inputFlags & (TInputFlags)EInputFlag::SpawnAll)
		{
			if (!spawnOnce)
			{
			
				SEntitySpawnParams sLevelControlParams;
				sLevelControlParams.pClass = gEnv->pEntitySystem->GetClassRegistry()->GetDefaultClass();
				sLevelControlParams.vPosition = Vec3(512.0f, 512.0f, 36.0f);

				IEntity* pSpawnedLevelController = gEnv->pEntitySystem->SpawnEntity(sLevelControlParams);
				pSpawnedLevelController->GetOrCreateComponentClass<CLevelControl>();
				pSpawnedLevelController->PrePhysicsActivate(true);

				spawnOnce = true;
			}
		}

		if (!pressOnce)
		{
			if (m_currentInput == EInputType::Press1)
			{
				CryLogAlways("1 Pressed");
				m_currentInput = EInputType::None;
				SelectGrid(0);
				pressOnce = true;
			}
			else if (m_currentInput == EInputType::Press2)
			{
				CryLogAlways("2 Pressed");
				m_currentInput = EInputType::None;
				SelectGrid(1);
				pressOnce = true;
			}
			else if (m_currentInput == EInputType::Press3)
			{
				CryLogAlways("3 Pressed");
				m_currentInput = EInputType::None;
				SelectGrid(2);
				pressOnce = true;
			}
			else if (m_currentInput == EInputType::Press4)
			{
				CryLogAlways("4 Pressed");
				m_currentInput = EInputType::None;
				SelectGrid(3);
				pressOnce = true;
			}
			else if (m_currentInput == EInputType::Press5)
			{
				CryLogAlways("5 Pressed");
				m_currentInput = EInputType::None;
				SelectGrid(4);
				pressOnce = true;
			}
			else if (m_currentInput == EInputType::Press6)
			{
				CryLogAlways("6 Pressed");
				m_currentInput = EInputType::None;
				SelectGrid(5);
				pressOnce = true;
			}
			else if (m_currentInput == EInputType::Press7)
			{
				CryLogAlways("7 Pressed");
				m_currentInput = EInputType::None;
				SelectGrid(6);
				pressOnce = true;
			}
			else if (m_currentInput == EInputType::Press8)
			{
				CryLogAlways("8 Pressed");
				m_currentInput = EInputType::None;
				SelectGrid(7);
				pressOnce = true;
			}
			else if (m_currentInput == EInputType::Press9)
			{
				CryLogAlways("9 Pressed");
				m_currentInput = EInputType::None;
				SelectGrid(8);
				pressOnce = true;
			}
		}

		//////ESC
		if (m_currentInput == EInputType::PressEsc)
		{
			CryLogAlways("R Pressed");
			ResetBools();
			m_currentInput = EInputType::None;
		}

		// Update the player's transformation
		Matrix34 transformation = m_pEntity->GetWorldTM();
		transformation.AddTranslation(transformation.TransformVector(velocity));

		// Update entity rotation based on latest input
		Ang3 ypr = CCamera::CreateAnglesYPR(Matrix33(transformation));

		const float rotationSpeed = 0.002f;
		ypr.x += m_mouseDeltaRotation.x * rotationSpeed;
		ypr.y += m_mouseDeltaRotation.y * rotationSpeed;

		// Disable roll
		ypr.z = 0;

		transformation.SetRotation33(CCamera::CreateOrientationYPR(ypr));

		// Reset the mouse delta since we "used" it this frame
		m_mouseDeltaRotation = ZERO;

		// Apply set position and rotation to the entity
		m_pEntity->SetWorldTM(transformation);
	}
	break;
	}
}

void CPlayerComponent::Revive()
{
	ResetBools();
	// Set player transformation, but skip this in the Editor
	if (!gEnv->IsEditor())
	{
		Vec3 playerScale = Vec3(1.f);
		Quat playerRotation = IDENTITY;

		// Position the player in the center of the map
		const float heightOffset = 20.f;
		float terrainCenter = gEnv->p3DEngine->GetTerrainSize() / 2.f;
		float height = gEnv->p3DEngine->GetTerrainZ(static_cast<int>(terrainCenter), static_cast<int>(terrainCenter));
		Vec3 playerPosition = Vec3(terrainCenter, terrainCenter, height + heightOffset);

		m_pEntity->SetWorldTM(Matrix34::Create(playerScale, playerRotation, playerPosition));
	}
	else {
		Vec3 playerScale = Vec3(1.f);
		Quat playerRotation = IDENTITY;

		// Position the player in the center of the map
		const float heightOffset = 20.f;
		float terrainCenter = gEnv->p3DEngine->GetTerrainSize() / 2.f;
		float height = gEnv->p3DEngine->GetTerrainZ(static_cast<int>(terrainCenter), static_cast<int>(terrainCenter));
		Vec3 playerPosition = Vec3(terrainCenter, terrainCenter, height + heightOffset);

		m_pEntity->SetWorldTM(Matrix34::Create(playerScale, playerRotation, playerPosition));

		
	}

	// Unhide the entity in case hidden by the Editor
	GetEntity()->Hide(false);

	// Reset input now that the player respawned
	m_inputFlags = 0;
	m_mouseDeltaRotation = ZERO;
}

void CPlayerComponent::ResetBools()
{
	CryLogAlways("Resetting bools");
	spawnOnce = false;
	pressOnce = false;
}

void CPlayerComponent::SelectGrid(int number)
{
	std::string gridName = std::to_string(number);
	const char* chr = gridName.c_str();
	selectedGrid = gEnv->pEntitySystem->FindEntityByName(chr);
	if (selectedGrid)
	{
		selectedGrid->GetComponent<CGridControl>()->startUpAnimation = true;
		selectedGrid = nullptr;
	}
	else
	{
		ResetBools();
	}
}

void CPlayerComponent::HandleInputFlagChange(TInputFlags flags, int activationMode, EInputFlagType type)
{
	switch (type)
	{
	case EInputFlagType::Hold:
	{
		if (activationMode == eIS_Released)
		{
			m_inputFlags &= ~flags;
		}
		else
		{
			m_inputFlags |= flags;
		}
	}
	break;
	case EInputFlagType::Toggle:
	{
		if (activationMode == eIS_Released)
		{
			// Toggle the bit(s)
			m_inputFlags ^= flags;
		}
	}
	break;
	}
}

void CPlayerComponent::HandleInputFlagChange(int activationMode, float value, EInputType inputType)
{
	m_currentInput = inputType;
}
