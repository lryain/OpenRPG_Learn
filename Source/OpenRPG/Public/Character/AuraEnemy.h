// Copyright Kevin.Liu@47129927@qq.com

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class OPENRPG_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	/** EnemyInterface 接口开始*/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/* EnemyInterface 接口结束 */

protected:
	virtual void BeginPlay() override;
};
