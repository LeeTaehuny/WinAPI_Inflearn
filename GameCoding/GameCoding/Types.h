#pragma once

using int8		= __int8;
using int16		= __int16;
using int32		= __int32;
using int64		= __int64;

using uint8		= unsigned __int8;
using uint16	= unsigned __int16;
using uint32	= unsigned __int32;
using uint64	= unsigned __int64;

// 위치정보를 저장하기 위한 구조체를 선언합니다.
struct Pos
{
	float x = 0;
	float y = 0;
};

// 오브젝트들이 가지고 있을 수 있는 스탯을 저장하기 위한 구조체를 선언합니다.
struct Stat
{
	int32 hp = 0;
	int32 maxHp = 0;
	float speed = 0;
};