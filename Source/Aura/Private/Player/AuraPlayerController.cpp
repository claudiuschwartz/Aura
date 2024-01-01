// Copyright Predict Edumedia


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
}

//Player tick
void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	
}
//

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	 *Line trace from cursor -> Scenarios:
	 *A. LastActor is null && LastActor is null
	 *		- Do nothing.
	 *B. LastActor is null && ThisActor is valid
	 *		- Highlight ThisActor
	 *C. LastActor is valid && ThisActor is null
	 *		- Unhighlight LastActor
	 *D. Both actors are valid, but LastActor != ThisActor
	 *		- Unhighlight LastActor, and Highlight ThisActor
	 *E. Both actors are valid, and are the same actor
	 *		- Do nothing.
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor !=nullptr) //ThisActor is valid
		{
			//Case B
			ThisActor->HighlightActor();
		}
		else
		{
			//Case A (do nothing)
		}
	}
	else //LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			//Case C
			LastActor->UnHighlightActor();
		}
		else //Both actors are valid (either they're both the same actor or different actors - cases D or E)
		{
			if (LastActor != ThisActor) //Case D
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				//Case E (do nothing)
			}
		}
	}
	
}

//BeginPlay
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
//

//InputComponent
void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}
//

//Move
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
//
