#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "EditScene.h"

void SceneManager::Init()
{

}

void SceneManager::Update()
{
	// 만약 현재 씬이 존재한다면?
	if (_scene)
	{
		// 씬을 업데이트 합니다.
		_scene->Update();
	}
}

void SceneManager::Render(HDC hdc)
{
	// 만약 현재 씬이 존재한다면?
	if (_scene)
	{
		// 씬을 렌더링합니다.
		_scene->Render(hdc);
	}
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	// 만약 바꾸고 싶은 씬 타입이 현재 씬 타입과 동일하다면?
	if (_sceneType == sceneType)
	{
		// 잘못된 것이므로 바로 리턴해줍니다.
		return;
	}

	Scene* newScene = nullptr;


	// 변경하고 싶은 씬 타입별로 다르게 처리합니다.
	switch (sceneType)
	{
	case SceneType::DevScene:
		// 테스트용 씬을 동적 할당합니다.
		newScene = new DevScene();
		break;

	case SceneType::EditScene:
		// 툴 전용 씬을 동적 할당합니다.
		newScene = new EditScene();
	}

	// 씬을 교체했으므로 기존 씬은 삭제합니다.
	SAFE_DELETE(_scene);

	// 기존의 씬을 새로운 씬으로 수정합니다.
	_scene = newScene;
	// 씬 타입을 변경한 씬의 타입으로 수정합니다.
	_sceneType = sceneType;

	// 새로운 씬을 초기화합니다.
	newScene->Init();
}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene);
}
