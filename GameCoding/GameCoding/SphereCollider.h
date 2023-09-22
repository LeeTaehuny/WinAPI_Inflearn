#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
	using Super = Collider;
public:
	SphereCollider();
	virtual ~SphereCollider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	// 충돌을 판별하기 위한 함수를 선언합니다.
	virtual bool CheckCollision(Collider* other);

	// 원의 반지름을 반환하기 위한 함수를 정의합니다.
	float GetRadius() { return _radius; }
	// 원의 반지름을 설정하기 위한 함수를 정의합니다.
	void SetRadius(float radius) { _radius = radius; }

private:
	// 원의 반지름을 저장하기 위한 변수를 선언합니다.
	float _radius = 0.0f;
};

