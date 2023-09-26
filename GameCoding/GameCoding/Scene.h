#pragma once

class Actor;
class UI;

// 화면을 그리고 싶을 때 화면에 있는 모든 처리(물체를 들고있는 등) 역할을 합니다.
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

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

