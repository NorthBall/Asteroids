// Fill out your copyright notice in the Description page of Project Settings.

#include "UFOHard.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "PlayerPawn.h"
#include "MyAsteroid.h"
#include "Navigation/PathFollowingComponent.h"


// Sets default values
AUFOHard::AUFOHard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->AttachToComponent(RootComponent,FAttachmentTransformRules(EAttachmentRule::KeepRelative,false));
	Shield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	Shield->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	for (int32 i = 0; i < 6; i++)
	{
		BeamEmitters.Add(CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Emitter"), i)));
		BeamEmitters[i]->SetRelativeLocation(FRotator(0, i * 60, 0).RotateVector(FVector(0, 120, 35)));
		BeamEmitters[i]->ActivateSystem();
		BeamEmitters[i]->SetEmitterEnable(TEXT("Main"), false);
		BeamEmitters[i]->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

// Called when the game starts or when spawned
void AUFOHard::BeginPlay()
{
	Super::BeginPlay();
	PowerOff(NULL);
	//Shield->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody,ECollisionResponse::ECR_Overlap);
	Shield->OnComponentBeginOverlap.AddDynamic(this, &AUFOHard::OnBeginOverlap);
	Shield->OnComponentEndOverlap.AddDynamic(this, &AUFOHard::OnEndOverlap);
	
	/*TrueController = Cast<AAIController>(GetController());
	if (TrueController != NULL) TrueController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AUFOHard::OnEndMove);*/
}

void AUFOHard::ChaseEnemy(APlayerPawn * Victim)
{
	Enemy = Victim;
	if (Enemy != NULL)
	{
		TrueController = Cast<AAIController>(GetController());
		SpareMoveTo(Enemy);
		//if ( TrueController!= NULL) TrueController->MoveToActor(Enemy,0.01f,false,true,true,0,true);
	}
}

void AUFOHard::PowerOff(AActor* IgnoredActor)
{
	TSet<AActor*> OverlappedActors;
	GetOverlappingActors(OverlappedActors, AMyAsteroid::StaticClass());
	if (IgnoredActor!=NULL) OverlappedActors.Remove(IgnoredActor);
	if (OverlappedActors.Num() == 0)
	{
		SetCanBeDamaged (true);
		ShieldOn = false;
		Shield->SetVisibility(false);
		for (UParticleSystemComponent* Emit : BeamEmitters)
		{
			Emit->SetEmitterEnable(TEXT("Main"), false);
		}
	}
}

void AUFOHard::PowerOn()
{
	SetCanBeDamaged (false);
	ShieldOn = true;
	Shield->SetVisibility(true);
	for (UParticleSystemComponent* Emit : BeamEmitters)
	{
		Emit->SetEmitterEnable(TEXT("Main"), true);
	}
}

float AUFOHard::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (Enemy!=NULL) Enemy->Score++;
	Destroy();
	return Damage;
}

void AUFOHard::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(!ShieldOn)	if (Cast<AMyAsteroid>(OtherActor))
	{
		PowerOn();
	}
	else
	{
		if (Cast<APlayerPawn>(OtherActor))
		{
			OtherActor->TakeDamage(1, FDamageEvent(), GetInstigatorController(), this);
		}
	}
}

void AUFOHard::OnEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AMyAsteroid>(OtherActor) != NULL && ShieldOn)
	{
		PowerOff(Cast<AMyAsteroid>(OtherActor));
	}
}

void AUFOHard::OnEndMove(FAIRequestID RequestID,const FPathFollowingResult& Result)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f Distance"), LevelUpdateTime);
}


