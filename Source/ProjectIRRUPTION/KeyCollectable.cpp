// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyCollectable.h"

#include "PPlayerCharacter.h"
#include "ProjectIRRUPTIONGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKeyCollectable::AKeyCollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AKeyCollectable::OnBeginOverlap);

	StaticMeshComponent->SetupAttachment(CapsuleComponent);

	SetRootComponent(CapsuleComponent);
}

// Called when the game starts or when spawned
void AKeyCollectable::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Blue, FString::Printf(TEXT("Começou")));
}

// Called every frame
void AKeyCollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyCollectable::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);

		if(GameMode)
		{
			AProjectIRRUPTIONGameModeBase* MyGameMode = Cast<AProjectIRRUPTIONGameModeBase>(GameMode);

			if(MyGameMode)
			{
				MyGameMode->CollectKey();

				this->Destroy();
			}
		}
	}
}
