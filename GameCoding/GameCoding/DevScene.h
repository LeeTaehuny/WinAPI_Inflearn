#pragma once
#include "Scene.h"

// 개발용 씬으로 Scene를 상속받습니다.
class DevScene : public Scene
{
public:
	DevScene();
	virtual ~DevScene() override;

	// 부모 클래스의 함수를 오버라이드 합니다.
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	// test player
	// * 플레이어의 현재 좌표를 저장할 변수를 선언합니다.
	Pos _playerPos = { 300, 300 };

	// test speed
	// * 플레이어의 이동 속도를 저장할 변수를 선언합니다.
	float _speed = 1000.0f;
};

