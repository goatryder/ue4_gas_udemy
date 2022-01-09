// Fill out your copyright notice in the Description page of Project Settings.


#include "GU_TeamComponent.h"

UTeamSettingsDatabase* UGU_TeamComponent::TeamSettings = nullptr;


ETeamRelationType UTeamSettingsDatabase::GetTeamsRelationByActor(const AActor* FirstActor, const AActor* SecondActor, bool bTraverseOwners, bool bReturnDefaultRelOnFail) const
{
	auto FindTeamComp = [=](const AActor* A)
	{
		auto TeamComp = (UGU_TeamComponent*)A->GetComponentByClass(UGU_TeamComponent::StaticClass());
		if (TeamComp)
		{
			return TeamComp;
		}
		
		if (bTraverseOwners)
		{
			while (A)
			{
				A = A->GetOwner();
				if (A)
				{
					TeamComp = (UGU_TeamComponent*)A->GetComponentByClass(UGU_TeamComponent::StaticClass());
					if (TeamComp)
					{
						return TeamComp;
					}
				}
			}
		}

		return (UGU_TeamComponent*)nullptr;
	};
	
	auto FirstTeamComp = FindTeamComp(FirstActor);
	auto SecondTeamComp = FindTeamComp(SecondActor);

	return GetTeamsRelationByComp(FirstTeamComp, SecondTeamComp, bReturnDefaultRelOnFail);
}

// Sets default values for this component's properties
UGU_TeamComponent::UGU_TeamComponent()
{
	static bool TeamSettingsInitialized = [&]()
	{
		const ConstructorHelpers::FObjectFinder<UTeamSettingsDatabase> TeamSettingsFinder(TEXT("TeamSettingsDatabase'/Game/Blueprints/Team/DA_TeamRelations.DA_TeamRelations'"));
		TeamSettings = TeamSettingsFinder.Object;
		return true;
	} ();
}


// Called when the game starts
void UGU_TeamComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
