// Copyright Kevin.Liu@47129927@qq.com

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

// 向前声明
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;

/**
 * 
 */
UCLASS()
class OPENRPG_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	// 我们需要用回调函数将这两个链接到一起
	// 每当我们按下wsad，会根据我们的映射配置（InputMapping）将输入数据想填充到 MoveAction中
	// Move函数接收这个参数
	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();
	// 用两个指针来保存当前鼠标下的 Actor 和上一个鼠标下的 Actor
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
};
