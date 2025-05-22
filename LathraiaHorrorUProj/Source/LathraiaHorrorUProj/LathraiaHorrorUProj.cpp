// Copyright Epic Games, Inc. All Rights Reserved.

#include "LathraiaHorrorUProj.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FYourGameModule, LathraiaHorrorUProj, "LathraiaHorrorUProj");

void FYourGameModule::StartupModule() 
{
    SetConfigKeyValue(
        "DefaultEngine.ini",
        "[/Game/Developers/ethan/Blueprints/UI/WBP_MainMenu.WBP_MainMenu_C]",
        "VersionNumber=",
        GetGitCommitHash()
    );
}


void FYourGameModule::SetConfigKeyValue(FString ConfigFileName, FString Section, FString Key, FString KeyValue)
{
    FString ConfigFilePath = FPaths::ProjectConfigDir() + ConfigFileName;

    FJsonSerializableArray Lines;
    FFileHelper::LoadFileToStringArray(Lines, *ConfigFilePath);

    int32 SectionIndex = -1, KeyIndex = -1;

    // Loop over all lines of the config file, storing the section and key line indexes
    for (int Index = 0; Index < Lines.Num(); Index++)
    {
        if (Lines[Index] == Section)
        {
            SectionIndex = Index;
        }

        if (SectionIndex != -1 && Lines[Index].StartsWith(Key))
        {
            KeyIndex = Index;
        }
    }

    FString NewKeyValue = Key + KeyValue;

    // Set the key value appropriately
    if (KeyIndex == -1)
    {
        if (SectionIndex == -1) // Section => Not found, Key => Not found
        {
            Lines.Add(""); // ensure empty line gap for new section
            Lines.Add(Section);
            Lines.Add(NewKeyValue);
        }
        else // Section => Found, Key => Not found
        {
            Lines.Insert(NewKeyValue, SectionIndex + 1); // add key directly after section line
        }
    }
    else // Section => Found, Key => Found
    {
        Lines[KeyIndex] = NewKeyValue;
    }

    FFileHelper::SaveStringArrayToFile(Lines, *ConfigFilePath);
}

FString FYourGameModule::GetGitCommitHash()
{
    FString Output;
    FString ErrorStr;
    int32 ReturnCode;

    FPlatformProcess::ExecProcess(TEXT("git"), TEXT("rev-parse HEAD"), &ReturnCode, &Output, &ErrorStr, *FPaths::ProjectDir());

    if (ReturnCode == 0)
    {
        Output = Output.Replace(TEXT("\n"), TEXT("")).Replace(TEXT("\r"), TEXT("")); // clean-up output
    }
    else
    {
        Output = "XXXXxxxxXXXXxxxx";
    }

    return Output;
}
