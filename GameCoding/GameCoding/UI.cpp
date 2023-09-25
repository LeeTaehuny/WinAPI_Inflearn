#include "pch.h"
#include "UI.h"
#include "InputManager.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::BeginPlay()
{
}

void UI::Tick()
{
}

void UI::Render(HDC hdc)
{
}

RECT UI::GetRect()
{
	// UI의 범위를 지정해 반환해줍니다.
	RECT rect =
	{
		_pos.x - _size.x / 2,
		_pos.y - _size.y / 2,
		_pos.x + _size.x / 2,
		_pos.y + _size.y / 2
	};

	return rect;
}

bool UI::IsMouseInRect()
{
	// 사각형(UI)과 마우스 위치의 충돌을 판별하기 위해 각각을 받아와 저장합니다.
	RECT rect = GetRect();
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

	// PtInRect() : 점이 RECT 내부에 위치하는지를 판별해주는 함수
	//::PtInRect(&rect, mousePos);

	// 직접 구현
	if (mousePos.x < rect.left)
	{
		return false;
	}	
	if (mousePos.x > rect.right)
	{
		return false;
	}	
	if (mousePos.y < rect.top)
	{
		return false;
	}	
	if (mousePos.y > rect.bottom)
	{
		return false;
	}

	return true;
}
