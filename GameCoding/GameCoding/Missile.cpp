#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"
#include "ObjectManager.h"

Missile::Missile() : Object(ObjectType::Projectile)
{
}

Missile::~Missile()
{
}

void Missile::Init()
{
	// TODO : Data
	
	// 테스트를 위해 하드코딩 합니다.
	// * 스탯 정보
	_stat.hp = 1;
	_stat.maxHp = 1;
	_stat.speed = 600;
}

void Missile::Update()
{
	// 수학적인 개념을 공부하지 않은 상태이므로, 오직 위 방향으로 이동하도록 설정합니다.
	
	// 프레임간 시간 정보를 저장하기 위한 변수를 선언합니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 매 프레임마다 위로 speed만큼 이동해야 합니다.
	_pos.y -= deltaTime * _stat.speed;


	// TODO : 충돌
	// * 오브젝트 매니저에 저장된 오브젝트 벡터 컨테이너를 가져옵니다. (복사 방식)
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	// 각각의 오브젝트를 순회하며 충돌을 체크합니다.
	for (Object* obj : objects)
	{
		// 자기 자신과 충돌하는 것은 말이 안되므로 예외처리 합니다.
		if (obj == this)
		{
			continue;
		}

		// 미사일은 몬스터일 경우에만 충돌이 일어날 것입니다. 예외처리 합니다.
		if (obj->GetObjectType() != ObjectType::Monster)
		{
			continue;
		}

		// 간단한 거리 공식
		// * 자신의 위치를 저장합니다.
		Pos p1 = GetPos();
		// * 다른 오브젝트의 위치를 저장합니다.
		Pos p2 = obj->GetPos();

		// 자신과 오브젝트 사이의 거리를 측정합니다.
		const float dx = p1.x - p2.x;
		const float dy = p1.y - p2.y;

		// 거리를 저장합니다. (거리 = 루트(dx^2 + dy^2))
		float dist = sqrt(dx * dx + dy * dy);

		// 만약 해당 거리가 미사일의 반지름(25)보다 작아진다면?
		if (dist < 25)
		{
			// 충돌이 일어난 것이므로 해당 객체와 미사일을 삭제합니다.
			// * 삭제해도 괜찮나 고민해보기..
			// ** 지금은 복사해서 받은 것이므로 원본에 해당 오브젝트가 삭제되어도 복사된 것들을 순회하는 과정에서는 문제 발생 X
			GET_SINGLE(ObjectManager)->Remove(obj);
			GET_SINGLE(ObjectManager)->Remove(this);
			return;
		}
	}

	// 특정 범위를 넘어서는 순간 소멸하도록 해줍니다.
	if (_pos.y < -100)
	{
		// 생각해볼 점
		// * 200보다 작아지는 순간에 ObjectManager에 들어가 자기 자신을 삭제해달라고 요청합니다.
		GET_SINGLE(ObjectManager)->Remove(this);
		// * 위 코드가 실행되면 자기 자신은 이미 소멸한 것입니다. 하지만 위 함수를 실행하고 여기로 다시 돌아오게 됩니다.
		// ** 즉, 자기 자신이 이미 유효한 객체가 아닌데 돌아와서 코드를 실행하는 것이 말이 되나?
		//	  -> 코드는 에러없이 정상 작동합니다.
		//    -> 하지만 이미 유효하지 않은 객체이므로 삭제 이후 무엇인가를(해당 객체와 연관있는 멤버 변수들을 사용.. 등) 하도록 설정하면 안됩니다.
		//      => 바로 return 처리 해줘야 합니다.
		return;
	}
}

void Missile::Render(HDC hdc)
{
	// 간단한 테스트를 위해 미사일을 원으로 그려줍니다.
	Utils::DrawCircle(hdc, _pos, 25);
}
