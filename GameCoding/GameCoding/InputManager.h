#pragma once

// 입력받은 키를 열거형으로 선언합니다.
// * 기본적으로 VK 시리즈가 존재하지만, 가독성이 떨어지므로 다시 매핑을 진행합니다.
enum class KeyType
{
	// 마우스의 좌클릭, 우클릭을 매핑합니다.
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	// 키보드의 방향키를 매핑합니다.
	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,

	// 키보드의 스페이스바를 매핑합니다.
	SpaceBar = VK_SPACE,

	// 키보드의 자판을 매핑합니다.
	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',

	Q = 'Q',
	E = 'E',
};

// 키의 상태를 열거형으로 선언합니다.
enum class KeyState
{
	None,	// 입력이 없는 상태
	Press,  // 지속적으로 누르고 있는 상태
	Down,   // 한 번 눌렀을 때의 상태
	Up,     // 누르다 뗐을 때의 상태

	End,    // 키의 상태가 총 몇 개인지 체크하기 위한 변수입니다.
};

// 키보드 타입과 키의 상태 개수를 관리하기 위해 열거형으로 상수를 선언합니다.
enum
{
	// KEY_TYPE_COUNT = 256
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	// KEY_STATE_COUNT = 4
	KEY_STATE_COUNT = static_cast<int32>(KeyState::End),
};

class InputManager
{
	DECLARE_SINGLE(InputManager);

public:
	void Init(HWND hWnd);
	void Update();

	// 누르고 있는 상태에 호출되는 함수를 정의합니다.
	// * 저장되어 있는 타입이 PRESS 타입인지 확인하여 반환해주는 함수입니다.
	bool GetButton(KeyType key) { return GetState(key) == KeyState::Press; }

	// 맨 처음 누른 상태에 호출되는 함수를 정의합니다.
	// * 저장되어 있는 타입이 DOWN 타입인지 확인하여 반환해주는 함수입니다.
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }

	// 맨 처음 누르다 뗀 상태에 호출되는 함수를 정의합니다.
	// * 저장되어 있는 타입이 UP 타입인지 확인하여 반환해주는 함수입니다.
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	// 마우스의 위치를 반환하는 Getter 함수를 정의합니다.
	POINT GetMousePos() { return _mousePos; }

private:
	// 입력한 키의 상태를 반환하는 Getter 함수를 정의합니다.
	KeyState GetState(KeyType key) { return _states[static_cast<uint64> (key)]; }

private:
	// 핸들 번호를 저장하기 위한 변수를 선언합니다.
	HWND _hWnd = 0;

	// 키보드에서 입력받은 값들을 저장하기 위한 벡터 컨테이너를 선언합니다.
	// * 입력받은 값들의 상태를 저장하는 벡터 컨테이너입니다.
	vector<KeyState> _states;

	// 마우스의 상태를 저장하기 위한 변수를 선언합니다.
	// * POINT : x, y로 이루어져 있는 구조체입니다.
	POINT _mousePos = {};
};

