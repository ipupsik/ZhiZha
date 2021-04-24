#pragma once

struct HitResult
{
	bool DoesHit;
	struct
	{
		float x, y, z;
	} HitLocation;
	class Actor* HitActor;
};