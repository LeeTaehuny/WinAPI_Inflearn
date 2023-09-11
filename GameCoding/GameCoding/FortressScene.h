#pragma once
#include "Scene.h"
class FortressScene : public Scene
{
public:
	FortressScene();
	virtual ~FortressScene() override;

	// 부모 클래스의 함수를 오버라이드 합니다.
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	// 턴을 넘겨주기 위한 함수를 선언합니다.
	void ChangePlayerTurn();

// Turn
private:
	// 현재 어떤 플레이어의 턴인지를 구분하기 위한 변수를 선언합니다.
	int32 _playerTurn = 1;

	// 누적 시간을 저장하기 위한 변수를 선언합니다.
	float _sumTime = 0.0f;

};

