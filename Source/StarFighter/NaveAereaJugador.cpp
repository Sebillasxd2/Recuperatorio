// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAereaJugador.h"
#include "Proyectil.h"
#include "NaveTerrestreEnemiga01.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ANaveAereaJugador::ANaveAereaJugador()
{
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	ShipInventory = CreateDefaultSubobject<UInventoryComponent>("MyInventory");

	// Movement
	MoveSpeed = 1000.0f;

	Energy = 10;

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;

	FireForwardValue = 0.0f;
	FireRightValue = 0.0f;

	//Ship info
	ShipInfo.Add("Health", 0);
	ShipInfo.Add("Armor", 0);
}
void ANaveAereaJugador::BeginPlay()
{
	Super::BeginPlay();

}

void ANaveAereaJugador::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ANaveAereaJugador::Fire);
	PlayerInputComponent->BindAction(TEXT("DropItem"), EInputEvent::IE_Pressed, this, &ANaveAereaJugador::DropItem);

}

void ANaveAereaJugador::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	if (ForwardValue != 0.0f || RightValue != 0.0f) {

		if (ForwardValue != FireForwardValue) {
			FireForwardValue = ForwardValue;
		}

		if (RightValue != FireRightValue) {
			FireRightValue = RightValue;
		}
	}

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}

}
//Funcion que aumenta la armadura o vida de nuestra nave, y si no necesitamos vida o armadura nos aumenta el score
void ANaveAereaJugador::CollectablePickup()
{
	if (Current_Armor <= 100.0f && Current_Health == 100.0f)
	{
		Current_Armor += 10.0f;
		if (Current_Armor > 100.0f) Current_Armor = 100.0f;
	}
	else if (Current_Health <= 100.0f)
	{
		Current_Health += 10.0f;
		if (Current_Health > 100.0f) Current_Health = 100.0f;
	}
	else if (bool ANaveTerrestreEnemiga01::bDead = false) {

		bDead = true;
	}
	else
		PlayerScore += 15.0f;
}
//Funcion que nos ayuda a reducir nuestra vida o armadura al chocar con un asteroide, un enemigo o un projectile

void ANaveAereaJugador::OnBeginOverlap(AActor* PlayerActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Asteroid") || OtherActor->ActorHasTag("EnemyShip"))
	{
		if (Current_Armor > 0.0f)
		{
			Current_Armor -= 10.0f;
			if (Current_Armor < 0.0f) Current_Armor = 0.0f;
		}
		else if (Current_Health > 0.0f)
		{
			Current_Health -= 10.0f;
			if (Current_Health < 0.0f)
			{
				Current_Health = 0.0f;
				bHit = true;
			}
		}
	}
	if (OtherActor->ActorHasTag("EnemyProjectile"))
	{
		if (Current_Armor > 0.0f)
		{
			Current_Armor -= 25.0f;
			if (Current_Armor < 0.0f) Current_Armor = 0.0f;
		}
		else if (Current_Health > 0.0f)
		{
			Current_Health -= 25.0f;
			if (Current_Health < 0.0f)
			{
				Current_Health = 0.0f;
				bHit = true;
			}
		}
	}
}
// Called when the game starts or when spawned
void ANaveAereaJugador::BeginPlay()
{
	Super::BeginPlay();

	bHit = bDeadPlayer = false;
	Max_Health = Current_Health = 100.0f;
	Max_Armor = Current_Armor = 100.0f;
	Current_Location = this->GetActorLocation();
	Current_Rotation = this->GetActorRotation();
	OnActorBeginOverlap.AddDynamic(this, &ANaveAereaJugador::OnBeginOverlap);
}
void ANaveAereaJugador::Fire() {
	bCanFire = true;
	UE_LOG(LogTemp, Warning, TEXT("Se presiono la barra espaciadora"));
	// Create fire direction vector
	
	UE_LOG(LogTemp, Warning, TEXT("FireForwardValue: %f FireRightValue: %f"), FireForwardValue, FireRightValue);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	//const FVector FireDirection = GetActorLocation();
	// Try and fire a shot
	FireShot(FireDirection);
}

void ANaveAereaJugador::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		
		// If we are pressing fire stick in a direction
		//if (FireDirection.SizeSquared() > 0.0f)
		//{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// spawn the projectile
				World->SpawnActor<AProyectil>(SpawnLocation, FireRotation);
			
			}

			

			//bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAereaJugador::ShotTimerExpired, FireRate);

			bCanFire = false;

	}
}

void ANaveAereaJugador::ShotTimerExpired()
{
	bCanFire = true;
}

void ANaveAereaJugador::DropItem()
{
	if (ShipInventory->CurrentInventory.Num() == 0)
	{
		return;
	}
	AInventoryActor* Item = ShipInventory->CurrentInventory.Last();
	ShipInventory->RemoveFromInventory(Item);
	//should probably use scaled bounding box
	FVector ItemOrigin;
	FVector ItemBounds;
	Item->GetActorBounds(false, ItemOrigin, ItemBounds);
	FTransform PutDownLocation = GetTransform() + FTransform(RootComponent->GetForwardVector() * ItemBounds.GetMax());
	Item->PutDown(PutDownLocation);
}

void ANaveAereaJugador::TakeItem(AInventoryActor* InventoryItem)
{
	InventoryItem->PickUp();
	ShipInventory->AddToInventory(InventoryItem);
}

void ANaveAereaJugador::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AInventoryActor* InventoryItem = Cast<AInventoryActor>(Other);
	if (InventoryItem != nullptr)
	{
		TakeItem(InventoryItem);

	}
}

