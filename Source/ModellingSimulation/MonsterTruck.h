#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterTruck.generated.h"

UENUM(BlueprintType)
enum class SolverEnum : uint8
{
	EULER	UMETA(DisplayName = "Euler"),
	EULER_CROMER	UMETA(DisplayName = "Euler_Cromer"),
	RKF	UMETA(DisplayName = "Rfk")
};

UCLASS()
class MODELLINGSIMULATION_API AMonsterTruck : public AActor
{
	GENERATED_BODY()

	/** Axles mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* Axles;

	/** SpringFL mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* SpringFL;

	/** SpringFR mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* SpringFR;

	/** SpringRL mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* SpringRL;

	/** SpringRR mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* SpringRR;

	/** Body mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* Body;

	/** FloorPlate mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* FloorPlate;

	/** WheelA mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* WheelA;

	/** WheelB mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* WheelB;

	/** WheelC mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* WheelC;

	/** WheelD mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* WheelD;

public:	
	// Sets default values for this actor's properties
	AMonsterTruck();

	// Parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Stiffness = 9.869600f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Mass = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Damping = 0;

	// Initial Conditions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float InitVelyZ = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float InitDispZ = 0.5;

	// Internal variables. These are the "state" variables which are not editable.
	float VelyZ;
	float AccelZ;
	float DispZ = 0;
	float FloorPlateDispZ = 0;

	// Internal Constants. These may be used for conversions between units.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Scaling = 26.25;
	
	float SpringLength = 71;

	// variables for the analytic solution.
	float SolnZ;

	// additional displacement variables used in floor-plate excitation
	float DispZ2 = 0;
	float DispZ3 = 0;

	// Solver Choice
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InitialValues)
		SolverEnum Solver = SolverEnum::EULER_CROMER;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
