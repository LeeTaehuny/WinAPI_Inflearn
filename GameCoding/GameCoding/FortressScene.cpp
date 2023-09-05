#include "pch.h"
#include "FortressScene.h"

#include "UIManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"

#include "Player.h"
#include "LineMesh.h"
#include "Object.h"

FortressScene::FortressScene()
{
}

FortressScene::~FortressScene()
{
}

void FortressScene::Init()
{
	// UI매니저 : 인게임 상에서 그려줘야 할 UI들을 모두 좌표를 잡아주는 역할
	// * UI매니저를 초기화합니다.
	GET_SINGLE(UIManager)->Init();

	// 플레이어 1 생성 및 초기화
	{
		// 오브젝트 매니저를 이용해 플레이어를 생성해줍니다.
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		// 생성된 플레이어의 타입을 설정합니다.
		player->SetPlayerType(PlayerType::MissileTank);
		// 플레이어의 아이디를 설정합니다.
		player->SetPlayerId(0);
		// 해당 플레이어의 차례라고 설정합니다.
		player->SetPlayerTurn(true);

		// 오브젝트 매니저에서 관리하는 오브젝트 목록에 플레이어를 추가합니다.
		GET_SINGLE(ObjectManager)->Add(player);

		// 시작 위치를 설정합니다.
		player->SetPos(Vector{ 100, 400 });
	}

	// 플레이어 2 생성 및 초기화
	{
		// 오브젝트 매니저를 이용해 플레이어를 생성해줍니다.
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		// 생성된 플레이어의 타입을 설정합니다.
		player->SetPlayerType(PlayerType::CanonTank);

		// 오브젝트 매니저에서 관리하는 오브젝트 목록에 플레이어를 추가합니다.
		GET_SINGLE(ObjectManager)->Add(player);

		// 시작 위치를 설정합니다.
		player->SetPos(Vector{ 700, 400 });
	}

}

void FortressScene::Update()
{
	// 프레임 시간을 저장합니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 복사 방식으로 오브젝트 매니저에서 관리하는 오브젝트들을 저장합니다.
	// * 복사방식으로 한 이유 : foreach 안에서 삭제가 가능하도록 하기 위함
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	// 오브젝트들을 순회하며 각각의 오브젝트를 업데이트 합니다.
	for (Object* obj : objects)
	{
		obj->Update();
	}
}

void FortressScene::Render(HDC hdc)
{
	// UI매니저를 렌더합니다.
	GET_SINGLE(UIManager)->Render(hdc);

	// 참조 방식으로 오브젝트 매니저에서 관리하는 오브젝트들을 저장합니다.
	// * 참조방식으로 한 이유 : foreach 안에서 삭제가 안 일어날 것이므로 메모리 절약을 위해
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	// 오브젝트들을 순회하며 각각의 오브젝트를 렌더합니다.
	for (Object* obj : objects)
	{
		obj->Render(hdc);
	}
}
