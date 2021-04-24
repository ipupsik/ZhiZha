#include "Character.h"
#include "PupsyaGlobals.h"

void ACharacter::ControllerInput()
{
}

void ACharacter::CameraManagement()
{
}

void ACharacter::BeginPlay()
{
}

void ACharacter::Tick(float DeltaSeconds)
{
	ControllerInput();

	if (Collider)
		for (auto& OwnCollderit : *Collider)
		{
			for (auto& Actors : World->WorldActors)
			{
				for (auto& OtherColliderit : *Actors->Collider)
				{
					if (OwnCollderit != OtherColliderit)
					{
						HitResult tmp;
						OwnCollderit->CollisionDetection(OtherColliderit, tmp);
					}
				}
			}
		}

	Actor::Tick(DeltaSeconds);
}
