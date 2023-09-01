#include "pch.h"
#include "GameScene.h"

#include "Player.h"
#include "Monster.h"
#include "Missile.h"

#include "ObjectManager.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::Init()
{
	// 플레이어 (당분간 사용 X)
	//{
	//	// 플레이어를 생성합니다.
	//	Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
	//
	//	// 플레이어의 위치를 초기화합니다.
	//	player->SetPos(Pos{ 400, 400 });
	//
	//	// 플레이어를 오브젝트 목록에 추가합니다.
	//	GET_SINGLE(ObjectManager)->Add(player);
	//}

	// 몬스터
	{
		// 몬스터를 생성합니다.
		Monster* monster = GET_SINGLE(ObjectManager)->CreateObject<Monster>();

		// 몬스터의 위치를 초기화합니다.
		//monster->SetPos(Pos{static_cast<float>(i + 1) * 100, 100 });
		monster->SetPos(Pos{ 400.0f, 400.0f});

		// 몬스터를 오브젝트 목록에 추가합니다.
		GET_SINGLE(ObjectManager)->Add(monster);
	}

}

void GameScene::Update()
{
	// 오브젝트 매니저에 저장된 오브젝트 벡터 컨테이너를 가져옵니다.
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();

	// 각각의 오브젝트를 순회하며 Update 해줍니다.
	// * foreach로 순회할 때의 주의사항 : 도중 삽입 삭제에 조심해야 합니다.
	// * 지금은 objects를 &으로 받아오기 때문에 원본에 접근하게 되는데, 이 때 원본을 순회하는 중 원본에 요소가 추가되므로 에러가 발생합니다.
	// * 즉, 현재 에러가 나는 이유는 각각의 오브젝트를 순회 중에 Player에서 objects 벡터 컨테이너에 오브젝트를 추가하기 때문입니다.
	// ** 해결방법 1 : objects를 &가 아닌 복사 방식으로 가져오기
	//				  -> but 위 방식대로 한다면 원본이 삭제된 경우 순회 중 삭제된 객체를 접근하게 되므로 문제가 발생합니다. (쌩 포인터의 한계)
	for (Object* obj : objects)
	{
		obj->Update();
	}
}

void GameScene::Render(HDC hdc)
{
	// 오브젝트 매니저에 저장된 오브젝트 벡터 컨테이너를 가져옵니다.
	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();

	// 각각의 오브젝트를 순회하며 Render 해줍니다.
	for (Object* obj : objects)
	{
		obj->Render(hdc);
	}
}
