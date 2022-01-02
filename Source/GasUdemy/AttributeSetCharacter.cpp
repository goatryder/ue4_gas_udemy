// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetCharacter.h"

#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"

UAttributeSetCharacter::UAttributeSetCharacter()
	: Health(200), MaxHealth(200)
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
}
