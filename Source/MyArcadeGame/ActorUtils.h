#pragma once

#include "GameFramework/Actor.h"

class ActorUtils{
public:

	inline static void Disable(AActor* actor)  
	{
		actor->SetActorEnableCollision(false);
		actor->SetActorHiddenInGame(true);
		actor->SetActorTickEnabled(false);
	}

};