// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AttributeSetCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, float, CurrentHealth, float, BaseHealth, float, Delta);

/**
 * 
 */
UCLASS()
class GASUDEMY_API UAttributeSetCharacter : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAttributeSetCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    FGameplayAttributeData MaxHealth;

	void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
};
