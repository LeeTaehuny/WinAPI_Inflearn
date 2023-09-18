#include "pch.h"
#include "Player.h"
#include "InputManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	// 부모의 함수 내용을 불러옵니다.
	Super::BeginPlay();
}

void Player::Tick()
{
	// 부모의 함수 내용을 불러옵니다.
	Super::Tick();

	// TODO : 플레이어의 업데이트
	
	// ex) 이동
	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		// 위로 움직여라.
	}
}

void Player::Render(HDC hdc)
{
	// 부모의 함수 내용을 불러옵니다.
	Super::Render(hdc);
}
