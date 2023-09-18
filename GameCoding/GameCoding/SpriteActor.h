#pragma once
#include "Actor.h"

class Sprite;

// 액터 중에 스프라이트를 그려주는 액터 클래스입니다.
class SpriteActor : public Actor
{
	using Super = Actor;

public:
	SpriteActor();
	virtual ~SpriteActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;

	virtual void Render(HDC hdc) override;

	// 스프라이트를 설정하기 위한 함수를 정의합니다.
	void SetSprite(Sprite* sprite) { _sprite = sprite; }

protected:
	// 스프라이트를 저장하기 위한 변수를 선언합니다.
	Sprite* _sprite = nullptr;
};

