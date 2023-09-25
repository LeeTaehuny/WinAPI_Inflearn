#pragma once
#include "Scene.h"

class Actor;
class UI;
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

	// 액터를 추가하기 위한 함수를 선언합니다.
	void AddActor(Actor* actor);
	// 액터를 제거하기 위한 함수를 선언합니다.
	void RemoveActor(Actor* actor);

public:
	// 액터들을 한 번에 관리하기 위한 벡터 컨테이너를 선언합니다.
	// * 레이어 별로 구분해서 사용하기 위해 2차원 벡터 컨테이너로 변경합니다.
	vector<Actor*> _actors[LAYER_MAXCOUNT];

	// UI들을 저장하기 위한 벡터 컨테이너를 선언합니다.
	vector<UI*> _uis;
};

