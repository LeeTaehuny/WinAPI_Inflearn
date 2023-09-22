#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
	using Super = Collider;
public:
	BoxCollider();
	virtual ~BoxCollider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	// 충돌을 판별하기 위한 함수를 선언합니다.
	virtual bool CheckCollision(Collider* other);

	// 사각형의 크기를 반환하기 위한 함수를 정의합니다.
	Vec2 GetSize() { return _size; }
	// 사각형의 크기를 설정하기 위한 함수를 정의합니다.
	void SetSize(Vec2 size) { _size = size; }

private:
	// 크기를 저장하기 위한 변수를 선언합니다.
	Vec2 _size = {};
};

