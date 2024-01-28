// Copyright Predict Edumedia


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
                                                FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
	
	for (const FGameplayTag& Tag : TagContainer)
	{
		// TODO: Broadcast the tag to the WidgetController
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		// GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green, Msg);
	}
}
