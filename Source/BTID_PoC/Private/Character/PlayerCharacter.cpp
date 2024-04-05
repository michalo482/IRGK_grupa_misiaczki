// Copyright Misiaczki IRGK_WSEI


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/BasePlayerState.h"

APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// server
	InitAbilityActorInfo();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//client
	InitAbilityActorInfo();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	ABasePlayerState* BasePlayerState = GetPlayerState<ABasePlayerState>();
	check(BasePlayerState);
	BasePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(BasePlayerState, this);
	AbilitySystemComponent = BasePlayerState->GetAbilitySystemComponent();
	AttributeSet = BasePlayerState->GetAttributeSet();
}
