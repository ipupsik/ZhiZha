#include <SFML/Window/Keyboard.hpp>

#include "Character.h"
#include "PupsyaGlobals.h"

using sf::Keyboard;

ACharacter::ACharacter() {
    IsJumping = false;
}

void ACharacter::ControllerInput() {
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        Jump();
    }

    if (Keyboard::isKeyPressed(Keyboard::A)) {
        Collider[0]->Velocity.X = -1.0f / 100;
    } else if (Keyboard::isKeyPressed(Keyboard::D)) {
        Collider[0]->Velocity.X = 1.0f / 100;
    } else {
        Collider[0]->Velocity.X = 0.0f;
    }
}

void ACharacter::CameraManagement() {

}

void ACharacter::Jump() {
    Collider[0]->Velocity.Y = 0.005;
}

void ACharacter::BeginPlay() {

}

void ACharacter::Tick(float DeltaSeconds) {
    ControllerInput();

    for (auto &OwnCollderit : Collider) {
        OwnCollderit->UpdatePhysicState(DeltaSeconds);
    }

    Location.X += dynamic_cast<CollisionSphere *>(Collider[0])->Position.X;
    Location.Y += dynamic_cast<CollisionSphere *>(Collider[0])->Position.Y;

    dynamic_cast<CollisionSphere *>(Collider[0])->Position.X = 0;
    dynamic_cast<CollisionSphere *>(Collider[0])->Position.Y = 0;

    for (auto &OwnCollderit : Collider) {
        for (auto &ActorElem : World->WorldActors) {
            for (auto &OtherColliderit : ActorElem->Collider) {
                if (OwnCollderit != OtherColliderit) {
                    HitResult tmp;
                    OwnCollderit->CollisionDetection(OtherColliderit, tmp);
                }
            }
        }
    }

    Actor::Tick(DeltaSeconds);
}
