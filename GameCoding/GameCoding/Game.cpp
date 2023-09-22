#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

// 생성자 함수를 정의합니다.
Game::Game()
{
	// 예를들어 동적할당을 생성만하고 해제하지 않은 경우라면?
	// * 출력창에 코드 라인까지 친절하게 올라오며 해제가 되지 않은 부분을 알려줍니다.
	// int* p = new int();
}

// 소멸자 함수를 정의합니다.
Game::~Game()
{
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ResourceManager)->Clear();
	// 마지막에 넣어야 의미가 있지만.. 일단은 여기 넣어봅니다.
	_CrtDumpMemoryLeaks();
}

// 초기화 함수를 정의합니다.
void Game::Init(HWND hWnd)
{
	// 전달받은 윈도우 핸들 번호를 저장합니다.
	_hWnd = hWnd;

	// 핸들 번호에 맞는 디바이스 컨텍스트를 저장합니다.
	_hdc = ::GetDC(hWnd);

	// 윈도우의 범위를 얻어와 _rect에 저장합니다.
	// * GetClientRect() : 윈도우의 크기를 가져와 RECT 구조체에 저장하는 함수입니다.
	::GetClientRect(hWnd, &_rect);

	// 기존에 사용하던 _hdc와 호환되는 디바이스 컨텍스트를 생성해 _hdcBack 변수에 저장합니다.
	// * CreateCompatibleDC() : hdc와 호환되는 dc를 생성해주는 함수입니다.
	_hdcBack = ::CreateCompatibleDC(_hdc);

	// 기존에 사용했던 _hdc와 호환되는 비트맵을 생성해 _bmpBack 변수에 저장합니다.
	// * CreateCompatibleBitmap : hdc와 호환되는 비트맵을 생성해주는 함수입니다.
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);

	// DC와 BMP를 연결하고 이전에 사용했던 비트맵을 백업(저장)합니다.
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);

	// 기존에 사용했던 비트맵을 삭제합니다.
	::DeleteObject(prev);

	// ResourceManager의 객체를 초기화합니다.
	GET_SINGLE(ResourceManager)->Init(_hWnd, fs::path(L"C:\\Study\\git\\WinAPI_Inflearn\\GameCoding\\Resources\\"));


	// TimeManager의 객체를 초기화합니다.
	GET_SINGLE(TimeManager)->Init();
	
	// InputManager의 객체를 초기화합니다.
	GET_SINGLE(InputManager)->Init(hWnd);

	// SceneManager의 객체를 초기화합니다.
	GET_SINGLE(SceneManager)->Init();
	// Default 씬을 설정합니다.
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::DevScene);


}

// 업데이트 함수를 정의합니다.
void Game::Update()
{
	// Game::Update()는 매 번 무한루프에서 호출됩니다.
	
	// TimeManager를 업데이트 합니다.
	// * 즉, TimeManager의 update를 호출해 fps 계산을 가능하도록 합니다. (현재 시간 계산)
	GET_SINGLE(TimeManager)->Update();

	// InputManager를 업데이트 합니다.
	// * 즉, 매 프레임마다 현재 키보드의 상태와 마우스의 상태를 저장합니다.
	GET_SINGLE(InputManager)->Update();

	// SceneManager를 업데이트 합니다.
	GET_SINGLE(SceneManager)->Update();
}

// 렌더링(그리기) 함수를 정의합니다.
void Game::Render()
{
	// 화면에 fps와 경과 시간을 출력하기 위해 TimeManager에서 관련 값을 받아옵니다.
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 예시) 타이머 출력하기 (프레임 관리)
	{
		// * 문자열을 출력하는 2번째 방법
		// * format() 함수를 통해 문자열을 미리 선언합니다.
		// ** {0}, {1}번째 들어오는 값을 뒤에서 호출하는 방식으로 작동합니다.
		wstring str = std::format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(_hdcBack, 650, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	// 예시) 마우스 위치 출력하기
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	
		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}
	
	// SceneManager를 화면에 그려줍니다.
	GET_SINGLE(SceneManager)->Render(_hdcBack);

	// Double Buffering
	// * 기존의 방식은 매 프레임마다 그림을 그리고 지우는 과정을 반복합니다.
	// * 즉, 너무 빠르게 그리고 삭제되기를 반복하기 때문에 그림이 그려지는 순간 or 지워진 순간을 볼 수도 있습니다. 
	//  (깜빡거림의 원인)
	// ** 이를 해결하기 위해 그림이 그려지는 공간을 2개로 나눠 뒤에서 그림이 전부 완성되면 앞에 고속 복사하고,
	//    복사한 원본을 지우는 과정을 반복하여 완성된 상태만 출력이 되도록 하는 방식을 더블 버퍼링이라고 합니다.
	
	// * 기존에 출력하던 DC를 전부 새로 만든 _hdcBack으로 변경합니다.
	// * 여기까지 오면 이미 새로 만든 _hdcBack에 모든 그림이 그려진 상태입니다.
	// ** _hdcBack에 그려진 것을 통으로 복사해 화면에 그려주면 됩니다.

	// _hdcBack에 그려진 내용을 _hdc로 고속 복사합니다.
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);
	// 복사한 원본인 _hdcBack를 리셋합니다.
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
