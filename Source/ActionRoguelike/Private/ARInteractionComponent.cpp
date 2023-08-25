// Fill out your copyright notice in the Description page of Project Settings.


#include "ARInteractionComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ARGameplayInterface.h"

// Sets default values for this component's properties
UARInteractionComponent::UARInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	InteractDistance = 1000.0f;
}


// Called when the game starts
void UARInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UARInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UARInteractionComponent::PrimaryInteract()
{
	FHitResult HitResult;

	auto Owner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector Start = EyeLocation;
	FVector End = EyeLocation + EyeRotation.Vector() * InteractDistance;
	
	float Radius = 32.0f;
	
	//FCollisionObjectQueryParams ObjectQueryParams;
	//ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	//
	//auto bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ObjectQueryParams);

	// Ĭ�� ObjectTypeQuery1 ���� WorldStatic
	// Ĭ�� ObjectTypeQuery2 ���� WorldDynamic
	// Ĭ�� ObjectTypeQuery3 ���� Pawn
	// Ĭ�� ObjectTypeQuery4 ���� PhysicasBody
	// Ĭ�� ObjectTypeQuery5 ���� Vehicle
	// Ĭ�� ObjectTypeQuery6 ���� Destructible
	// ������ ProjectSettings->Engine->Collision->Object Channels ����Զ���
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery2);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);

	TArray<FHitResult> HitResults;

	//auto bHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, ObjectTypes, false,
	//												 ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);

	auto HitActor = HitResult.GetActor();

	auto bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, Radius, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitResults, true);

	for (const auto& Hit : HitResults)
	{
		HitActor = Hit.GetActor();

		if (HitActor)
		{
			if (HitActor->Implements<UARGameplayInterface>())
			{
				auto Pawn = Cast<APawn>(Owner);

				IARGameplayInterface::Execute_Interact(HitActor, Pawn);

				break;
			}
		}

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, FColor::Green, false, 3.0f);
	}
}

