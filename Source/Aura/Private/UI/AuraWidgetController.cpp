// Copyright Predict Edumedia


#include "UI/AuraWidgetController.h"

//Helper function that just sets the values of the params from those in the struct.
void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}
//

void UAuraWidgetController::BroadcastInitialValues()
{
	
}


