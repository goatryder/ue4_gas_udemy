// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GU_CharacterBase.generated.h"

UCLASS()
class GASUDEMY_API AGU_CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGU_CharacterBase();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(BlueprintReadWrite, Category="Ability", meta = (AllowPrivateAccess = true))
	class UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(BlueprintReadWrite, Category="Ability", meta = (AllowPrivateAccess = true))
	class UAttributeSetCharacter* AttributeSetCharacter;

	// grant ability to character class on begin play 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<class UGameplayAbility>> StartupAbilities;
	
public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComp; }

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void AquireAbility(TSubclassOf<class UGameplayAbility> AbilityToAquire);

	UFUNCTION()
	void OnHealthChanged(float CurrentHealth, float BaseHealth, float Delta);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnHealthChanged(float CurrentHealth, float BaseHealth, float Delta);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Died();

};
