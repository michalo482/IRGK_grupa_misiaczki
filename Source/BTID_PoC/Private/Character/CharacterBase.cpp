// Copyright Misiaczki IRGK_WSEI


#include "Character/CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


