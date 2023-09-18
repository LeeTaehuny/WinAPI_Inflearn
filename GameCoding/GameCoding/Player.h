#pragma once
#include "FlipbookActor.h"

class Flipbook;

class Player : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;

	virtual void Render(HDC hdc) override;

private:
	// 애니메이션을 저장할 변수를 선언합니다.
	Flipbook* _flipbookUp = nullptr;
	Flipbook* _flipbookDown = nullptr;
	Flipbook* _flipbookLeft = nullptr;
	Flipbook* _flipbookRight = nullptr;
};

