// Fill out your copyright notice in the Description page of Project Settings.


#include "Shuttercock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AShuttercock::AShuttercock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the capsule collider
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetCapsuleSize(18.5f, 13);
	Capsule->SetupAttachment(GetRootComponent());

	// Create and attach the mesh for the shuttlecock
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Capsule);

	// Assign the value of PI
	Pi = UKismetMathLibrary::GetPI();
}

// Called when the game starts or when spawned
void AShuttercock::BeginPlay()
{
	Super::BeginPlay();

	// Start with tick off and only turn on when the player activates it.
	SetActorTickEnabled(false);

	// Initialization
	LaunchAngle2 = 90 - LaunchAngle;

	VelyY = InitSpeed * (sin(LaunchAngle2 * Pi / 180));
	VelyZ = InitSpeed * (cos(LaunchAngle2 * Pi / 180));
	//VelyY = InitSpeed * (sin(LaunchAngle));
	//VelyZ = InitSpeed * (cos(LaunchAngle));

	Theta = LaunchAngle2 * Pi / 180;
	SetActorRotation(FRotator(0, 0, LaunchAngle));

	GroundHeight = GetActorLocation().Z;

	DispY = InitDispY;
	DispZ = InitHeight;
	AddActorWorldOffset(FVector(0, -InitDispY * 100, InitHeight * 100));
}

// Called every frame
void AShuttercock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// COMPUTATION
	// Here you will write your code based on your mathematical model --------------

	float ForceY;
	float ForceZ;
	float Speed;
	float SpeedSquared;
	float DragZ;
	float DragY;
	float TotalDrag;

	// Write your code under here --------------------------------------------------

	// Calculate the Speed Squared
	SpeedSquared = VelyY * VelyY + VelyZ * VelyZ;
	Speed = sqrt(SpeedSquared);
	
	// Calculate Total Drag
	TotalDrag = (0.5f * Pi * (ShuttleRad * ShuttleRad)) * AirDensity * DragCoeff * (Speed * Speed);
	
	// Calculate the Drag for both Y and Z axis
	DragY = TotalDrag * (VelyY / Speed);
	DragZ = TotalDrag * (VelyZ / Speed);

	// Calculate the forces moving the shuttlecock - Don't forget gravity in Z
	ForceY = -DragY;
	ForceZ = -DragZ + (Gravity * Mass);

	// Calculate acceleration, velocity and position for both the Y and Z axis
	AccelZ = ForceZ / Mass;
	VelyZ += AccelZ * DeltaTime;
	DispZ += VelyZ * DeltaTime;

	AccelY = ForceY / Mass;
	VelyY += AccelY * DeltaTime;
	DispY += VelyY * DeltaTime;

	// End of your code above here -------------------------------------------------

	// VISUALISATION
	// Here you will write code to convert the state variable into a position, size
	// color or something else which can be seen.

	// Set the new location
	FVector NewPos = GetActorLocation();
	NewPos.Y += DispY * Scaling;
	NewPos.Z += DispZ * Scaling;
	SetActorLocation(NewPos);

	// Get the angle from the velocity and set new rotation
	Theta = UKismetMathLibrary::Atan2(VelyZ, VelyY);
	SetActorRotation(FRotator(0, 0, Theta));

	if (GetActorLocation().Z < GroundHeight)
		SetActorTickEnabled(false);
}

