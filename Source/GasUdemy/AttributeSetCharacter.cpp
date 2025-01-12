// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetCharacter.h"

#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"

UAttributeSetCharacter::UAttributeSetCharacter()
	: Health(200), MaxHealth(200),
      Mana(100), MaxMana(150),
      Stamina(200), MaxStamina(200)
{
}

void UAttributeSetCharacter::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	// Health Attribute  
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetCharacter::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetCharacter, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetCurrentValue()));
		float Delta = Data.EffectSpec.GetModifierMagnitude(0, false);
		OnHealthChanged.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue(), Delta);
	}

	// Mana Attribute  
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetCharacter::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetCharacter, Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.f, MaxMana.GetCurrentValue()));
		float Delta = Data.EffectSpec.GetModifierMagnitude(0, false);
		OnManaChanged.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue(), Delta);
	}

	// Stamina Attribute  
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetCharacter::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetCharacter, Stamina)))
	{
		Stamina.SetCurrentValue(FMath::Clamp(Stamina.GetCurrentValue(), 0.f, MaxStamina.GetCurrentValue()));
		Stamina.SetBaseValue(FMath::Clamp(Stamina.GetBaseValue(), 0.f, MaxStamina.GetCurrentValue()));
		float Delta = Data.EffectSpec.GetModifierMagnitude(0, false);
		OnStaminaChanged.Broadcast(Stamina.GetCurrentValue(), MaxStamina.GetCurrentValue(), Delta);
	}
}
