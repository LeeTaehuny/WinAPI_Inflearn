#pragma once
#include "Scene.h"

class Actor;
class UI;
class TilemapActor;
//class GameObject;

// 개발용 씬으로 Scene를 상속받습니다.
class DevScene : public Scene
{
	using Super = Scene;
public:
	DevScene();
	virtual ~DevScene() override;

	// 부모 클래스의 함수를 오버라이드 합니다.
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Clear();

	// tilemap을 빠르게 접근하기 위해 저장해둘 변수
	TilemapActor* _tilemapActor = nullptr;
};

