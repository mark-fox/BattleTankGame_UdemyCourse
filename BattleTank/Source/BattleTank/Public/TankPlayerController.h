// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "Tank.h"
#include "TankPlayerController.generated.h"

//class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	/*UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;*/
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	// Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world.
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landscape.
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.3333f;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
