// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ApocalypseRide.generated.h"

UENUM(BlueprintType)
enum class StateEnum : uint8
{
	STATE_RISING	UMETA(DisplayName = "STATE_RISING"),
	STATE_FALLING	UMETA(DisplayName = "STATE_FALLING"),
	STATE_PAUSEATTOP	UMETA(DisplayName = "STATE_PAUSEATTOP"),
	STATE_BRAKING	UMETA(DisplayName = "STATE_BRAKING"),
	STATE_STOPPED	UMETA(DisplayName = "STATE_STOPPED")
};

UCLASS()
class MODELLINGSIMULATION_API AApocalypseRide : public AActor
{
	GENERATED_BODY()
	
	/** Capsule collider */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UCapsuleComponent* CapsuleCollider;

	/** Tower mesh */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* TowerMesh;

	/** Tower top mesh */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* TowerTopMesh;

	/** Car mesh */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* CarMesh;

	///** Destroyed car mesh */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UDestructibleComponent* DestroyedCarMesh;

public:
	// Sets default values for this actor's properties
	AApocalypseRide();

	// Custom var defaults
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Scaling = 26.25;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		int itn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		FVector OldLoc;

	// Parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Gravity = -9.8f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Mass = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float BrakingForce = 39.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float ReleaseHeight = 108;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float BrakingHeight = 27;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float PauseTime = 2;

	// Initial Conditions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InitialValues)
		float VelyLift;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InitialValues)
		StateEnum CarState;

	// Internal variables. These are the "state" variables which are not editable.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
		float VelyZ = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
		float MaxAcc = 39.2f;

	float DispZ;
	float AccelZ;
	float Time;
	bool bFractured;

	float SaveTime = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
