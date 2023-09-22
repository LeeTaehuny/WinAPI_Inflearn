#pragma once

class Component;
class Collider;

// 씬에 배치 가능한 오브젝트 클래스입니다.
class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void BeginPlay();
	virtual void Tick();

	virtual void Render(HDC hdc);

	// 위치 정보를 설정하기 위한 함수를 정의합니다.
	void SetPos(Vec2 pos) { _pos = pos; }
	// 위치 정보를 반환하기 위한 함수를 정의합니다.
	Vec2 GetPos() { return _pos; }

	// 컴포넌트를 추가하는 함수를 선언합니다.
	void AddComponent(Component* component);
	// 컴포넌트를 제거하는 함수를 선언합니다.
	void RemoveComponent(Component* component);

	// 레이어의 타입을 설정하기 위한 함수를 정의합니다.
	void SetLayer(LAYER_TYPE layer) { _layer = layer; }
	// 레이어의 타입을 반환하기 위한 함수를 정의합니다.
	LAYER_TYPE GetLayer() { return _layer; }

	// 충돌이 발생하면 호출될 함수를 선언합니다.
	// * 어떤 컴포넌트가 충돌했는지 (collider)
	// * 상대방은 어떤 컴포넌트인지 (other)
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

protected:
	// 씬에 배치가 가능하다는 것은 위치 정보를 가지고 있다는 의미입니다.
	// * 위치 정보를 저장하기 위한 변수를 선언합니다.
	Vec2 _pos = { 0,0 };

	// 컴포넌트를 저장하기 위한 배열을 선언합니다.
	vector<Component*> _components;

	// 액터의 종류를 구분하기 위한 변수를 선언합니다.
	LAYER_TYPE _layer = LAYER_OBJECT;

private:
	// 여기에 스프라이트 or 텍스쳐를 넣어줄 수도 있음
	// * 하드코딩
	// * 모든 액터가 스프라이트를 들고 있는 것이 아닐 수도 있기 때문

	// * 언리얼은 상속 구조로 스프라이트를 들고 있는 액터를 추가로 만들어주는 방식
};

