// Fill out your copyright notice in the Description page of Project Settings.


#include "Lantern.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values
ALantern::ALantern()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALantern::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(this, 0);
	USkeletalMeshComponent* playerMesh = player->GetMesh();

	LanternSockets.Add(ELanternSocketType::ELST_Held, playerMesh->GetSocketByName(HeldLanternSocketName));
	LanternSockets.Add(ELanternSocketType::ELST_Stowed, playerMesh->GetSocketByName(StowedLanternSocketName));
	LanternSockets.Add(ELanternSocketType::ELST_Rekindle, playerMesh->GetSocketByName(RekindleLanternSocketName));


	if (bSpawnOnPlayer)
	{
		if (const USkeletalMeshSocket* defaultSocket = *LanternSockets.Find(DefaultLanternSocket))
		{
			AttachToComponent(playerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, defaultSocket->SocketName);
		}
	}
}


// Called every frame
void ALantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

