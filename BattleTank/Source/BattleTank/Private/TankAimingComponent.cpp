// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;		// why was this missing???
	PrimaryComponentTick.bCanEverTick = false;

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


//// Called when the game starts
//void UTankAimingComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//	
//}
//
//
//// Called every frame
//void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
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
