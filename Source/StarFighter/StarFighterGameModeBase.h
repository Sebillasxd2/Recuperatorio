// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "NaveTerrestreEnemiga01.h"
#include "Pickup2.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "StarFighterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API AStarFighterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		//Agarramos nuestros blueprints para poder utilizarlos y crear un spawn

	UPROPERTY(EditAnywhere)
		TSubclassOf<ANaveTerrestreEnemiga01> Enemy;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APickup2> AsteroideTemplate;

	AStarFighterGameModeBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	TSubclassOf<APickup2> GetAsteroideTemplate();

public:
	int32 SpawnTimer;
	bool bPlayerDead;
	bool bStart;

protected:
	FActorSpawnParameters AsteroidSpawnParams;
	FVector AsteroidSpawnLocation;
	FRotator AsteroidSpawnRotation;

	UWorld* ThisWorld;

	//Declaramos nuestros widgets

	UPROPERTY(EditAnywhere, Category = "HUD Elements")
		TSubclassOf<UUserWidget> Score_Widget_Class;
	UUserWidget* Score_Widget;

	UPROPERTY(EditAnywhere, Category = "HUD Elements")
		TSubclassOf<UUserWidget> Health_And_Armor_Class;
	UUserWidget* Health_And_Armor_Widget;

	APlayerController* PC_Ref;
};