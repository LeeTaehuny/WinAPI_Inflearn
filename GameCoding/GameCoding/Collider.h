#pragma once
#include "Component.h"

class BoxCollider;
class SphereCollider;

// 여러 충돌체의 베이스가 되는 클래스입니다.
class Collider : public Component
{
public:
	Collider(ColliderType colliderType);
	virtual ~Collider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	// 충돌을 판별하기 위한 함수를 선언합니다.
	virtual bool CheckCollision(Collider* other);

	// 충돌체의 타입을 반환하기 위한 함수를 정의합니다.
	ColliderType GetColliderType() { return _colliderType; }

	// 디버그용 출력을 설정하기 위한 함수를 정의합니다.
	void SetShowDebug(bool show) { _showDebug = show; }

	// 충돌중인 물체들을 반환하기 위한 함수를 정의합니다.
	//unordered_set<Collider*>& GetCollisionMap() { return _collisionMap; }

public:
	// 생각해보면 충돌을 체크하는 과정에서 상대방의 타입에 따라 분기합니다.
	// * 즉, 굳이 각각의 함수를 만드는 것이 아닌 부모 클래스에서 경우의 수에 따른 함수를 만들어주면 편합니다.

	// * 박스 충돌체와 박스 충돌체의 충돌 여부를 확인하기 위한 함수를 정의합니다.
	static bool CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2);
	// * 구체 충돌체와 박스 충돌체의 충돌 여부를 확인하기 위한 함수를 정의합니다.
	static bool CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2);
	// * 구체 충돌체와 구체 충돌체의 충돌 여부를 확인하기 위한 함수를 정의합니다.
	static bool CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2);

protected:
	// 충돌체의 타입을 저장하기 위한 변수를 선언합니다.
	ColliderType _colliderType;
	// 디버그용 모양을 출력할지 판별하기 위한 변수를 선언합니다.
	bool _showDebug;

//private: // 빠르게 확인하기 위해 잠시만 public으로 선언
public:
	// 충돌하고 있는 충돌체의 정보들을 저장하기 위해 변수를 선언합니다.
	// * 정말 충돌한 충돌체들을 확인만 할 것이므로, set(키) 자료구조를 사용합니다.
	// * vector의 경우 충돌중인 물체들이 많아지면 순차적으로 순회를 해야하므로 효율 X
	unordered_set<Collider*> _collisionMap;

	// 오브젝트 간의 트레이스 채널(특정 오브젝트와 충돌이 가능한지 여부)을 저장하기 위한 비트 플래그 변수를 선언합니다.
	// * ex) 32비트가 아닌 8비트라고 가정 | 0 : 오브젝트 / 1 : 맵 |
	//       -> 0000 0001 : 오브젝트와만 충돌 가능한 경우의 비트 플래그
	//       -> 0000 0011 : 오브젝트와도 충돌 가능, 맵과도 충돌 가능한 경우의 비트 플래그
	uint32 _flag = 0;
};

