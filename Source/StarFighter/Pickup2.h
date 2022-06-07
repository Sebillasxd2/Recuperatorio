// Fill out your copyright notice in the Description page of Project Settings.
//ESTE PICKUP: enrealidad son los asteroides pero me confundi al escribir el nombre
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Pickup2.generated.h"

UCLASS()
class STARFIGHTER_API APickup2 : public AActor
{
	GENERATED_BODY()
	
public:	
	APickup2();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CollisionComponent;

	UFUNCTION()
		void OnBeginOverlap(AActor* AsteroidActor, AActor* OtherActor);

	float InitialRotation;
	float Initial_X_Loc;
	float Initial_Y_Loc;
	float RandSize;
	float SelfDestructTimer;

	UPROPERTY(EditAnywhere)
		float Spawn_X_Vel;

	UPROPERTY(EditAnywhere)
		float Spawn_Y_Vel;

	bool bHit;
	bool bStartDestroyTimer;

	void SetHazardVelocity(FVector NewVelocity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
