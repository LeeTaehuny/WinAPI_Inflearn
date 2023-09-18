#include "pch.h"
#include "DevScene.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Player.h"

DevScene::DevScene()
{

}

DevScene::~DevScene()
{

}

void DevScene::Init()
{
	// 씬에 필요한 텍스쳐들을 불러옵니다.
	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
	//GET_SINGLE(ResourceManager)->LoadTexture(L"Sword", L"Sprite\\Item\\Sword.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Potion", L"Sprite\\UI\\Mp.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDown", L"Sprite\\Player\\PlayerDown.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerUp", L"Sprite\\Player\\PlayerUp.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Edit", L"Sprite\\UI\\Edit.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Exit", L"Sprite\\UI\\Exit.bmp");

	// 씬에 필요한 스프라이트들을 생성합니다.
	GET_SINGLE(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 150, 0, 150, 150);

	// 배경
	{
		// 사용할 스프라이트를 가져옵니다.
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");

		// 액터를 생성합니다.
		SpriteActor* background = new SpriteActor();
		// 스프라이트를 저장합니다.
		background->SetSprite(sprite);

		// 액터의 위치를 설정합니다.
		const Vec2Int size = sprite->GetSize();
		background->SetPos(Vec2(size.x / 2, size.y / 2));
		
		// 씬에 액터를 저장합니다.
		_actors.push_back(background);
	}

	// 플레이어
	{
		// 사용할 스프라이트를 가져옵니다. (스타트를 플레이어로 가정
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Start_On");

		// 액터를 생성합니다.
		Player* player = new Player();
		// 스프라이트를 저장합니다.
		player->SetSprite(sprite);

		// 액터의 위치를 설정합니다.
		const Vec2Int size = sprite->GetSize();
		player->SetPos(Vec2(size.x / 2, size.y / 2));

		// 씬에 액터를 저장합니다.
		_actors.push_back(player);
	}

	// 유니티 방식
	//{
	//	GameObject* player = new GameObject();
	//	player->SetPos({ 500, 500 });
	//	
	//	// 부품 추가 (스프라이트)
	//	{
	//		// 스프라이트를 가져옵니다.
	//		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Start_Off");
	//
	//		// 스프라이트를 그려주기 위한 부품을 생성합니다.
	//		SpriteRenderer* sr = new SpriteRenderer();
	//		// 스프라이트를 저장합니다.
	//		sr->SetSprite(sprite);
	//
	//		// 플레이어에 부품을 추가합니다.
	//		player->AddComponent(sr);
	//	}
	//
	//	// 부품 추가 (이동)
	//	{
	//		// 이동하기 위한 부품을 생성합니다.
	//		PlayerMoveScript* mv = new PlayerMoveScript();
	//		
	//		// 부품을 추가합니다.
	//		player->AddComponent(mv);
	//	}
	//
	//	// 씬에 게임오브젝트를 저장합니다.
	//	_go = player;
	//}

	// BeginPlay() 함수는 게임 실행과 동시에 호출되는 함수입니다.
	// * 일단 테스트를 위해 여기서 호출하도록 하겠습니다.
	for (Actor* actor : _actors)
	{
		actor->BeginPlay();
	}
}

void DevScene::Update()
{
	// Update() 함수가 실행되는 간격은 환경(성능)에 따라달라집니다.
	// * 즉, 모든 컴퓨터에서 동일한 속도로 이동시키기 위해 이전 프레임에서 현재 프레임까지의 경과시간을 이용합니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 액터를 업데이트 합니다.
	for (Actor* actor : _actors)
	{
		actor->Tick();
	}
}

void DevScene::Render(HDC hdc)
{
	// 액터를 렌더합니다.
	for (Actor* actor : _actors)
	{
		actor->Render(hdc);
	}
}
