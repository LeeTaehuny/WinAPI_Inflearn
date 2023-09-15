#pragma once
#include "ResourceBase.h"

class Texture;

class Sprite : public ResourceBase
{
public:
	Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy);
	virtual ~Sprite();

	// DC를 반환하기 위한 함수를 선언합니다.
	HDC		GetDC();
	// 투명화할 색상을 반환하기 위한 함수를 선언합니다.
	int32	GetTransparent();
	// 위치를 반환하기 위한 함수를 정의합니다.
	Vec2Int	GetPos() { return Vec2Int{ _x, _y }; }
	// 사이즈를 반환하기 위한 함수를 정의합니다.
	Vec2Int GetSize() { return Vec2Int{ _cx, _cy }; }

private:
	// 텍스처를 저장하기 위한 변수를 선언합니다.
	Texture* _texture = nullptr;

	// 위치를 저장하기 위한 변수를 선언합니다.
	int32 _x;
	int32 _y;

	// 사이즈를 저장하기 위한 변수를 선언합니다.
	int32 _cx;
	int32 _cy;
};

