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
	// b1 충돌체의 위치와 크기 정보를 받아옵니다.
	Vec2 p1 = b1->GetOwner()->GetPos();
	Vec2 s1 = b1->GetSize();

	// b2 충돌체의 위치와 크기 정보를 받아옵니다.
	Vec2 p2 = b2->GetOwner()->GetPos();
	Vec2 s2 = b2->GetSize();

	// b1 충돌체의 영역(x, y좌표 범위)을 구해줍니다.
	float minX_1 = p1.x - s1.x / 2;
	float maxX_1 = p1.x + s1.x / 2;
	float minY_1 = p1.y - s1.y / 2;
	float maxY_1 = p1.y + s1.y / 2;

	// b2 충돌체의 영역(x, y좌표 범위)을 구해줍니다.
	float minX_2 = p2.x - s2.x / 2;
	float maxX_2 = p2.x + s2.x / 2;
	float minY_2 = p2.y - s2.y / 2;
	float maxY_2 = p2.y + s2.y / 2;

	// 충돌이 일어날 수 없는 경우들을 제외합니다.
	{
		// b2의 오른쪽 X 좌표가 b1의 왼쪽 X 좌표보다 작은 경우
		if (maxX_2 < minX_1)
		{
			return false;
		}
		// b1의 오른쪽 X 좌표가 b2의 왼쪽 X 좌표보다 작은 경우
		if (maxX_1 < minX_2)
		{
			return false;
		}

		// b2의 위쪽 Y 좌표가 b1의 아래쪽 Y 좌표보다 작은 경우
		if (maxY_2 < minY_1)
		{
			return false;
		}
		// b1의 위쪽 Y 좌표가 b2의 아래쪽 Y 좌표보다 작은 경우
		if (maxY_1 < minY_2)
		{
			return false;
		}
	}

	// 전부 아닌 경우라면?
	return true;
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
