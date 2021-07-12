// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrier.h"

#include "PPlayerCharacter.h"
#include "ProjectIRRUPTIONGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABarrier::ABarrier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ABarrier::OnBeginOverlap);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ABarrier::OnEndOverlap);

	BoxComponent->SetupAttachment(CapsuleComponent);
	SpriteComponent->SetupAttachment(CapsuleComponent);

	SetRootComponent(CapsuleComponent);

	CapsuleComponent->SetGenerateOverlapEvents(false);
}

// Called when the game starts or when spawned
void ABarrier::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(CapsuleOverlapTimerHandle, this, &ABarrier::EnableCapsuleOverlapEvents, 1.0f, false, 0.5f);
}

// Called every frame
void ABarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarrier::EnableCapsuleOverlapEvents()
{
	if(CapsuleOverlapTimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(CapsuleOverlapTimerHandle);

	CapsuleComponent->SetGenerateOverlapEvents(true);

	GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, "Timer");
}


void ABarrier::Interact()
{
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this);

	if(GameModeBase)
	{
		AProjectIRRUPTIONGameModeBase* MyGameMode = Cast<AProjectIRRUPTIONGameModeBase>(GameModeBase);

		if(MyGameMode)
			MyGameMode->SetHintText("");
	}

	Destroy();
}

void ABarrier::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, FString::Printf(TEXT("Barreira Colidiu")));

	if(OtherActor->ActorHasTag("Player"))
	{
		APPlayerCharacter* MyPlayer = Cast<APPlayerCharacter>(OtherActor);

		if(MyPlayer)
			MyPlayer->SetInteractable(this);
		
		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this);

		if(GameModeBase)
		{
			AProjectIRRUPTIONGameModeBase* MyGameMode = Cast<AProjectIRRUPTIONGameModeBase>(GameModeBase);

			if(MyGameMode)
			{
				if(MyGameMode->HasKey)
				{
					MyGameMode->SetHintText(TEXT("Press 'E' to use the KEY."));
				}
				else
				{
					MyGameMode->SetHintText(TEXT("You need the KEY to continue."));
				}
			}
		}
	}
}

void ABarrier::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, FString::Printf(TEXT("Barreira DesColidiu")));

	if(OtherActor->ActorHasTag("Player"))
	{
		APPlayerCharacter* MyPlayer = Cast<APPlayerCharacter>(OtherActor);

		if(MyPlayer)
			MyPlayer->SetInteractable(nullptr);
		
		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this);

		if(GameModeBase)
		{
			AProjectIRRUPTIONGameModeBase* MyGameMode = Cast<AProjectIRRUPTIONGameModeBase>(GameModeBase);

			if(MyGameMode)
			{
				MyGameMode->RemoveWidget();
			}
		}
	}
}
