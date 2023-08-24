#pragma once
#include <windows.h>
#include <string>
using namespace std;

// 헬퍼 기능들을 관리하기 위한 클래스입니다.
class Utils
{
public:
	static void DrawText(HDC hdc, Pos pos, const wstring& str);

	static void DrawRect(HDC hdc, Pos pos, int32 w, int32 h);

	static void DrawCircle(HDC hdc, Pos pos, int32 radius);

	static void DrawLine(HDC hdc, Pos from, Pos to);
};

