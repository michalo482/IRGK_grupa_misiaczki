// Copyright Misiaczki IRGK_WSEI

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEffectActor.generated.h"

class USphereComponent;

UCLASS()
class BTID_POC_API ABaseEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseEffectActor();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

};
