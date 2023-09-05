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

	// 몬스터의 위치와 바라보는 위치를 초기화해줍니다.
	_pos = Vector{ 400, 300 };
	_lookPos = Vector{ 700, 70 };

	// 방향벡터를 만들어줍니다.
	_lookDir = _lookPos - _pos;
	_lookDir.Normalize();
}

void Monster::Update()
{
	
}

void Monster::Render(HDC hdc)
{
	// 몬스터를 그려줍니다.
	Utils::DrawCircle(hdc, _pos, 100);

	// 경계선을 그려주기 위해 펜을 등록합니다.
	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);
	{
		// 몬스터가 바라보고 있는 위치(방향)을 그려줍니다.
		Utils::DrawLine(hdc, _pos, _lookPos);
	}
	// 사용한 펜을 삭제합니다.
	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);

	// 마우스 위치를 플레이어의 위치라고 가정하고 몬스터의 뒤(특정 각도)에서 공격하는지를 체크할 것입니다.

	// 마우스의 좌표를 저장합니다.
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();
	// 몬스터의 위치에서 마우스의 위치까지의 벡터를 구해줍니다.
	Vector monsterToMouseDir = mousePos - _pos;
	// 해당 벡터를 방향 벡터로 만들어줍니다.
	monsterToMouseDir.Normalize();

	// 몬스터가 바라보는 방향과 몬스터에서 플레이어로 항햐는 방향 벡터를 구했습니다.
	// * 몬스터가 바라보는 방향(v1)과 플레이어로 향하는 방향(v2)의 각도를 구해줍니다.

	// 방향을 구하는 방법
	// * v1과 v2를 내적을 하면 둘 다 방향벡터이므로 크기가 1이고, 결국 cos(각도)만 나오게 됩니다.
	// * 즉, 내적의 결과 값을 arccos에 넣어주면 해당 각도가 나오게 됩니다.
	float dot = _lookDir.Dot(monsterToMouseDir);
	float radian = ::acos(dot);

	// 각도는 현재 호도입니다. 우리가 사용하는 각도로 표현해줍니다.
	float angle = radian * 180 / 3.14f;

	// arccos 자체가 0 ~ 180까지만 나오도록 되어있기 때문에 0 ~ 180의 값만 나오게 됩니다.
	// * 0 ~ 360으로 해주기 위한 여러 방법들이 존재합니다.

	// 1. 각도 보정 - 하드코딩 : 몬스터의 각도가 틀어지는 경우 문제 발생
	//if (monsterToMouseDir.x < 0)
	//{
	//	angle = 360 - angle;
	//}

	// 2. 시계방향, 반시계방향 이용 - 외적
	float cross = _lookDir.Cross(monsterToMouseDir);
	// 결과값이 0보다 작다면? - 반대 방향으로 이동하는 것
	if (cross < 0)
	{
		angle = 360 - angle;
	}
	
	// 로그를 출력해 각도를 확인해봅니다.
	wstring str = std::format(L"Angle : {0}", angle);
	Utils::DrawTextW(hdc, { 100	,100 }, str);
}
