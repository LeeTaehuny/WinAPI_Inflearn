#pragma once

class Collider;

// 모든 충돌체 정보를 등록해 관리하는 클래스입니다.
class CollisionManager
{
	DECLARE_SINGLE(CollisionManager);

public:
	void Init();
	void Update();

	void AddCollider(Collider* collider);
	void RemoveCollider(Collider* collider);

private:
	// 충돌체를 저장하기 위한 벡터 컨테이너를 선언합니다.
	vector<Collider*> _colliders;
};

