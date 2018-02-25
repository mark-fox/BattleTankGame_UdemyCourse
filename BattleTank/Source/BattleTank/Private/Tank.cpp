// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
//#include "TankAimingComponent.h"
//#include "TankMovementComponent.h"
//#include "Engine/World.h"
//#include "TankBarrel.h"
//#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}



// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

//// Called every frame
//void ATank::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor* DamageCauser) {
	// Convert float to int to avoid comparing float to 0.
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	return DamageToApply;
}