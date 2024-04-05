// Copyright Misiaczki IRGK_WSEI


#include "Player/CharacterPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Interaction/EnemyInterface.h"

ACharacterPlayerController::ACharacterPlayerController()
{
	bReplicates = true;
	bIgnoreRotationDuringJump = false;
}

void ACharacterPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void ACharacterPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	* Kilka scenariuszy:
	* a) LastActor = null i ThisActor = null
	*	- nic nie robi
	* b) LastActor = null ale ThisActor = valid
	*	- Highlight ThisActor
	* c) LastActor = valis ale ThisActor = null
	*	- UnHighlight
	* d) LastActor != ThisActor ale oba s� valid
	*	- UnHighlight LastActor, Highlight ThisActor
	* 
	*/
	
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
		}
	}

}

void ACharacterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(PlayerContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

}

void ACharacterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	
	EnhancedInputComponent->BindAction(MaveAction, ETriggerEvent::Triggered, this, &ACharacterPlayerController::Move);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacterPlayerController::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacterPlayerController::StopJump);
}

void ACharacterPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>()) 
	{
		
			ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
			ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
		
	}
}

void ACharacterPlayerController::Jump()
{
	
	if (APawn* ControlledPawn = GetPawn())
	{
		Cast<ACharacter>(ControlledPawn)->Jump();
		bIgnoreRotationDuringJump = true;
	}
}

void ACharacterPlayerController::StopJump()
{
	if (APawn* ControlledPawn = GetPawn())
	{
		Cast<ACharacter>(ControlledPawn)->StopJumping();
		bIgnoreRotationDuringJump = false;
	}
}





