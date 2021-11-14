// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetCharacter.generated.h"

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
	
};
