// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
// Depends on movement component via pathfinding system.


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}



void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (ensure(PlayerTank)) {
		// Move towards the player.
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim towards the player.
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire.
		ControlledTank->Fire();
	}
}




