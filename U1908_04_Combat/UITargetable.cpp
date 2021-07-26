// Fill out your copyright notice in the Description page of Project Settings.


#include "UITargetable.h"


bool IUITargetable::OnSelected()
{
	return false;
}

bool IUITargetable::OnDeselected()
{
	return false;
}

bool IUITargetable::IsTargetable()
{
	return false;
}
