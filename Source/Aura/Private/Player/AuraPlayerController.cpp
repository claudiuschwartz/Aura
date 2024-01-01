// Copyright Predict Edumedia


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext); //Checks if AuraContext (IMC) is set. //This is an "assert" It crashes game if the pointer isn't set.//

	//Subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check (Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);
	//

	//Cursor
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	//

	//InputMode
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	//
	
}
