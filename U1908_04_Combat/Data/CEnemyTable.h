#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "CEnemyTable.generated.h"

USTRUCT(BlueprintType)
struct FEnemySheet : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
		FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
		FString Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
		FString MaterialChest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
		float Power;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
		float PlayRate;
};

UCLASS()
class U1908_04_COMBAT_API UCEnemyTable : public UObject
{
	GENERATED_BODY()

public:
	UCEnemyTable();

	void GetRows(TArray<FEnemySheet *>& Arr);
	const FEnemySheet* GetRow(uint32 RowIndex);

public:
	const FString MaterialPath = "/Game/Character/Materials/";

private:
	UDataTable* Table;
};
