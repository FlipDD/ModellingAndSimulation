// Fill out your copyright notice in the Description page of Project Settings.

#include "ApocalypseRide.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DestructibleComponent.h"


// Macros
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)
// Sets default values
AApocalypseRide::AApocalypseRide()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Main collider
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollider");
	CapsuleCollider->SetupAttachment(GetRootComponent());
	CapsuleCollider->SetCapsuleHalfHeight(2000);
	CapsuleCollider->SetCapsuleRadius(115);

	// Create and attach the meshes
	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>("TowerMesh");
	TowerMesh->SetupAttachment(CapsuleCollider);
	TowerMesh->SetRelativeScale3D(FVector(2, 2, 20));

	TowerTopMesh = CreateDefaultSubobject<UStaticMeshComponent>("TowerTopMesh");
	TowerTopMesh->SetupAttachment(CapsuleCollider);
	TowerTopMesh->SetRelativeLocation(FVector(0, 0, 2560));
	TowerTopMesh->SetRelativeScale3D(FVector(3, 3, 2));

	CarMesh = CreateDefaultSubobject<UStaticMeshComponent>("CarMesh");
	CarMesh->SetupAttachment(CapsuleCollider);
	CarMesh->SetRelativeLocation(FVector(155, 0, 0));
	CarMesh->SetRelativeScale3D(FVector(2));

	DestroyedCarMesh = CreateDefaultSubobject<UDestructibleComponent>("DestroyedCarMesh");
	DestroyedCarMesh->SetupAttachment(CarMesh);
	DestroyedCarMesh->SetRelativeScale3D(FVector(2));
	DestroyedCarMesh->SetVisibility(false);
	DestroyedCarMesh->SetSimulatePhysics(false);
}

// Called when the game starts or when spawned
void AApocalypseRide::BeginPlay()
{
	Super::BeginPlay();

	// Start with tick off and only turn on when the player activates it.
	SetActorTickEnabled(false);

	OldLoc = CarMesh->GetComponentLocation();

	// Set initial conditions
	Time = 0;
	DispZ = 0;
	VelyZ = VelyLift;
	CarState = StateEnum::STATE_RISING;

	// Initialize Variables - Do we need these?
	//ReleaseHeight = 54.0f;
	//Scaling = 52.5f;
	//AccelZ = 0;

}

// Called every frame
void AApocalypseRide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Any variable here is local to this function. You cannot access it outside
	// this function, e.g., you cannot sent it to the HUD.
	/* Uncomment the following lines
	*/

	float ForceZ;
	// if we are not at the top then we must get there ---------------------------
	if (CarState == StateEnum::STATE_RISING) {

		VelyZ = VelyLift;
		ForceZ = 0;
		UE_LOG(LogTemp, Warning, TEXT("Dispz: %f, releaseheight: %f"), DispZ, ReleaseHeight);
		if (DispZ >= ReleaseHeight) {  // have reached the top
			CarState = StateEnum::STATE_PAUSEATTOP;
			SaveTime = Time;
		}
	}

	// we will delay at the top --------------------------------------------------
	if (CarState == StateEnum::STATE_PAUSEATTOP) {

		ForceZ = 0;
		VelyZ = 0;
		if (Time > (SaveTime + PauseTime))    // wait until pause is finished
			CarState = StateEnum::STATE_FALLING;
	}

	// we are falling ------------------------------------------------------------
	if (CarState == StateEnum::STATE_FALLING) {

		ForceZ = Mass * Gravity;

		if (DispZ <= BrakingHeight)
			CarState = StateEnum::STATE_BRAKING;
	}

	// we are braking ----------------------------------------------------------
	if (CarState == StateEnum::STATE_BRAKING) {

		ForceZ = Mass * Gravity + BrakingForce;

		if (VelyZ >= 0)
			CarState = StateEnum::STATE_STOPPED;
	}

	// we have stopped ---------------------------------------------------------
	if (CarState == StateEnum::STATE_STOPPED)
		SetActorTickEnabled(false);

	// Now let's compute the DYNAMICS based on the forces set up in each State

	AccelZ = ForceZ / Mass;
	VelyZ += AccelZ * DeltaTime;
	DispZ += VelyZ * DeltaTime;

	Time += DeltaTime;

	// End of your code above here -------------------------------------------------

	// VISUALISATION
	// Here you will write code to convert the state variable into a position, size
	// color or something else which can be seen.

	FVector NewVec;

	NewVec = OldLoc;
	NewVec.Z = NewVec.Z + (DispZ * Scaling);
	CarMesh->SetWorldLocation(NewVec);

	UE_LOG(LogTemp, Warning, TEXT("AccelZ: %f"), AccelZ);
	if (AccelZ > MaxAcc) {
		CarMesh->SetVisibility(false);
		DestroyedCarMesh->SetVisibility(true);
		DestroyedCarMesh->SetSimulatePhysics(true);
		DestroyedCarMesh->ApplyRadiusDamage(50000, CarMesh->GetComponentLocation(), 5000, 5000, true);
		//NewObject<UDestructibleMesh>(this, DestroyedCarMeshToSpawn);
		//DestroyedCarMesh->SetSimulatePhysics(true);
		SetActorTickEnabled(false);
		PrimaryActorTick.bCanEverTick = false;
	}
}

