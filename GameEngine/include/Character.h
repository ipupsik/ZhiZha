#pragma once

#include "Actor.h"

class ACharacter : public Actor
{
public:
	ACharacter();

	void ControllerInput();
	void CameraManagement();

	void Jump();
	void GoRight();
	void GoLeft();

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

public:
	bool IsJumping;
};