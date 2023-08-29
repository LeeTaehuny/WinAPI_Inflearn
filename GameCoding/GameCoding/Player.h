#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player();
	virtual ~Player() override;

	// 부모 클래스에서 만들어진 순수 가상함수를 재정의합니다.
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// 실제 미사일이 발사될 위치를 받아오는 함수를 선언합니다.
	Pos GetFirePos();

public:
	// 포신의 각도를 저장할 변수를 선언합니다.
	float _barrelAngle = 0.0f;
	// 포신의 길이를 저장할 변수를 선언합니다.
	float _barrelLength = 100.0f;
};

