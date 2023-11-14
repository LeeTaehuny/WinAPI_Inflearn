#include "pch.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "ACtor.h"

Collider::Collider(ColliderType colliderType) : _colliderType(colliderType)
{

}

Collider::~Collider()
{
}

void Collider::BeginPlay()
{
}

void Collider::TickComponent()
{
}

void Collider::Render(HDC hdc)
{
}

bool Collider::CheckCollision(Collider* other)
{
	return false;
}

bool Collider::CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2)
{
	// b1충돌체와 b2충돌체의 영역을 받아옵니다.
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	// 충돌 영역을 저장하기 위한 RECT를 선언합니다.
	RECT intersect = {};

	// IntersectRect() : 충돌 결과를 boolean 값으로 반환 및 충돌 영역을 아웃 파라미터로 전달하는 함수 
	return ::IntersectRect(&intersect, &r1, &r2);
}

bool Collider::CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2)
{
	return false;
}

bool Collider::CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2)
{
	// s1 충돌체의 위치와 반지름을 받아옵니다.
	Vec2 p1 = s1->GetOwner()->GetPos();
	float r1 = s1->GetRadius();

	// s2 충돌체의 위치와 반지름을 받아옵니다.
	Vec2 p2 = s2->GetOwner()->GetPos();
	float r2 = s2->GetRadius();

	// s2에서 s1으로 가는 방향 벡터를 구해 길이를 구해줍니다.
	// * 길이는 결국 스칼라값이므로 p2 - p1과 p1 - p2는 동일합니다.
	Vec2 dir = p1 - p2;
	float dist = dir.Length();

	// 위에서 구한 길이와 두 충돌체의 반지름과 비교합니다.
	// * dist <= r1 + r2 : 충돌 O
	// * dist > r1 + r2	 : 충돌 X
	return dist <= r1 + r2;
}
