#pragma once
#include "FlipbookActor.h"

class Flipbook;
class BoxCollider;

class Player : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;

	virtual void Render(HDC hdc) override;

	// 충돌이 발생하면 호출될 함수를 선언합니다.
	// * 어떤 컴포넌트가 충돌했는지 (collider)
	// * 상대방은 어떤 컴포넌트인지 (other)
	// ** OnComponentBeginOverlap() : 충돌이 발생한 시점에 1회 호출되는 함수 
	// ** OnComponentEndOverlap() : 충돌이 발생한 후 해당 영역을 벗어날 때 1회 호출되는 함수 
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) override;

private:
	void TickGravity();
	// 충돌한 영역 만큼 뒤로 밀쳐주기 위한 함수를 선언합니다.
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);

private:
	// 애니메이션을 저장할 변수를 선언합니다.
	Flipbook* _flipbookUp = nullptr;
	Flipbook* _flipbookDown = nullptr;
	Flipbook* _flipbookLeft = nullptr;
	Flipbook* _flipbookRight = nullptr;
};

