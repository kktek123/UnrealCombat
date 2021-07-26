#include "CGameMode.h"
#include "Global.h"
#include "CPlayer.h"
#include "CPlayerController.h"

ACGameMode::ACGameMode()
{
	FString path = L"";

	path = L"Blueprint'/Game/Blueprints/BpCPlayer.BpCPlayer_C'";
	ConstructorHelpers::FClassFinder<ACPlayer> player(*path);

	if (player.Succeeded())
		DefaultPawnClass = player.Class;


	path = L"Blueprint'/Game/Blueprints/BpCPlayerController.BpCPlayerController_C'";
	ConstructorHelpers::FClassFinder<ACPlayerController> controller(*path);

	if (controller.Succeeded())
		PlayerControllerClass = controller.Class;

}