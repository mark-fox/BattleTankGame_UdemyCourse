// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "TankAimingComponent.h"
#include "Tank.generated.h"

// Forward Declarations:
//class UTankBarrel;
//class UTankAimingComponent;
//class UTankMovementComponent;
//class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Called by the engine when actor damage is dealt.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor* DamageCauser) override;

	// Returns current health as a percentage of starting health.
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;
};
