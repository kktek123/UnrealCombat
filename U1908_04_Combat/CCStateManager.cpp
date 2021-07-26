

#include "CCStateManager.h"
#include "Global.h"

UCCStateManager::UCCStateManager()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCCStateManager::SetState(E_State State)
{
	E_State PrevState = E_State::Idle;
	//UKismetSystemLibrary::K2_ClearTimer(this, FString("UCCStateManager::SetIdleState()"));
	PrevState = CurrentState;
	CurrentState = State;
	if (CurrentState != PrevState)
		OnStateChanged.Broadcast(PrevState, CurrentState);

}

E_State UCCStateManager::GetState()
{
	return CurrentState;
}

void UCCStateManager::SetActivity(E_Activity Activity, bool Value)
{
	if (GetActivityValue(Activity) != Value)
	{
		
		Activities.Add(Activity, Value);
		intActivities.Add(Activity, 300.0f);
		OnActivityChanged.Broadcast(Activity, Value);
		float* a = intActivities.Find(Activity);
		//if(Value)
		//	
		//else
		//	CLog::Print(TEXT("false"));
	}
}

bool UCCStateManager::GetActivityValue(E_Activity Activity)
{
	
	if (Activities.Find(Activity))
	{
		bool *value = Activities.Find(Activity);
		return *value;
	}
	else
	{
		return false;
	}
}

void UCCStateManager::ResetState(float InTime)
{
	if (GetState() != E_State::Dead)
	{
		if (InTime <= 0)
		{
			SetIdleState();
		}
		else
		{
			FTimerHandle timerhandle;
			//UKismetSystemLibrary::K2_SetTimer(this, FString("SetIdleState()"), InTime, false);
			GetOwner()->GetWorldTimerManager().SetTimer(timerhandle, this, &UCCStateManager::SetIdleState, InTime, false);

		}
	}
}

void UCCStateManager::SetIdleState()
{
	SetState(E_State::Idle);
}

void UCCStateManager::BeginPlay()
{
	Super::BeginPlay();
}

void UCCStateManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
