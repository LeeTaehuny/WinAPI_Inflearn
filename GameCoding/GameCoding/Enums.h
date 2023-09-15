#pragma once

// Scene의 타입을 구분하기 위한 열거형을 정의합니다.
enum class SceneType
{
	None,		// 0
	DevScene,	// 1 = 테스트용 씬
	EditScene,  // 2 = 툴 용도로 사용할 씬
};

// 플레이어의 타입을 열거형으로 정의합니다.
enum class PlayerType
{
	CanonTank,
	MissileTank,
};

// 플레이어의 방향을 열거형으로 정의합니다.
enum class Dir
{
	Left,
	Right,
};