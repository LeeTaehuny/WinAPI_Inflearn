#pragma once

// Scene의 타입을 구분하기 위한 열거형을 정의합니다.
enum class SceneType
{
	None,		// 0
	DevScene,	// 1 = 테스트용 씬
	EditScene,  // 2 = 툴 용도로 사용할 씬
};

// 렌더링할 순서를 구분하기 위한 열거형을 정의합니다.
enum LAYER_TYPE
{
	// 위에서부터 먼저 렌더링됩니다.
	LAYER_BACKGROUND,	// 0 = 배경 
	LAYER_OBJECT,		// 1 = 오브젝트
	LAYER_UI,			// 2 = UI

	LAYER_MAXCOUNT,		// 레이어 숫자 3
}; 