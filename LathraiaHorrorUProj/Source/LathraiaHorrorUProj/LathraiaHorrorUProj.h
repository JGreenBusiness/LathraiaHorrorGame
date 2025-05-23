// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FYourGameModule : public IModuleInterface 
{
public:
    virtual void StartupModule() override;
    virtual bool IsGameModule() const override { return true; }

private:
    void SetConfigKeyValue(FString ConfigFileName, FString Section, FString Key, FString KeyValue);

    FString GetGitCommitHash();
};


