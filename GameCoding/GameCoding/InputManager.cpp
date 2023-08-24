#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hWnd)
{
	// 핸들 번호를 초기화합니다.
	_hWnd = hWnd;
	// 벡터의 사이즈를 키보드 타입의 개수로 설정하고 None으로 초기화합니다.
	_states.resize(KEY_TYPE_COUNT, KeyState::None);
}

void InputManager::Update()
{
	// ::GetAsyncKeyState() : 현재 키 값이 눌려있는지 체크하는 함수입니다.
	// * 하지만 여러번 호출 시 속도가 느려진다는 단점이 존재합니다.

	// ::GetKeyboardState() : 키보드 값 하나를 읽어오는 것이 아닌 전체 값을 읽어오는 함수입니다.
	// * 즉, 모든 상태를 저장해서 특정 키 비교를 통해 로직을 구현할 것입니다. 

	// 256개의 키들을 받아줄 배열을 생성합니다.
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};

	// 생성한 공간에 모든 키보드의 입력 값을 저장합니다.
	// * 만약 false라면 리턴합니다.
	if (::GetKeyboardState(asciiKeys) == false)
	{
		return;
	}

	// 위에서 저장한 asciiKeys를 가지고 상태를 저장합니다.
	// * ex) 이전 Update에서 누르고 있었고, 이번에도 누르고 있다면 누르고 있는 상태입니다.
	// * 이해만 하고 넘어가는 것이 좋습니다.
	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		// 키가 눌려있으면 ture
		if (asciiKeys[key] & 0x80)
		{
			KeyState& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면? PRESS
			if (state == KeyState::Press || state == KeyState::Down)
			{
				state = KeyState::Press;
			}
			// 이번에만 눌린 상황이라면? DOWN
			else
			{
				state = KeyState::Down;
			}
		}
		// 키가 눌려있지 않다면? 뗏다면?
		else
		{
			KeyState& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면? UP
			if (state == KeyState::Press || state == KeyState::Down)
			{
				state = KeyState::Up;
			}
			// 이전 프레임에도 누르지 않은 상태라면? NONE;
			else
			{
				state = KeyState::None;
			}
		}
	}

	// Mouse의 위치를 저장합니다.
	::GetCursorPos(&_mousePos);
	// 저장된 Mouse의 위치를 창 기준 위치로 변경합니다.
	::ScreenToClient(_hWnd, &_mousePos);
}
