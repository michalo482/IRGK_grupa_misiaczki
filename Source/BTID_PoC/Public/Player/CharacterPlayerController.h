// Copyright Misiaczki IRGK_WSEI

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;

/**
 * 
 */
UCLASS()
class BTID_POC_API ACharacterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACharacterPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext>  PlayerContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MaveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
};
