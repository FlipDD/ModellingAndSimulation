#include "MonsterTruck.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMonsterTruck::AMonsterTruck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the mesh for the shuttercocK MonsterTruck
	FloorPlate = CreateDefaultSubobject<UStaticMeshComponent>("FloorPlate");
	FloorPlate->SetupAttachment(GetRootComponent());
	Axles = CreateDefaultSubobject<UStaticMeshComponent>("Axles");
	Axles->SetupAttachment(FloorPlate);
	WheelA = CreateDefaultSubobject<UStaticMeshComponent>("WheelA");
	WheelA->SetupAttachment(Axles);
	WheelB = CreateDefaultSubobject<UStaticMeshComponent>("WheelB");
	WheelB->SetupAttachment(Axles);
	WheelC = CreateDefaultSubobject<UStaticMeshComponent>("WheelC");
	WheelC->SetupAttachment(Axles);
	WheelD = CreateDefaultSubobject<UStaticMeshComponent>("WheelD");
	WheelD->SetupAttachment(Axles);
	SpringFL = CreateDefaultSubobject<UStaticMeshComponent>("SpringFL");
	SpringFL->SetupAttachment(Axles);
	SpringFR = CreateDefaultSubobject<UStaticMeshComponent>("SpringFR");
	SpringFR->SetupAttachment(Axles);
	SpringRL = CreateDefaultSubobject<UStaticMeshComponent>("SpringRL");
	SpringRL->SetupAttachment(Axles);
	SpringRR = CreateDefaultSubobject<UStaticMeshComponent>("SpringRR");
	SpringRR->SetupAttachment(Axles);
	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Body->SetupAttachment(SpringRR);
}

// Called when the game starts or when spawned
void AMonsterTruck::BeginPlay()
{
	Super::BeginPlay();

	VelyZ = InitVelyZ;
}

// Called every frame
void AMonsterTruck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

