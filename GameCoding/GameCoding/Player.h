#pragma once
#include "FlipbookActor.h"

class Flipbook;
class BoxCollider;

// 플레이어의 상태를 구분하기 위한 열거형을 선언합니다.
enum class PlayerState
{
	MoveGround,
	JumpFall,
};

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

public:
	// 플레이어의 상태를 설정 & 반환하기 위한 함수들을 선언합니다.
	void SetState(PlayerState state);
	PlayerState GetState() { return _state; }

private:
	// 점프를 위한 함수를 선언합니다.
	void Jump();
	// 중력을 적용하기 위한 함수를 선언합니다.
	void TickGravity();
	// 충돌한 영역 만큼 뒤로 밀쳐주기 위한 함수를 선언합니다.
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);

private:
	// 플레이어의 상태에 따라 업데이트해주기 위한 함수를 선언합니다.
	// * 주로 상태를 묶어주는 경우이므로 최상위 클래스에서 가상함수로 선언하는 것이 좋습니다.
	virtual void TickMoveGround();
	virtual void TickJumpFall();

	// 공용으로 사용할 입력 함수를 선언합니다.
	void TickInput();

private:
	// 애니메이션을 저장할 변수를 선언합니다.
	Flipbook* _flipbookUp = nullptr;
	Flipbook* _flipbookDown = nullptr;
	Flipbook* _flipbookLeft = nullptr;
	Flipbook* _flipbookRight = nullptr;

private:
	// 플레이어의 속도를 저장하기 위한 변수를 선언합니다.
	Vec2 _speed = { };
	// 중력 값을 저장하기 위한 변수를 선언합니다.
	int32 _gravity = 1000;

	// 플레이어의 상태를 저장하기 위한 변수를 선언합니다.
	PlayerState _state = PlayerState::JumpFall;
};

