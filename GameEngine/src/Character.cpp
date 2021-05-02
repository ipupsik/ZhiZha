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

    float &x = dynamic_cast<CollisionSphere *>(Collider[0].get())->Position.X;
    float &y = dynamic_cast<CollisionSphere *>(Collider[0].get())->Position.Y;
    Location.X += x;
    Location.Y += y;

    x = 0;
    y = 0;

    for (auto &OwnCollderit : Collider) {
        for (auto &ActorElem : World->WorldActors) {
            for (auto &OtherColliderit : ActorElem->Collider) {
                if (OwnCollderit != OtherColliderit) {
                    HitResult tmp;
                    OwnCollderit->CollisionDetection(std::move(OtherColliderit), tmp);
                }
            }
        }
    }

    Actor::Tick(DeltaSeconds);
}
