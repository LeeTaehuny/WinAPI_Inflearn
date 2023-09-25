#pragma once
#include "UI.h"

class Sprite;

// 버튼의 상태들을 표현하기 위한 열거형을 선언합니다.
enum ButtonState
{
	BS_Default,		// 0 = 디폴트 상태
	BS_Hovered,		// 1 = 마우스를 올려둔 상태
	BS_Pressed,		// 2 = 마우스를 누르고 있는 상태
	BS_Clicked,		// 3 = 마우스를 클릭한 상태

	BS_MaxCount		// 4 = 마우스 상태 수
};

class Button : public UI
{
	using Super = UI;
public:
	Button();
	virtual ~Button() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	// 버튼의 크기를 설정하기 위한 함수를 정의합니다.
	void SetSize(Vec2Int size) { _size = size; }
	// 버튼의 상태에 따른 스프라이트를 반환하기 위한 함수를 정의합니다.
	Sprite* GetSprite(ButtonState state) { return _sprites[state]; }

	// 현재 사용할 스프라이트를 설정하기 위한 함수를 정의합니다.
	void SetCurrentSprite(Sprite* sprite) { _currentSprite = sprite; }
	// 상황에 맞는 스프라이트를 설정하기 위한 함수를 정의합니다.
	void SetSprite(Sprite* sprite, ButtonState state) { _sprites[state] = sprite; }
	
	// 현재 버튼의 상태를 설정하기 위한 함수를 선언합니다.
	void SetButtonState(ButtonState state);

protected:
	// UI의 스프라이트를 저장하기 위한 변수를 선언합니다.
	Sprite* _currentSprite = nullptr;
	// 스프라이트들을 저장하기 위한 배열을 선언합니다.
	Sprite* _sprites[BS_MaxCount] = {};

	// 현재 버튼의 상태를 저장하기 위한 열거형 타입의 변수를 선언합니다.
	ButtonState _state = BS_Default;

	// 누적 시간을 저장하기 위한 변수를 선언합니다.
	float _sumTime = 0.0f;

public:
	template<typename T>
	void AddOnClickDelegate(T* owner, void(T::* func)())
	{
		_onClick = [owner, func]()
		{
			(owner->*func)();
		};
	}

	// 함수 포인터 + 함수 객체
	std::function<void(void)> _onClick = nullptr;
};

