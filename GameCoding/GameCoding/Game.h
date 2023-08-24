#pragma once

class Game
{
public:
	// 생성자와 소멸자 함수의 원형을 선언합니다.
	Game();
	~Game();

public:
	// 초기화 함수의 원형을 선언합니다.
	void Init(HWND hWnd);
	// 업데이트 함수의 원형을 선언합니다.
	void Update();
	// 렌더링 함수의 원형을 선언합니다.
	void Render();

private:
	// 윈도우 핸들 번호를 저장할 변수를 선언합니다.
	// * = {} : 기본적으로 경고를 막기위해 초기화 해준 것을 의미합니다.
	HWND _hWnd = {};
	// 윈도우 디바이스 컨텍스트를 저장할 변수를 선언합니다.
	HDC _hdc = {};

private:
	// 더블 버퍼링 관련 기능을 추가합니다.
	// * 현재 그리는 영역을 저장하기 위한 변수를 선언합니다.
	RECT _rect;
	// * 두번째 hdc를 추가합니다. (그림을 그리는 용도와 화면을 출력하는 용도 구분을 위함)
	HDC _hdcBack = {};
	// * 비트맵을 저장하기 위한 변수를 선언합니다.
	HBITMAP _bmpBack = {};
};

