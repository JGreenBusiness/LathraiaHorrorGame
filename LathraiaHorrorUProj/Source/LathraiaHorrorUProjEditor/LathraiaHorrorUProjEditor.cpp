#include "LathraiaHorrorUProjEditor.h"

#include "ViewConeVisualizer.h"
#include "LathraiaHorrorUProj/AI/ViewConeComponent.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE(FLathraiaHorrorUProjEditorModule, LathraiaHorrorUProjEditor)

void FLathraiaHorrorUProjEditorModule::StartupModule()
{
	// Check if editor valid
	if (GUnrealEd)
	{
		// Make a new instance of the visualizer
		TSharedPtr<FComponentVisualizer> Visualizer = MakeShareable(new FViewConeVisualizer());

		// Register it to our specific component class
		GUnrealEd->RegisterComponentVisualizer(UViewConeComponent::StaticClass()->GetFName(), Visualizer);
		Visualizer->OnRegister();
	}

	// Add a section filter for the 'Eye Stalk' category, on the EyeStalk class
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	{
		TSharedRef<FPropertySection> Section = PropertyModule.FindOrCreateSection("EyeStalk", "Eye Stalk", FText::FromString("Eye Stalk"));
		Section->AddCategory("Eye Stalk");
	}
	PropertyModule.NotifyCustomizationModuleChanged();
}

void FLathraiaHorrorUProjEditorModule::ShutdownModule()
{
	// Check if editor valid
	if (GUnrealEd)
	{
		// Unregister when the module shuts down
		GUnrealEd->UnregisterComponentVisualizer(UViewConeComponent::StaticClass()->GetFName());
	}
}