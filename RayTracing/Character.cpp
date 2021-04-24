#include "Character.h"
#include "PupsyaGlobals.h"

#include <Windows.h>

ACharacter::ACharacter()
{
	IsJumping = false;
}

void ACharacter::ControllerInput()
{
	if (GetKeyState(VK_SPACE) > 0 && !IsJumping)
	{
		Jump();
		IsJumping = true;
	}
}

void ACharacter::CameraManagement()
{

}

void ACharacter::Jump()
{
	MainCollision->Velocity.Y = 0.005;
}

void ACharacter::BeginPlay()
{

}

void ACharacter::Tick(float DeltaSeconds)
{
	ControllerInput();

	if (Collider)
	{
		MainCollision->UpdatePhysicState(DeltaSeconds);
		for (auto& OwnCollderit : *Collider)
		{
			OwnCollderit->UpdatePhysicState(DeltaSeconds);
		}
	}

	Location.X += MainCollision->Position.X;
	Location.Y += MainCollision->Position.Y;

	MainCollision->Position.X = 0;
	MainCollision->Position.Y = 0;

	if (Collider)
		for (auto& OwnCollderit : *Collider)
		{
			for (auto& ActorElem : World->WorldActors)
			{
				if (ActorElem->Collider)
					for (auto& OtherColliderit : *ActorElem->Collider)
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
