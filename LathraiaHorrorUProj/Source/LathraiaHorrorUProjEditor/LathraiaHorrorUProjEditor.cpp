#include "LathraiaHorrorUProjEditor.h"

#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE(FLathraiaHorrorUProjEditorModule, LathraiaHorrorUProjEditor)

void FLathraiaHorrorUProjEditorModule::StartupModule()
{
	// Check if editor valid
	if (GUnrealEd)
	{
		// Make a new instance of the visualizer
		// TSharedPtr<FComponentVisualizer> Visualizer = MakeShareable(new FComponentVisualizer());

		// Register it to our specific component class
		// GUnrealEd->RegisterComponentVisualizer(UActorComponent::StaticClass()->GetFName(), Visualizer);
		// Visualizer->OnRegister();
	}
}

void FLathraiaHorrorUProjEditorModule::ShutdownModule()
{
	// Check if editor valid
	if (GUnrealEd)
	{
		// Unregister when the module shuts down
		// GUnrealEd->UnregisterComponentVisualizer(UActorComponent::StaticClass()->GetFName());
	}
}