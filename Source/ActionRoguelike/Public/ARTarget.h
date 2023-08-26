// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARTarget.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AARTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UARAttributesComponent> AttributesComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<class UStaticMeshComponent> Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, UARAttributesComponent* OwningComponent, float NowHealth, float MaxHealth, float Delta);
};
