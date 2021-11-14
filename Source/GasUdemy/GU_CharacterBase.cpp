// Fill out your copyright notice in the Description page of Project Settings.


#include "GU_CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetCharacter.h"

// Sets default values
AGU_CharacterBase::AGU_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	AttributeSetCharacter = CreateDefaultSubobject<UAttributeSetCharacter>("AttributeSetCharacter");
}

// Called when the game starts or when spawned
void AGU_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGU_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGU_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGU_CharacterBase::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire)
{
	if (AbilitySystemComp)
	{
		if (HasAuthority() && AbilitySystemComp)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAquire, 1, INDEX_NONE, this));
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

