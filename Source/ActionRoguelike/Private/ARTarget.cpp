// Fill out your copyright notice in the Description page of Project Settings.


#include "ARTarget.h"
#include "ARAttributesComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AARTarget::AARTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	RootComponent = Mesh;

	AttributesComponent = CreateDefaultSubobject<UARAttributesComponent>("AttributesComponent");
}

// Called when the game starts or when spawned
void AARTarget::BeginPlay()
{
	Super::BeginPlay();
	
	AttributesComponent->OnHealthChange.AddDynamic(this, &AARTarget::OnHealthChange);
}

// Called every frame
void AARTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AARTarget::OnHealthChange(AActor* InstigatorActor, UARAttributesComponent* OwningComponent, float NowHealth, float MaxHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		Mesh->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}
