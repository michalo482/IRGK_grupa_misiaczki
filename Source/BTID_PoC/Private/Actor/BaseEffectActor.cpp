// Copyright Misiaczki IRGK_WSEI


#include "Actor/BaseEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "Components/SphereComponent.h"

ABaseEffectActor::ABaseEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void ABaseEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UBaseAttributeSet* BaseAttributeSet = Cast<UBaseAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UBaseAttributeSet::StaticClass()));
		UBaseAttributeSet* MutableBaseAttributeSet = const_cast<UBaseAttributeSet*>(BaseAttributeSet);
		MutableBaseAttributeSet->SetHealth(BaseAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void ABaseEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ABaseEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ABaseEffectActor::EndOverlap);
}


