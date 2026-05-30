// Copyright Kevin.Liu@47129927@qq.com

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class OPENRPG_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	// 存储角色Ability和属性的指针
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent; // AAuraEnemy 中初始化

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
