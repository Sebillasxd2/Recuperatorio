// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pickup1.h"
#include "Proyectil.h"
#include "NaveTerrestre.h"
#include "NaveTerrestreEnemiga01.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API ANaveTerrestreEnemiga01 : public ANaveTerrestre
{
	GENERATED_BODY()
public:
	ANaveTerrestreEnemiga01();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProyectil> EnemyProjectile_BP;

	UWorld* ThisWorld;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APickup1> Pickup_Can;

	UPROPERTY(EditAnywhere)
		FVector Current_Velocity;
	void UpdateMovement(float DeltaTime);
	void UpdateFiring(float DeltaTime);

	FVector Current_Location;
	FRotator Current_Rotation;

	float TotalTime;
	float TimeSinceLastShot;
	float RandomStart;
	float fDestroyTimer;
	float fBurstDelay;

	bool bHit;
	bool bDead;

	UFUNCTION()
		void OnBeginOverlap(AActor* EnemyActor, AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
