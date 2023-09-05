#pragma once
#include "Scene.h"

// 메뉴씬의 역할
// * 특정 키(E)를 누르면 포트리스 씬으로 넘어가도록 해주는 역할
// * 게임의 시작 화면
class MenuScene : public Scene
{
public:
	MenuScene();
	virtual ~MenuScene() override;

	// 부모 클래스의 함수를 오버라이드 합니다.
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

};

