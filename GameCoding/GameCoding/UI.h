#pragma once
class UI
{
public:
	UI();
	virtual ~UI();

	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

	// 위치를 저장하고 불러오기 위한 Getter, Setter 함수를 정의합니다.
	void SetPos(Vec2 pos) { _pos = pos; }
	Vec2 GetPos() { return _pos; }

	// UI가 사각형이라고 가정하고 해당 사각형을 반환해주는 함수를 선언합니다.
	RECT GetRect();
	// UI 사각형 안에 마우스가 위치했는지 판별해주기 위한 함수를 선언합니다.
	bool IsMouseInRect();

protected:
	// UI의 위치를 저장하기 위한 변수를 선언합니다.
	Vec2 _pos = { 400, 300 };
	// UI의 크기를 저장하기 위한 변수를 선언합니다.
	Vec2Int _size = { 150, 150 };
};

