// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveTerrestreEnemiga01.h"
#include "NaveAerea.h"
#include "InventoryComponent.h"
#include "NaveAereaJugador.generated.h"

UCLASS()
class STARFIGHTER_API ANaveAereaJugador : public ANaveAerea :
{
	GENERATED_BODY()
	
	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	//Cola<class AProyectil*> ColaProyectiles;

public:
	ANaveAereaJugador();
	
	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;

	void Fire();
	
	/* Fire a shot in the specified direction */
	void FireShot(FVector FireDirection);

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	//Variables que nos permitiran manejar la vida maxima de nuestra nave, la vida actual, la maxima armadura y la armadura actual

	UPROPERTY(BlueprintReadOnly)
		float Max_Health;
	UPROPERTY(BlueprintReadOnly)
		float Current_Health;
	UPROPERTY(BlueprintReadOnly)
		float Max_Armor;
	UPROPERTY(BlueprintReadOnly)
		float Current_Armor;

	//Funcion que nos permitira aumentar la vida y armadura de nuestra nave cuando recojamos un objeto

	void CollectablePickup();


	bool bIsFiring;
	bool bHit;
	bool bDeadPlayer;

	//Variable que nos permite controlar el score

	UPROPERTY(BlueprintReadOnly)
		float PlayerScore;
	FVector Current_Location;
	FVector New_Location;
	FRotator Current_Rotation;

	UFUNCTION()
		void OnBeginOverlap(AActor* PlayerActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProyectil> WeaponProyectil_BP;


	//Inventario
	UPROPERTY()
		UInventoryComponent* ShipInventory;

	UPROPERTY()
		TMap<FString, int32> ShipInfo;


	UFUNCTION()
		void TakeItem(AInventoryActor* InventoryItem);

	UFUNCTION()
		void DropItem();

	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;


	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	float FireForwardValue;
	float FireRightValue;

};
