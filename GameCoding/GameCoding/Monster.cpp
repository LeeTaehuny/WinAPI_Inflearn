#include "pch.h"
#include "Monster.h"

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
}

void Monster::Render(HDC hdc)
{
	// 간단한 테스트를 위해 몬스터를 사각형으로 그려줍니다.
	Utils::DrawRect(hdc, _pos, 50, 50);
}
