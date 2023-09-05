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
};

