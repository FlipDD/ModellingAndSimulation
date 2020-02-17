// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shuttercock.generated.h"

UCLASS()
class MODELLINGSIMULATION_API AShuttercock : public AActor
{
	GENERATED_BODY()
	
	/** Shuttercock mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* Mesh;

public:
	// Sets default values for this actor's properties
	AShuttercock();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Custom var defaults
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Scaling = 26.25;
	// Constants
	float Pi;

	// Parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Gravity = -9.8f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Mass = 0.0052f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float DragCoeff = 0.6f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float AirDensity = 1.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float ShuttleRad = 0.034f;

	// Initial Conditions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InitialValues)
		float InitSpeed = 6.8f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InitialValues)
		float InitHeight = 2.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InitialValues)
		float InitDispY = -2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InitialValues)
		float LaunchAngle = 55;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InitialValues)
		float LaunchAngle2 = 90;

	// Internal variables. These are the "state" variables which are not editable.
	float VelyY;
	float DispY;
	float VelyZ;
	float DispZ;
	float AccelY;
	float AccelZ;
	float Time;
	float Theta;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
