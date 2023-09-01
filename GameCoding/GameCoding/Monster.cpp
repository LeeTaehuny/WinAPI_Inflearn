#include "pch.h"
#include "Monster.h"

#include "InputManager.h"

Monster::Monster() : Object(ObjectType::Monster)
{
}

Monster::~Monster()
{
}

void Monster::Init()
{
	// TODO : Data
	
	// 몬스터의 기본 스텟을 하드코딩합니다. (나중에는 데이터 시트 사용해야 함)
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 10;
}

void Monster::Update()
{
	// start->end 벡터를 만들어줍니다.
	Vector v1 = _end - _start;

	// v2의 목적지인 mousePos를 구해줍니다.
	// * Vector 업데이트 (POINT 생성자 추가)
	Vector _mousePos = GET_SINGLE(InputManager)->GetMousePos();

	// start->mousePos 벡터를 만들어줍니다.
	Vector v2 = _mousePos - _start;
	
	// v1 벡터를 정규화(방향벡터로 만들기)합니다.
	v1.Normalize();
	// 두 벡터의 내적 결과를 저장합니다.
	float dot = v1.Dot(v2);
	// Dot는 크기를 가지고있으므로, v1과 곱해 방향성도 가지게 만들어줍니다.
	// * 실제 움직여야 하는 위치는 시작지점(start)입니다. 시작지점과 결과 벡터를 더해줍니다. (목표 위치)
	Vector pos = _start + v1 * dot;

	// 범위를 지정해줍니다.
	if (dot < 0 || dot >(_end - _start).Length())
	{
		return;
	}

	// 몬스터의 위치를 위에서 얻은 결과 위치로 이동시켜줍니다.
	_pos = pos;
}

void Monster::Render(HDC hdc)
{
	// 간단한 테스트를 위해 몬스터를 사각형으로 그려줍니다.
	Utils::DrawCircle(hdc, _pos, 50);

	// 경계선을 그려주기 위해 펜을 등록합니다.
	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);
	{
		// 로밍할 수 있는 범위를 그려줍니다.
		Utils::DrawLine(hdc, _start, _end);
	}
	// 사용한 펜을 삭제합니다.
	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}
