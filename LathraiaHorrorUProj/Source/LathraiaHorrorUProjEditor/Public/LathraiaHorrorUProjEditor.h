#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class FLathraiaHorrorUProjEditorModule : public IModuleInterface
{
public:
	void StartupModule() override;
	void ShutdownModule() override;
};