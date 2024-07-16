// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathZone.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"

ADeathZone::ADeathZone()
{
	PrimaryActorTick.bCanEverTick = false;

	ZoneBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ZoneBox"));
	SetRootComponent(ZoneBox);
}

void ADeathZone::BeginPlay()
{
	Super::BeginPlay();
	
	ZoneBox->OnComponentBeginOverlap.AddDynamic(this, &ADeathZone::OnBoxOverlap);
}

void ADeathZone::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABlasterCharacter* OverlappingCharacter = Cast<ABlasterCharacter>(OtherActor);
	ABlasterPlayerController* OwnerController = Cast<ABlasterPlayerController>(OverlappingCharacter->Controller);
	if (OverlappingCharacter && OwnerController)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 400.f, OwnerController, this, UDamageType::StaticClass());
	}
}
