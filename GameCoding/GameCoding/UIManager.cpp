#include "pch.h"
#include "UIManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "LineMesh.h"
#include "ResourceManager.h"

void UIManager::Init()
{	
	// 각종 테스트 설정
	_windPercent = 50;
	//_powerPercent = 50;
	_staminaPercent = 40;
	_remainTime = 7;
	_playerAngle = 0.f;
	_barrelAngle = 20.f;
}

void UIManager::Render(HDC hdc)
{
	// UI
	RenderBackground(hdc);
	RenderWind(hdc);
	RenderPower(hdc);
	RenderStamina(hdc);
	RenderTime(hdc);
	RenderAngle(hdc);
	RenderWeaponChoice(hdc);
	RenderMiniMap(hdc);
}

void UIManager::RenderBackground(HDC hdc)
{
	const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(L"UI");
	if (mesh)
		mesh->Render(hdc, Pos{ 0, 0 });
}

void UIManager::RenderWind(HDC hdc)
{
	float minY = 560.0f / 600 * GWinSizeY;
	float maxY = 575.0f / 600 * GWinSizeY;
	float avgX = 100.0f / 800 * GWinSizeX;
	float sizeX = 49.0f / 800 * GWinSizeX;

	HBRUSH brush = ::CreateSolidBrush(RGB(50, 198, 74));
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

	if (_windPercent < 0)
	{
		Rectangle(hdc
			, static_cast<int32>(avgX + sizeX * _windPercent / 100)
			, static_cast<int32>(minY)
			, static_cast<int32>(avgX)
			, static_cast<int32>(maxY));
	}
	else
	{
		Rectangle(hdc
			, static_cast<int32>(avgX)
			, static_cast<int32>(minY)
			, static_cast<int32>(avgX + sizeX * _windPercent / 100)
			, static_cast<int32>(maxY));
	}

	::SelectObject(hdc, oldBrush);
	::DeleteObject(brush);
}

void UIManager::RenderPower(HDC hdc)
{
	{
		RECT rect = {};
		rect.left = static_cast<LONG>(265.0f / 800 * GWinSizeX);
		rect.top = static_cast<LONG>(505.0f / 600 * GWinSizeY);
		rect.right = static_cast<LONG>(680.0f / 800 * GWinSizeX);
		rect.bottom = static_cast<LONG>(535.0f / 600 * GWinSizeY);
		::Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	}

	{
		RECT rect = {};
		rect.left = static_cast<LONG>(270.0f / 800 * GWinSizeX);
		rect.top = static_cast<LONG>(510.0f / 600 * GWinSizeY);
		rect.right = static_cast<LONG>(270.0f / 800 * GWinSizeX + _powerPercent * 4);
		rect.bottom = static_cast<LONG>(530.0f / 600 * GWinSizeY);

		HBRUSH Brush, oBrush;
		Brush = ::CreateSolidBrush(RGB(255, 216, 216));
		oBrush = (HBRUSH)::SelectObject(hdc, Brush);

		::Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		::SelectObject(hdc, oBrush);
		::DeleteObject(Brush);
	}
}

void UIManager::RenderStamina(HDC hdc)
{
	{
		RECT rect = {};
		rect.left = static_cast<LONG>(265.0f / 800 * GWinSizeX);
		rect.top = static_cast<LONG>(538.0f / 600 * GWinSizeY);
		rect.right = static_cast<LONG>(680.0f / 800 * GWinSizeX);
		rect.bottom = static_cast<LONG>(568.0f / 600 * GWinSizeY);
		::Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	}
	{
		RECT rect = {};
		rect.left = static_cast<long>(270.0f / 800 * GWinSizeX);
		rect.top = static_cast<long>(543.0f / 600 * GWinSizeY);

		rect.right = static_cast<long>(270.0f / 800 * GWinSizeX + _staminaPercent * 4);

		rect.bottom = static_cast<long>(563.0f / 600 * GWinSizeY);

		HBRUSH brush = ::CreateSolidBrush(RGB(250, 236, 197));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

		::Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		::SelectObject(hdc, oldBrush);
		::DeleteObject(brush);
	}
}

void UIManager::RenderTime(HDC hdc)
{
	HFONT myFont = ::CreateFont(
		30						// 높이
		, 0						// 폭 0이면 높이와 비례
		, 0						// 글자 전체 기울기
		, 0						// 기준선이 정해진 기울기
		, 0						// 폰트의 두께
		, 0						// 이탤릭
		, 0						// 밑줄
		, 0						// 취소선
		, DEFAULT_CHARSET		// 케릭터 셋
		, 0						// 정밀도
		, 0						// 정밀도
		, 0						// 정밀도
		, 0						// 정밀도
		, L"궁서체"				// 글꼴이름
	);

	HFONT oldFont = (HFONT)::SelectObject(hdc, myFont);

	WCHAR message[100];
	::wsprintf(message, L"%02d", static_cast<int32>(_remainTime));

	::TextOut(hdc, 728, 510, message, ::lstrlen(message));
	::SelectObject(hdc, oldFont);
	::DeleteObject(myFont);
}

void UIManager::RenderAngle(HDC hdc)
{
	::MoveToEx(hdc, 96, 520, nullptr);
	::Ellipse(hdc, 96 - 35, 520 - 35, 96 + 35, 520 + 35);

	::MoveToEx(hdc, 96, 520, nullptr);
	::LineTo(hdc
		, static_cast<int32>(96 + 30 * ::cos(_playerAngle * PI / 180))
		, static_cast<int32>(520 - 30 * ::sin(_playerAngle * PI / 180)));

	HPEN MyPen = ::CreatePen(PS_SOLID, 0, RGB(204, 61, 61));
	HPEN pOldPen = (HPEN)::SelectObject(hdc, MyPen);

	::MoveToEx(hdc, 96, 520, nullptr);

	::LineTo(hdc
		, static_cast<int32>(96 + 30 * ::cos(_barrelAngle * PI / 180))
		, static_cast<int32>(520 + -30 * ::sin(_barrelAngle * PI / 180)));

	::SelectObject(hdc, pOldPen);
	::DeleteObject(MyPen);
}

void UIManager::RenderWeaponChoice(HDC hdc)
{
	HBRUSH brush = ::CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

	if (_specialWeapon == false)
		::Rectangle(hdc, 20 - 5, 550 - 5, 20 + 5, 550 + 5);
	else
		::Rectangle(hdc, 170 - 5, 550 - 5, 170 + 5, 550 + 5);

	::SelectObject(hdc, oldBrush);
	::DeleteObject(brush);
}

void UIManager::RenderMiniMap(HDC hdc)
{
	float ratioX = static_cast<float>(GMinimapSizeX) / static_cast<float>(1280);
	float ratioY = static_cast<float>(GMinimapSizeY) / static_cast<float>(720);

	// 미니맵 범위
	RECT rect = { GWinSizeX - GMinimapSizeX - 10, 10, GWinSizeX - 10, 10 + GMinimapSizeY };

	// 미니맵 테두리
	::Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}