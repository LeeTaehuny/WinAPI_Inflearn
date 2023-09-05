#include "pch.h"
#include "MenuScene.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "LineMesh.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Init()
{
}

void MenuScene::Update()
{
	// 'E' 키가 눌렸다면?
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
	{
		// FortressScene으로 전환
		GET_SINGLE(SceneManager)->ChangeScene(SceneType::FortressScene);
	}
}

void MenuScene::Render(HDC hdc)
{
	// 메뉴 리소스를 메시에 저장합니다.
	const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(L"Menu");

	// 만약 해당 메시가 존재한다면?
	if (mesh)
	{
		// 메시를 렌더합니다.
		mesh->Render(hdc, Pos{ 0, 0 });
	}


}
