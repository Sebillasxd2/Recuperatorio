// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Pickup1.generated.h"

UCLASS()
class STARFIGHTER_API APickup1 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickup1();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PickUp1Mesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CollisionComponent;


	UFUNCTION()
		void OnBeginOverlap(AActor* Pickup1Actor, AActor* OtherActor);

	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved,
			FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
