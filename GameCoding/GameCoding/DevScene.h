#pragma once
#include "Scene.h"

class Actor;
//class GameObject;

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
	// 액터들을 한 번에 관리하기 위한 벡터 컨테이너를 선언합니다.
	vector<Actor*> _actors;

	//GameObject* _go;
};

