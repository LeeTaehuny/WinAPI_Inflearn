#pragma once
#include "Object.h"
class Bullet : public Object
{
public:
	Bullet();
	virtual ~Bullet() override;

	// 부모 클래스에서 만들어진 순수 가상함수를 재정의합니다.
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	// 스피드를 반환하기 위한 함수를 정의합니다.
	Vector GetSpeed() { return _speed; }
	// 스피드를 설정하기 위한 함수를 정의합니다.
	void SetSpeed(Vector speed) { _speed = speed; }

	// 발사한 주체를 반환하기 위한 함수를 정의합니다.
	Object* GetOwner() { return _owner; }
	// 발사한 주체를 설정하기 위한 함수를 정의합니다.
	void SetOwner(Object* owner) { _owner = owner; }

public:
	// 스피드를 저장할 변수를 선언합니다.
	Vector _speed = {};

	// 자신을 발사한 주체를 저장하기 위한 변수를 선언합니다.
	Object* _owner = nullptr;
};

