// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTestActor.generated.h"

UCLASS()
class ATPROJECT_API ABaseTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTestActor();

protected:

	virtual void BeginPlay() override;
	
	// Function that sets up the language specific environment.
	virtual void SetupTestEnvironment();

	// Shuts the language specific environment down.
	virtual void BreakdownTestEnvironment();

	virtual void PerformTest();
};
