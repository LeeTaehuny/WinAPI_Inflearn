#pragma once


// GameObject에 끼워서 사용할 부품 클래스
class Component
{
public:
	virtual void Start() { }
	virtual void Update() { }
	virtual void Render(HDC hdc) { }

	// owner (컴포넌트들 추가한 게임 오브젝트 정보)
	//GameObject* _owner;
};

