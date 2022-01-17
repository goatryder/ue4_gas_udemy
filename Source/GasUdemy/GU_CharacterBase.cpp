// Fill out your copyright notice in the Description page of Project Settings.


#include "GU_CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetCharacter.h"
#include "GU_TeamComponent.h"

// Sets default values
AGU_CharacterBase::AGU_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	AttributeSetCharacter = CreateDefaultSubobject<UAttributeSetCharacter>("AttributeSetCharacter");
	TeamComponent = CreateDefaultSubobject<UGU_TeamComponent>("TeamComp");
}

// Called when the game starts or when spawned
void AGU_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	AttributeSetCharacter->OnHealthChanged.AddDynamic(this, &AGU_CharacterBase::OnHealthChanged);
	AttributeSetCharacter->OnManaChanged.AddDynamic(this, &AGU_CharacterBase::OnManaChanged);
	AttributeSetCharacter->OnStaminaChanged.AddDynamic(this, &AGU_CharacterBase::OnStaminaChanged);

	// grant abilities
	for (const auto& StartupAbility : StartupAbilities)
	{
		AquireAbility(StartupAbility.AbilityClass);

		if (StartupAbility.bActivateOnStart)
		{
			AbilitySystemComp->TryActivateAbilityByClass(StartupAbility.AbilityClass, false);			
		}
	}

	// health full -> add tag full health
	if (FullHealthTag.IsValid() && AttributeSetCharacter->Health.GetCurrentValue() == AttributeSetCharacter->MaxHealth.GetCurrentValue())
	{
		AddGameplayTagUnique(FullHealthTag);
	}
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
	if (AbilityToAquire && AbilitySystemComp)
	{
		if (HasAuthority() && AbilitySystemComp)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAquire, 1, INDEX_NONE, this));
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

void AGU_CharacterBase::OnHealthChanged(float CurrentHealth, float BaseHealth, float Delta)
{
	BP_OnHealthChanged(CurrentHealth, BaseHealth, Delta);

	// health full -> add tag full health
	if (FullHealthTag.IsValid() && CurrentHealth == BaseHealth)
	{
		AddGameplayTagUnique(FullHealthTag);
	}
	else
	{
		RemoveGameplayTagUnique(FullHealthTag);
	}
	
	if (CurrentHealth <= 0.f)
	{
		BP_Died();		
	}
}

void AGU_CharacterBase::OnManaChanged(float CurrentMana, float BaseMana, float Delta)
{
	BP_OnManaChanged(CurrentMana, BaseMana, Delta);
}

void AGU_CharacterBase::OnStaminaChanged(float CurrentStamina, float BaseStamina, float Delta)
{
	BP_OnStaminaChanged(CurrentStamina, BaseStamina, Delta);
}

void AGU_CharacterBase::AddGameplayTagUnique(const FGameplayTag& Tag)
{
	GetAbilitySystemComponent()->AddLooseGameplayTag(Tag, 1);
	GetAbilitySystemComponent()->SetLooseGameplayTagCount(Tag,1);
}

void AGU_CharacterBase::RemoveGameplayTagUnique(const FGameplayTag& Tag)
{
	if (GetAbilitySystemComponent()->HasMatchingGameplayTag(Tag))
	{
		GetAbilitySystemComponent()->SetLooseGameplayTagCount(Tag,1);
		GetAbilitySystemComponent()->RemoveLooseGameplayTag(Tag, 1);
	}
}

