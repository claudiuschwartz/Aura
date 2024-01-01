// Copyright Predict Edumedia


#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"


AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->CustomDepthStencilValue = CUSTOM_DEPTH_RED;

	Weapon->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Weapon->CustomDepthStencilValue = CUSTOM_DEPTH_RED;
	
}

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
