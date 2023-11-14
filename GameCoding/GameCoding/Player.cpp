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

	// 프레임 시간을 받아옵니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// TODO : 플레이어의 업데이트
	
	// 위로 이동
	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		// 위치를 이동시켜줍니다.
		_pos.y -= 200 * deltaTime;
		// 위로 이동하는 애니메이션으로 설정합니다.
		SetFlipbook(_flipbookUp);
	}
	// 아래로 이동
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		// 위치를 이동시켜줍니다.
		_pos.y += 200 * deltaTime;
		// 위로 이동하는 애니메이션으로 설정합니다.
		SetFlipbook(_flipbookDown);
	}
	// 왼쪽으로 이동
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
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
}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	int k = 0;
}

void Player::TickGravity()
{
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
