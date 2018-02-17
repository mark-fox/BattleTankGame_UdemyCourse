// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;		// why was this missing???
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

//void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
//	if (!BarrelToSet) { return; }
//	Barrel = BarrelToSet;
//}
//
//
//void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
//	if (!TurretToSet) { return; }
//	Turret = TurretToSet;
//}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	//Super::BeginPlay();

	// So that first fire is after initial reload.
	LastFireTime = FPlatformTime::Seconds();
	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringState::Aiming;
	}
	else {
		FiringState = EFiringState::Locked;
	}
}


bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }

	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}


void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)
		) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	/*else {
		
	}*/
}



void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	if (!ensure(Barrel && Turret)) { return; }

	// Work out difference between current barrel rotation and AimDirection.
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}



void UTankAimingComponent::Fire() {

	//bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (FiringState != EFiringState::Reloading) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		// Spawn a projectile at the socket location on the barrel.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}