#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "TimeManager.h"
#include "CameraComponent.h"
#include "BoxCollider.h"


Player::Player()
{
	// 애니메이션을 저장합니다.
	_flipbookUp = GET_SINGLE(ResourceManager)->GetFilpbook(L"FB_MoveUp");
	_flipbookDown = GET_SINGLE(ResourceManager)->GetFilpbook(L"FB_MoveDown");
	_flipbookLeft = GET_SINGLE(ResourceManager)->GetFilpbook(L"FB_MoveLeft");
	_flipbookRight = GET_SINGLE(ResourceManager)->GetFilpbook(L"FB_MoveRight");

	// 카메라 컴포넌트를 생성합니다.
	CameraComponent* camera = new CameraComponent();
	// 카메라 컴포넌트를 컴포넌트들의 배열에 추가합니다.
	AddComponent(camera);
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	// 부모의 함수 내용을 불러옵니다.
	Super::BeginPlay();
	
	// 시작 애니메이션을 설정합니다.
	SetFlipbook(_flipbookDown);
}

void Player::Tick()
{
	// 부모의 함수 내용을 불러옵니다.
	Super::Tick();

	/** 플레이어의 상태에 따라 분기합니다. */
	switch (_state)
	{
	case PlayerState::MoveGround:
		TickInput();
		TickMoveGround();
		break;
	case PlayerState::JumpFall:
		TickInput();
		TickJumpFall();
		break;
	}

	TickGravity();
}

void Player::Render(HDC hdc)
{
	// 부모의 함수 내용을 불러옵니다.
	Super::Render(hdc);
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	// 박스 콜라이더 형식으로 형변환합니다.
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr) return;

	// 충돌한 영역만큼 뒤로 미루기 위한 함수를 호출합니다.
	AdjustCollisionPos(b1, b2);

	// 충돌한 대상이 땅이라면?
	if (b2->GetCollisionLayerType() == CLT_GROUND)
	{
		SetState(PlayerState::MoveGround);
	}
}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	// 박스 콜라이더 형식으로 형변환합니다.
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr) return;

	if (b2->GetCollisionLayerType() == CLT_GROUND)
	{

	}
}

void Player::SetState(PlayerState state)
{
	// 현재 상태와 이전 상태가 같으면 리턴합니다.
	if (_state == state)
		return;

	// 변경할 state에 대해 처리할 부분이 있으면 switch문을 이용해 처리해주도록 합니다.
	// + 추가로 상태에 대한 디버깅을 할 때 여기서만 하면 되므로 편리합니다.
	switch (state)
	{
	case PlayerState::MoveGround:
		_speed.y = 0;
		break;
	case PlayerState::JumpFall:
		break;
	}

	// 현재 상태에 전달받은 상태를 반영해줍니다.
	_state = state;
}

void Player::Jump()
{
	// 이중점프 제한 (플레이어의 상태가 점프 상태라면 리턴)
	if (_state == PlayerState::JumpFall)
		return;

	// 플레이어의 현재 상태를 점프 상태로 변경합니다.
	SetState(PlayerState::JumpFall);
	_speed.y = -500;
}

void Player::TickGravity()
{
	// 물리 공식
	// -> v = at
	// -> s = vt

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	if (deltaTime > 0.1f)
	{
		return;
	}

	// y의 속도를 증가시킵니다. (아래 방향으로 떨어지기 위함)
	_speed.y += _gravity * deltaTime;
	// 증가된 y값을 pos에 반영시켜줍니다.
	_pos.y += _speed.y * deltaTime;
}

void Player::AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2)
{
	// 각각의 영역을 가져옵니다.
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	Vec2 pos = GetPos();

	// 각각의 영역이 충돌한 결과 충돌 영역을 추출합니다.
	RECT intersect = {};
	if (::IntersectRect(&intersect, &r1, &r2))
	{
		// 충돌한 영역의 어느 면이 길이가 더 긴지 체크합니다.
		int32 w = intersect.right - intersect.left;
		int32 h = intersect.bottom - intersect.top;

		// 만약 가로 길이가 더 크다면?
		if (w > h)
		{
			// 선분의 길이에 따라 다시 밀어줍니다.
			if (intersect.top == r2.top)
			{
				pos.y -= h * 2;
			}
			else
			{
				pos.y += h * 2;
			}
		}
		else
		{
			if (intersect.left == r2.left)
			{
				pos.x -= w * 2;
			}
			else
			{
				pos.x += w * 2;
			}
		}
	}

	// 밀쳐진 위치를 다시 적용합니다.
	SetPos(pos);
}

void Player::TickMoveGround()
{
	// 점프는 땅에 있을 때만 가능합니다.
	// * 점프 입력은 TickMoveGround() 함수 내부에서 받아줍니다.
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		Jump();
	}
}

void Player::TickJumpFall()
{
}

void Player::TickInput()
{
	// 프레임 시간을 받아옵니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 왼쪽으로 이동
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		// 위치를 이동시켜줍니다.
		_pos.x -= 200 * deltaTime;
		// 위로 이동하는 애니메이션으로 설정합니다.
		SetFlipbook(_flipbookLeft);
	}
	// 오른쪽으로 이동
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		// 위치를 이동시켜줍니다.
		_pos.x += 200 * deltaTime;
		// 위로 이동하는 애니메이션으로 설정합니다.
		SetFlipbook(_flipbookRight);
	}
}
