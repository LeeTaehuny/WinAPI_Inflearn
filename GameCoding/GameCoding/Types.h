#pragma once
#include <cmath>

using int8		= __int8;
using int16		= __int16;
using int32		= __int32;
using int64		= __int64;

using uint8		= unsigned __int8;
using uint16	= unsigned __int16;
using uint32	= unsigned __int32;
using uint64	= unsigned __int64;

// 벡터 정보를 저장하기 위한 구조체를 선언합니다.
struct Vector
{
	// 생성자를 선언합니다.
	Vector() { }
	Vector(float x, float y) : x(x), y(y) { }

	/** 벡터의 기능들을 구현해줍니다. */

	// 다른 벡터와의 덧셈을 위한 연산자 오버로딩
	Vector operator+(const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;

		return ret;
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}

	// 다른 벡터와의 뺄셈을 위한 연산자 오버로딩
	Vector operator-(const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;

		return ret;
	}

	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}

	// 특정 값과 곱셈을 위한 연산자 오버로딩
	Vector operator*(float value)
	{
		Vector ret;
		ret.x = x * value;
		ret.y = y * value;

		return ret;
	}

	void operator*=(float value)
	{
		x *= value;
		y *= value;
	}

	/************************************************************************/
	// 벡터의 크기(Length)를 구하는 함수를 정의합니다.

	// 루트 내부의 제곱 연산을 수행하는 함수입니다.
	// * 루트를 씌우는 연산이 복잡합니다. (비용이 많이 듬)
	// * 즉, 가장 가까운 몬스터를 찾는 등 루트 없이 구현되는 것들에는 제곱만 사용하기 위해 따로 함수를 빼준 것입니다.
	float LengthSquared()
	{
		return x * x + y * y;
	}

	// 내부 제곱 연산이 구현되어있으므로, 그것을 이용해 루트를 씌워 반환하는 함수입니다.
	float Length()
	{
		return ::sqrt(LengthSquared());
	}
	/************************************************************************/
	// 정규화 (크기가 1인 벡터로 만들어 반환) 함수를 정의합니다.
	// * (x, y)가 있을 때 (x / x의 길이, y / y의 길이)로 방향 벡터를 만들 수 있습니다.
	void Normalize()
	{
		float length = Length();

		// 길이가 0인 경우에는 방향벡터를 구할 수 없습니다. (예외처리)
		if (length < 0.00000000001f)
		{
			return;
		}

		x /= length;
		y /= length;
	}
	/************************************************************************/

	// 값을 저장할 변수를 선언합니다.
	float x = 0;
	float y = 0;
};

// 위치정보를 저장하기 위한 구조체를 선언합니다.
// * 벡터와 Pos는 결과적으로 저장하는 구조가 동일합니다.
// * 이제부터는 Pos를 사용하지 않고 벡터만 사용하도록 합니다.
//struct Pos
//{
//	float x = 0;
//	float y = 0;
//};

// 기존 Pos대신 Vector를 사용하겠다고 처리합니다.
// * 기존 Pos : 위치만 저장하는 벡터(위치벡터)로 사용한다고 생각하기. (x, y만 저장하기 위해 사용하는 것)
using Pos = Vector;


// 오브젝트들이 가지고 있을 수 있는 스탯을 저장하기 위한 구조체를 선언합니다.
struct Stat
{
	int32 hp = 0;
	int32 maxHp = 0;
	float speed = 0;
};