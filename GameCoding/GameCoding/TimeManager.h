#pragma once

// 시간을 관리하는 역할의 클래스입니다.
// * 주로 시간을 체크해서 이전 프레임과 현재 프레임에서 얼마만큼의 시간이 경과되었는지를 추적해주는 등의 역할을 합니다.
class TimeManager
{
	DECLARE_SINGLE(TimeManager);

public:
	// 초기화 함수의 원형을 선언합니다.
	void Init();
	// 업데이트 함수의 원형을 선언합니다.
	void Update();

	// 외부에서 접근이 가능하도록 Getter 함수를 정의합니다.
	uint32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

private:
	uint64 _frequency = 0;
	uint64 _prevCount = 0;

	// 경과시간을 저장할 변수를 선언합니다.
	// * 이전 프레임에서 현재 시간까지 경과된 시간
	float _deltaTime = 0.0f;

private:
	// 현재 프레임 관련 정보를 저장하기위한 변수를 선언합니다.
	uint32 _frameCount = 0;
	float _frameTime = 0.0f;
	uint32 _fps = 0;
};

