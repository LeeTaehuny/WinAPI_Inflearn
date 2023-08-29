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

	/***********************************************************************/
	// 유도탄
	// * x좌표와 y좌표를 기존에는 직접 계산하는 방식으로 해당 좌표로 날라가게 만들었음
	// * 이제는 벡터를 이용해 관리할 것

	// 만약 아직 타겟이 존재하지 않는다면?
	if (_target == nullptr)
	{
		// 0.2초가 지나기 전이면 기존 미사일 발사 방식을 유지합니다.
		_pos.x += _stat.speed * cos(_angle) * deltaTime;
		_pos.y += _stat.speed * -sin(_angle) * deltaTime;

		// 매 프레임마다 시간을 누적합니다.
		_sumTime += deltaTime;
		// 만약 누적 시간이 0.2초보다 커진다면?
		if (_sumTime >= 0.2f)
		{
			// 오브젝트 매니저를 통해 오브젝트들의 목록을 받아옵니다.
			// * 추가 삭제가 없을 것이므로 복사가 아닌 참조값으로 전달 받아도 상관 없습니다. (&)
			const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
			// 오브젝트 매니저를 순회하다 처음 접근되는 몬스터를 타겟으로 설정합니다.
			for (Object* object : objects)
			{
				// 만약 해당 요소가 몬스터 타입이라면?
				if (object->GetObjectType() == ObjectType::Monster)
				{
					// 타겟으로 설정합니다.
					_target = object;
					// 반복문을 종료합니다.
					break;
				}
			}
		}
	}
	// 타겟이 존재한다면?
	else
	{
		// 목적지까지의 벡터(거리 + 방향)를 구해줍니다.
		// * 목적지 벡터 - 출발지 벡터
		Vector dir = _target->GetPos() - GetPos();

		// 실제 미사일의 이동속도(거리)는 다음과 같습니다.
		// -> _stat.speed * deltaTime;
		// -> 즉, 프레임마다 위의 계산 결과만큼의 거리를 이동할 것이지 dir이 가지고 있는 거리는 필요가 없습니다.
		// -> 정규화를 시켜 방향벡터를 구해줍니다.
		dir.Normalize();

		// 실제로 목적지까지 프레임마다 거리만큼 이동시켜줍니다.
		// -> 실제 이동할 위치 = 방향 벡터 * 프레임별 이동 거리
		Vector moveDir = dir * _stat.speed * deltaTime;
		_pos += moveDir;
	}

	// 구조상의 문제
	// * 미사일이 몬스터를 타겟으로 들고 있는 상황에서 몬스터가 삭제된다면?
	// * 몬스터가 삭제되는 동시에 메모리 상에 위치 정보까지 싹 다 날라가게 됩니다.
	// * 즉, 미사일은 타겟을 향해 날라가지만 타겟의 위치가 없으므로(쓰레기값) 에러가 발생하게 됩니다.
	// * 그나마 GetPos()처럼 쓰레기 값을 가져오기만 하는 경우에는 터지지는 않는데..
	// * Setter()를 통해 값을 세팅하게 되는 순간 운이 나쁘게 그 자리에 다른 객체가 해당 공간을 차지하고..
	// * 그 자리에 값을 넣게 되면 메모리 오염이 발생합니다.
	// ** 크래시가 날 수도 있고... 그냥 오동작할 수도 있습니다.
	// ** shared_ptr을 사용해야 하는 문제
	/***********************************************************************/

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
		// const float dx = p1.x - p2.x;
		// const float dy = p1.y - p2.y;
		// * 벡터로 수정
		Vector dir = p2 - p1;

		// 거리를 저장합니다. (거리 = 루트(dx^2 + dy^2))
		// float dist = sqrt(dx * dx + dy * dy);
		// * 벡터로 수정
		float dist = dir.Length();

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
