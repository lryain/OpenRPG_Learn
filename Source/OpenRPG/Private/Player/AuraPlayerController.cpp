// Copyright Kevin.Liu@47129927@qq.com


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit) return;
	// 用两个指针来保存当前鼠标下的 Actor 和上一个鼠标下的 Actor
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	* Line trace from cursor. There are several scenarios:
	* A: LastActor is null && ThisActor is null
	*	- Do nothing
	* B: LastActor is null && ThisActor is valid
	*	- Highlight ThisActor
	* C: LastActor is valid && ThisActor is null
	*	- UnHighlight LastActor
	* D: Both actors are valid, but LastActor != ThisActor 我们从一个 Actor 切换到另一个 Actor
	*	- UnHighlight LastActor and Highlight ThisActor
	* E: Both actors are valid, and are the same actor
	*	- Do nothing
	*/
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B - 
			ThisActor->HighlightActor();

		}
		else
		{
			// Case A - both are ull, do nothing
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr) {
			// Case C - UnHighlight LastActor
			LastActor->UnHighlightActor();
		}
		else // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();

			}
			else
			{
				// Case E - both are valid and the same, do nothing
			}
		}
	}

}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	// 设置输入映射上下文 InputMappingContext
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 不要锁住视角
	InputModeData.SetHideCursorDuringCapture(false); // 显示光标
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	// 绑定输入回调函数
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

}

// 输入回调函数
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	//根据 xy 分量来控制角色移动
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

