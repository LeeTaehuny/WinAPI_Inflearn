#pragma once

// 화면을 그리고 싶을 때 화면에 있는 모든 처리(물체를 들고있는 등) 역할을 합니다.
class Scene
{
public:
	Scene();
	virtual ~Scene();

	// 자식 클래스에서 구현해야 할 기능들을 순수 추상 함수로 선언합니다.
	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

protected:

};

