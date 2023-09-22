#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Actor.h"

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{
	// TODO : 매 프레임 충돌 체크

	// 충돌체크를 하기위해 기존 저장되어있는 충돌체 벡터 컨테이너를 복사합니다. (참조)
	vector<Collider*>& colliders = _colliders;

	// 모든 충돌체들끼리 짝으로 비교하기 위해 순회합니다.
	for (int32 i = 0; i < colliders.size(); i++)
	{
		for (int32 j = i + 1; j < colliders.size(); j++)
		{
			// i번째 충돌체와 j번째 충돌체를 충돌 체크합니다.
			Collider* src = colliders[i];
			Collider* dest = colliders[j];

			if (src->CheckCollision(dest))
			{
				// 충돌 O
				
				// 만약 해당 충돌체와 충돌중인 충돌체가 아니라면? (처음 충돌한 경우)
				if (src->_collisionMap.contains(dest) == false)
				{
					// 충돌이 발생했으므로 각각의 주인에게 충돌 발생을 알려줍니다.
					src->GetOwner()->OnComponentBeginOverlap(src, dest);
					dest->GetOwner()->OnComponentBeginOverlap(dest, src);

					// 서로 충돌했으므로 충돌중인지 확인하는 배열에 서로를 추가합니다.
					src->_collisionMap.insert(dest);
					dest->_collisionMap.insert(src);
				}
			}
			else
			{
				// 충돌 X

				// 충돌은 없었지만 만약 충돌중인지 확인하는 배열에 상대방이 존재한다면?
				// * 충돌하다 충돌을 벗어난 경우
				if (src->_collisionMap.contains(dest) == true)
				{
					// 충돌이 종료되었으므로 각각의 주인에게 충돌 종료를 알려줍니다.
					src->GetOwner()->OnComponentEndOverlap(src, dest);
					dest->GetOwner()->OnComponentEndOverlap(dest, src);

					// 충돌이 끝났으므로 충돌중인지 확인하는 배열에서 서로를 제거합니다.
					src->_collisionMap.erase(dest);
					dest->_collisionMap.erase(src);
				}
			}
		}
	}
}

void CollisionManager::AddCollider(Collider* collider)
{
	_colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(Collider* collider)
{
	auto it = remove(_colliders.begin(), _colliders.end(), collider);
	_colliders.erase(it, _colliders.end());
}
