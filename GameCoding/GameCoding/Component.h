#pragma once

class Actor;

// GameObject에 끼워서 사용할 부품 클래스
class Component
{
public:
	Component();
	virtual ~Component();

	virtual void BeginPlay() { }
	virtual void TickComponent() { }
	virtual void Render(HDC hdc) { }

	// owner를 설정하고 반환하는 함수를 정의합니다.
	void SetOwner(Actor* owner) { _owner = owner; }
	Actor* GetOwner() { return _owner; }

protected:
	// owner (컴포넌트들 추가한 게임 오브젝트 정보)를 저장할 변수를 선언합니다.
	Actor* _owner = nullptr;
};

