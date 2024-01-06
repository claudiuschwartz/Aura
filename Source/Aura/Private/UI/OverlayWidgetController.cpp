// Copyright Predict Edumedia


#include "UI/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AuraAttributeSet->Health.GetCurrentValue());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->MaxHealth.GetCurrentValue());
	OnManaChanged.Broadcast(AuraAttributeSet->Mana.GetCurrentValue());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->MaxMana.GetCurrentValue());
}
