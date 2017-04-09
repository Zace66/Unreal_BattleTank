// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"


	// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;	// OUT parameter

	if (GetSightRayHitLocation(HitLocation))
	{

		// TODO Tell the controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}


}

// Get the world location of linetrace through the crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Get the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString());

	// deproject the screen position of the crosshair to a world location
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// line trace along that look direction and see what we hit  (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction : %s"), *LookDirection.ToString());
	}


	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	int32 LineTraceRange = 10000;
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0);
		return false;
	}

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;	// to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
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