#ifndef _H_HITRESULT_
#define _H_HITRESULT_

#include "Actor.h"

class HitResult
{
	bool DoesHit;
	struct
	{
		float x, y, z;
	} HitLocation;
	Actor* HitActor;
};

#endif