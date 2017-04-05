// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

//Tick
	// Super
	// AimTowardsCrosshair()

	// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No controlled tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank %s controlled."), *(ControlledTank->GetName()));
	}

	//UE_LOG(LogTemp, Warning, TEXT("player Controller signing in - testing 1 2 3..."));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());


}


