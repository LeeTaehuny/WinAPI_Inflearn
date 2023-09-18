#pragma once
#include "Actor.h"

class Flipbook;

// 애니메이션을 사용하는 액터 클래스입니다.
class FlipbookActor : public Actor
{
	using Super = Actor;
public:
	FlipbookActor();
	virtual ~FlipbookActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;

	virtual void Render(HDC hdc) override;

	// 애니메이션을 설정하기 위한 함수를 선언합니다.
	void SetFlipbook(Flipbook* flipbook);
	// 애니메이션을 초기화(처음부터 재생)하기 휘안 함수를 선언합니다.
	void Reset();

protected:
	// 애니메이션을 저장하기 위한 변수를 선언합니다.
	Flipbook* _flipbook = nullptr;

	// 누적 시간을 저장할 변수를 선언합니다.
	float _sumTime = 0.0f;

	// 애니메이션을 어디까지 재생했는지를 저장하기 위한 변수를 선언합니다.
	int32 _idx = 0;
};

