#include "pch.h"
#include "TimeManager.h"

// 초기화 함수를 정의합니다.
void TimeManager::Init()
{
	/** 시간을 측정하는 방법은 여러가지가 존재합니다. */ 
	// 1. ::GetTickCount64(), ::GetTickCount64()
	//    해당 함수를 호출하면 ms의 시간이 반환되며 2번 호출하여 그 사이의 차이를 가지고 시간을 계산할 수 있습니다.
	//    but 시간의 정밀도가 떨어진다는 단점이 존재합니다.
	
	// 2. ::QueryPerformanceFrequency(), ::QueryPerformanceCounter()
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount)); // cpu 클럭
}

// 업데이트 함수를 정의합니다.
void TimeManager::Update()
{
	// 현재 값과 이전 값의 차이를 비교하기 위해 현재 값을 저장합니다.
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	// 경과된 시간을 구합니다.
	// * 경과 시간 = (현재시간 - 이전시간) / _frequency
	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);

	// 경과 시간을 구했으므로 prevCount를 현재 값으로 덮어씌웁니다.
	_prevCount = currentCount;

	// 해당 함수가 몇 번 호출되었는지 추적을 위해 _frameCount를 증가시킵니다.
	_frameCount++;
	// 경과된 시간도 누적합니다.
	_frameTime += _deltaTime;

	// 만약 경과된 누적 시간(_frameTime)이 1초를 넘어섰다면?
	if (_frameTime >= 1.0f)
	{
		// fps(frame per second) : 매 초마다 몇 번의 갱신이 일어났는가를 의미합니다.
		// * fps를 구해줍니다.
		// ** 현재 몇 초가 경과되었으며, 몇 번 함수를 호출했는지 계산해 fps에 저장합니다.
		_fps = static_cast<uint32>(_frameCount / _frameTime);

		// fps를 구해주었으므로 초기값으로 돌려줍니다.
		_frameCount = 0;
		_frameTime = 0;
	}
}
