#pragma once

#include "Engine.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "UnrealEd.h"

DECLARE_LOG_CATEGORY_EXTERN(LathraiaHorrorUProjEditor, All, All)

class FLathraiaHorrorUProjEditorModule : public IModuleInterface
{
public:
	void StartupModule() override;
	void ShutdownModule() override;
};