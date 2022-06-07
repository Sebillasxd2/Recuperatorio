// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InventoryActor.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API AInventoryActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInventoryActor();
	float MoveSpeed;
	bool bHit;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void PickUp();
	virtual void PutDown(FTransform TargetLocation);
	
	UFUNCTION()
		void OnBeginOverLap(AActor* OneActor, AActor* OtherActor);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Datos", meta = (AllowPrivateAccess = "true"))
		FString InventoryActorName;

public:
	FString GetInventoryActorName() const { return InventoryActorName; }
	void SetInventoryActorName(const FString _InventoryActorName) { InventoryActorName = _InventoryActorName; }

};
