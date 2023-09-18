#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "TimeManager.h"


Player::Player()
{
	// 애니메이션을 저장합니다.
	_flipbookUp = GET_SINGLE(ResourceManager)->GetFilpbook(L"FB_MoveUp");
	_flipbookDown = GET_SINGLE(ResourceManager)->GetFilpbook(L"FB_MoveDown");
	_flipbookLeft = GET_SINGLE(ResourceManager)->GetFilpbook(L"FB_MoveLeft");
	_flipbookRight = GET_SINGLE(ResourceManager)->GetFilpbook(L"FB_MoveRight");
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
