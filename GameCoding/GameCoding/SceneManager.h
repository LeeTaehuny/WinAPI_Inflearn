#pragma once

// 씬을 관리하는 매니저 클래스입니다.
// * 결국 모든 오브젝트들을 관리하는 클래스입니다.
class SceneManager
{
	DECLARE_SINGLE(SceneManager)

public:
	void Init();
	void Update();
	void Render(HDC hdc);

public:
	// 씬을 전환하는 함수의 원형을 선언합니다.
	void ChangeScene(SceneType sceneType);

	// 씬을 삭제하는 함수의 원형을 선언합니다.
	void Clear();

private:
	// 씬을 저장하기 위한 변수를 선언합니다.
	class Scene* _scene;
	// 씬의 타입을 저장하기 위한 변수를 선언합니다.
	SceneType _sceneType = SceneType::None;
};

