#include "pch.h"
#include "Bullet.h"
#include "FortressScene.h"

#include "TimeManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "UIManager.h"

Bullet::Bullet() : Object(ObjectType::Projectile)
{

}

Bullet::~Bullet()
{

}

void Bullet::Init()
{
	_radius = 20.0f;
}

void Bullet::Update()
{
	// 프레임 시간을 저장합니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 바람을 생성합니다.
	float windPercent = GET_SINGLE(UIManager)->GetWindPercent();
	// 이동 속도에 바람의 세기를 적용시켜줍니다.
	_speed.x += 10 * deltaTime * windPercent;

	// 중력을 생성합니다.
	Vector gravity{ 0, 1000 };
	// 이동 속도에서 중력만큼을 더해니다.
	_speed += gravity * deltaTime;

	// 총알을 이동시켜줍니다.
	_pos += _speed * deltaTime;

	// 오브젝트 목록을 받아옵니다.
	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
	// 오브젝트 목록을 순회합니다.
	for (Object* obj : objects)
	{
		// 만약 오브젝트의 타입이 플레이어가 아니라면?
		if (obj->GetObjectType() != ObjectType::Player)
		{
			// 건너뜁니다.
			continue;
		}

		// 만약 주체가 해당 오브젝트라면?
		if (obj == _owner)
		{
			// 건너뜁니다.
			continue;
		}

		// 총알과 플레이어간의 거리를 구해줍니다.
		Vector dir = _pos - obj->GetPos();
		// 만약 거리가 둘의 반지름 합보다 작다면?
		if (dir.Length() < _radius + obj->GetRadius())
		{
			// 씬을 불러와 저장합니다.
			// * FortressScene인 경우만 체크하도록 dynamic_cast를 사용합니다.
			FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

			// 만약 씬이 존재한다면?
			if (scene)
			{
				// 턴을 변경해줍니다.
				scene->ChangePlayerTurn();
			}

			// TODO : 데미지 계산

			// 충돌한 것이므로 총알을 삭제합니다.
			GET_SINGLE(ObjectManager)->Remove(this);
			// 종료합니다.
			return;
		}
	}

	// 만약 총알의 y 좌표가 윈도우 세로 크기의 1.5배보다 커지거나 작아진다면?
	if (_pos.y > GWinSizeY * 1.5f || _pos.y < -GWinSizeY * 1.5f)
	{
		// 씬을 불러와 저장합니다.
		// * FortressScene인 경우만 체크하도록 dynamic_cast를 사용합니다.
		FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

		// 만약 씬이 존재한다면?
		if (scene)
		{
			// 턴을 변경해줍니다.
			scene->ChangePlayerTurn();
		}
		 
		// 총알을 삭제 시켜줍니다.
		GET_SINGLE(ObjectManager)->Remove(this);
		// 업데이트를 종료합니다.
		return;
	}
}

void Bullet::Render(HDC hdc)
{
	// 테스트로 총알을 간단하게 그려줍니다.
	Utils::DrawCircle(hdc, _pos, static_cast<int>(_radius));
}
