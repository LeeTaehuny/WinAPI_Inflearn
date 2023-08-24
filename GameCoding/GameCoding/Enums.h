#pragma once

// Scene의 타입을 구분하기 위한 열거형을 정의합니다.
enum class SceneType
{
	None,		// 0
	DevScene,	// 1 = 테스트용 씬
	GameScene,	// 2 = 실제 게임용 씬
};