#include "LathraiaHorrorUProjEditor.h"

#include "EyeStalkVisualizer.h"
#include "EyeStalkVisualizerComponent.h"

#include "UnrealEd.h"

IMPLEMENT_GAME_MODULE(FLathraiaHorrorUProjEditorModule, LathraiaHorrorUProjEditor)

void FLathraiaHorrorUProjEditorModule::StartupModule()
{
	// Check if editor valid
	if (GUnrealEd)
	{
		// Make a new instance of the visualizer
		TSharedPtr<FComponentVisualizer> Visualizer = MakeShareable(new FEyeStalkVisualizer());

		// Register it to our specific component class
		GUnrealEd->RegisterComponentVisualizer(UEyeStalkVisualizerComponent::StaticClass()->GetFName(), Visualizer);
		Visualizer->OnRegister();
	}

	// Add section filters for custom classes ...
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	{
		// ... EyeStalk
		TSharedRef<FPropertySection> Section_EyeStalk = PropertyModule.FindOrCreateSection("EyeStalk", "Eye Stalk", FText::FromString("Eye Stalk"));
		Section_EyeStalk->AddCategory("Eye Stalk Config: General");
		Section_EyeStalk->AddCategory("Eye Stalk Config: Info");
		Section_EyeStalk->AddCategory("Eye Stalk Config: Awareness Modifiers");
		Section_EyeStalk->AddCategory("Eye Stalk Config: Mode Modifiers");
		Section_EyeStalk->AddCategory("View Cone");

		// ... Tendril
		TSharedRef<FPropertySection> Section_Tendril = PropertyModule.FindOrCreateSection("Tendril", "Tendril", FText::FromString("Tendril"));
		Section_Tendril->AddCategory("Tendril Config: General");
	}
	PropertyModule.NotifyCustomizationModuleChanged();
}

void FLathraiaHorrorUProjEditorModule::ShutdownModule()
{
	// Check if editor valid
	if (GUnrealEd)
	{
		// Unregister when the module shuts down
		GUnrealEd->UnregisterComponentVisualizer(UEyeStalkVisualizerComponent::StaticClass()->GetFName());
	}
}