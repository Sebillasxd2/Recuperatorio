// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup1.h"
#include "NaveAereaJugador.h"

// Sets default values
APickup1::APickup1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PickUp1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUp1Mesh"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	PickUp1Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}


// Called when the game starts or when spawned
void APickup1::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APickup1::OnBeginOverlap);
	
}

// Called every frame
void APickup1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = this->GetActorLocation();
	NewLocation.X -= DeltaTime * 50.0f;
	NewLocation.Z = 0;
	this->SetActorLocation(NewLocation);
}

void APickup1::OnBeginOverlap(AActor* Pickup1Actor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Jugador") )
	{
		ANaveAereaJugador* PlayerActor = Cast<ANaveAereaJugador>(OtherActor);
		PlayerActor->CollectablePickup();
		this->Destroy();
		if (OtherActor->ActorHasTag("Bounds"))
			this->Destroy();
	}
}

