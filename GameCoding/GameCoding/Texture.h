#pragma once
#include "ResourceBase.h"

class Texture : public ResourceBase
{
public:
	Texture();
	virtual ~Texture();

public:
	// 텍스쳐를 불러오기 위한 함수를 선언합니다.
	Texture*	LoadBmp(HWND hwnd, const wstring& path);
	// 디바이스 컨텍스트를 불러오기 위한 함수를 선언합니다.
	HDC			GetDC();

	// 사이즈를 설정하기 위한 함수를 정의합니다.
	void		SetSize(Vec2Int size) { _size = size; }
	// 사이즈를 불러오기 위한 함수를 정의합니다.
	Vec2Int		GetSize() { return _size; }
	
	// 투명처리할 색상을 설정하기 위한 함수를 정의합니다.
	void		SetTransparent(uint32 transparent) { _transparent = transparent; }
	// 투명처리할 색상을 불러오기 위한 함수를 정의합니다.
	uint32		GetTransparent() { return _transparent; }

private:
	// 디바이스 컨텍스트를 저장하기 위한 변수를 선언합니다.
	HDC			_hdc = {};
	// 비트맵을 저장하기 위한 변수를 선언합니다.
	HBITMAP		_bitmap = {};
	// 비트맵의 사이즈를 저장하기 위한 변수를 선언합니다.
	Vec2Int		_size = {};
	// 투명처리할 색상을 저장하기 위한 변수를 선언합니다.
	uint32		_transparent = RGB(255, 0, 255);
};

