// Copyright Epic Games, Inc. All Rights Reserved.


#include "StarFighterGameModeBase.h"


void AStarFighterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	bPlayerDead = false;

	//Implementamos nuestros widgets

	if (Score_Widget_Class)
	{
		Score_Widget = CreateWidget<UUserWidget>(GetWorld(), Score_Widget_Class);
		Score_Widget->AddToViewport();
	}

	if (Health_And_Armor_Class)
	{
		Health_And_Armor_Widget = CreateWidget<UUserWidget>(GetWorld(), Health_And_Armor_Class);
		Health_And_Armor_Widget->AddToViewport();
	}

	PC_Ref = GetWorld()->GetFirstPlayerController();

}
void AStarFighterGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnTimer = FMath::RandRange(0, 1000);

	//Le damos un spawn a nuestros enemigos y asteroides

	if (Enemy && SpawnTimer > 990)
	{
		FVector EnemySpawnLoc(0.0f, 0.0f, 0.0f);
		FRotator EnemySpawnRot(0.0f, 0.0f, 0.0f);

		AActor* NewEnemy = GetWorld()->SpawnActor(Enemy, &EnemySpawnLoc, &EnemySpawnRot, AsteroidSpawnParams);

		if (NewEnemy)
			NewEnemy->SetActorLocation(FVector(1000.0f, FMath::RandRange(-500, 500), 0.0f));
	}

	if (AsteroideTemplate && SpawnTimer > 995)
		GetWorld()->SpawnActor(AsteroideTemplate, &AsteroidSpawnLocation, &AsteroidSpawnRotation, AsteroidSpawnParams);

}

TSubclassOf<APickup2> AStarFighterGameModeBase::GetAsteroideTemplate()
{
	return TSubclassOf<APickup2>();
}
