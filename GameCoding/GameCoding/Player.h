#pragma once
#include "SpriteActor.h"

class Player : public SpriteActor
{
	using Super = SpriteActor;

public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;

	virtual void Render(HDC hdc) override;
};

