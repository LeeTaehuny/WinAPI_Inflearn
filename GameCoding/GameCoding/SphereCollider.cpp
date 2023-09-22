#include "pch.h"
#include "SphereCollider.h"
#include "SceneManager.h"
#include "Actor.h"
#include "BoxCollider.h"

SphereCollider::SphereCollider() : Collider(ColliderType::Sphere)
{

}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::BeginPlay()
{
	Super::BeginPlay();
}

void SphereCollider::TickComponent()
{
	Super::TickComponent();
}

void SphereCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	// 만약 디버그 모드가 꺼져있다면?
	if (_showDebug == false)
	{
		// 종료합니다.
		return;
	}

	// 카메라의 위치를 받아옵니다.
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	// 콜라이더의 위치를 받아옵니다.
	// * 위치 = 주인의 위치
	Vec2 pos = GetOwner()->GetPos();

	// 카메라 기준 위치로 변경합니다.
	pos.x -= (cameraPos.x - GWinSizeX / 2);
	pos.y -= (cameraPos.y - GWinSizeY / 2);

	// 투명하게 보이기 위해 브러시를 설정합니다.
	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);

	Utils::DrawCircle(hdc, pos, _radius);

	::SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

bool SphereCollider::CheckCollision(Collider* other)
{
	// 다른 충돌체(other)의 타입별로 분기합니다.
	switch (other->GetColliderType())
	{
	// 다른 충돌체의 타입이 박스인 경우
	case ColliderType::Box:
		// 구체와 박스의 충돌 체크 결과를 반환합니다.
		return CheckCollisionSphere2Box(this, static_cast<BoxCollider*>(other));

	// 다른 충돌체의 타입이 구체인 경우
	case ColliderType::Sphere:
		// 구체와 구체의 충돌 체크 결과를 반환합니다.
		return CheckCollisionSphere2Sphere(this, static_cast<SphereCollider*>(other));
	}

	return false;
}
