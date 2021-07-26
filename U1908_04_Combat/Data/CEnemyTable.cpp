#include "CEnemyTable.h"
#include "Global.h"

UCEnemyTable::UCEnemyTable()
{
	FString path = L"DataTable'/Game/Sheets/EnemySheet.EnemySheet'";
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable(*path);
	if (dataTable.Succeeded())
		Table = dataTable.Object;
}

void UCEnemyTable::GetRows(TArray<FEnemySheet*>& Arr)
{
	Table->GetAllRows("", Arr);
}

const FEnemySheet * UCEnemyTable::GetRow(uint32 RowIndex)
{
	FString str = FString::FromInt((int)RowIndex);

	return Table->FindRow<FEnemySheet>(FName(*str), "");
}
