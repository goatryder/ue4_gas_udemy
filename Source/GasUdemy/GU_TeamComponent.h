// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GU_TeamComponent.generated.h"


UENUM(BlueprintType)
enum class ETeamRelationType : uint8
{
	Undefined = 255,
	Neutral = 0,
	Friendly = 1,
	Hostile = 2
};

UCLASS()
class GASUDEMY_API UTeamConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TeamIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TeamName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor TeamColor;
};

USTRUCT(BlueprintType)
struct FTeamRelationEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTeamConfig* FirstTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTeamConfig* SecondTeam;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETeamRelationType Relation;
};

UCLASS()
class GASUDEMY_API UTeamSettingsDatabase : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETeamRelationType DefaultRelation = ETeamRelationType::Neutral;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTeamConfig*> TeamConfigArr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTeamRelationEntry> TeamRelations;

	UFUNCTION(BlueprintPure)
	ETeamRelationType GetTeamsRelationById(int32 TeamIdLeft, int32 TeamIdRight, bool bReturnDefaultRelOnFail = true) const
	{
		for (const auto& TeamRelation : TeamRelations)
		{
			if (TeamRelation.FirstTeam->TeamIndex == TeamIdLeft && TeamRelation.SecondTeam->TeamIndex == TeamIdRight ||
				TeamRelation.FirstTeam->TeamIndex == TeamIdRight && TeamRelation.SecondTeam->TeamIndex == TeamIdLeft)
			{
				return TeamRelation.Relation;
			}
		}

		if (bReturnDefaultRelOnFail)
		{
			return DefaultRelation;
		}
		
		return ETeamRelationType::Undefined;
	}

	UFUNCTION(BlueprintPure)
	ETeamRelationType GetTeamsRelationByComp(const class UGU_TeamComponent* TeamCompLeft, const class UGU_TeamComponent* TeamCompRight, bool bReturnDefaultRelOnFail = true) const;

	UFUNCTION(BlueprintPure)
	ETeamRelationType GetTeamsRelationByActor(const AActor* FirstActor, const AActor* SecondActor, bool bTraverseOwners = true, bool bReturnDefaultRelOnFail = true) const;

	UFUNCTION(BlueprintPure)
	bool bIsTeamsHostile(int32 TeamIdLeft, int32 TeamIdRight) const
	{
		return GetTeamsRelationById(TeamIdLeft, TeamIdRight) == ETeamRelationType::Hostile;
	}

	UFUNCTION(BlueprintPure)
	UTeamConfig* GetTeamConfig(int32 TeamId) const
	{
		if (auto ElemPtr = TeamConfigArr.FindByPredicate( [=](const UTeamConfig* Entry) { return Entry->TeamIndex == TeamId;} ))
		{
			return *ElemPtr;
		}

		return nullptr;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, IsBlueprintBase) )
class GASUDEMY_API UGU_TeamComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGU_TeamComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 TeamIndex;

	static UTeamSettingsDatabase* TeamSettings;

public:
	UFUNCTION(BlueprintPure)
	static const UTeamSettingsDatabase* GetTeamSettings() { return TeamSettings; }
	
	UFUNCTION(BlueprintCallable)
	void ChangeTeamIndex(int32 NewTeamIndex) { TeamIndex = NewTeamIndex; }
	
	UFUNCTION(BlueprintCallable)
	int32 GetTeamIndex() const { return TeamIndex; }
	
};

inline ETeamRelationType UTeamSettingsDatabase::GetTeamsRelationByComp(const UGU_TeamComponent* TeamCompLeft, const UGU_TeamComponent* TeamCompRight, bool bReturnDefaultRelOnFail) const
{
	if (TeamCompLeft && TeamCompRight)
	{
		return GetTeamsRelationById(TeamCompLeft->GetTeamIndex(), TeamCompRight->GetTeamIndex(), bReturnDefaultRelOnFail);
	}

	if (bReturnDefaultRelOnFail)
	{
		return DefaultRelation;
	}

	return ETeamRelationType::Undefined;
}
