// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeBounds.h"
#include "Components/ShapeComponent.h"

void ALifeBounds::BeginPlay()
{
	Super::BeginPlay();
	if (GetCollisionComponent() != NULL)
	{
		GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &ALifeBounds::OnEndOverlap); //for gameplay interactions
	}
}

void ALifeBounds::OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsValidLowLevel()) OtherActor->Destroy();
}
