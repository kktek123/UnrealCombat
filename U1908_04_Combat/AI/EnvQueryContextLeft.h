// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvQueryContextLeft.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UEnvQueryContextLeft : public UEnvQueryContext
{
	GENERATED_BODY()

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
	
	//UFUNCTION(BlueprintImplementableEvent)
	 void ProvideSingleLocation(UObject* QuerierObject, AActor* QuerierActor, FVector& ResultingLocation) const;

};
