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
#include "Flipbook.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "UI.h"
#include "Button.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "Sound.h"
#include "SoundManager.h"

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

	GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));

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

	GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 0, 0, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileX", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 48, 0, 48, 48);

	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 150, 0, 150, 150);

	// 플레이어 애니메이션 설정
	{
		// 텍스쳐를 가져옵니다.
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		// 애니메이션을 생성합니다.
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp");
		// 애니메이션의 정보를 설정합니다.
		fb->SetInfo({ texture, L"MoveUp", {200, 200}, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown");
		fb->SetInfo({ texture, L"MoveDown", {200, 200}, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft");
		fb->SetInfo({ texture, L"MoveLeft", {200, 200}, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight");
		fb->SetInfo({ texture, L"MoveRight", {200, 200}, 0, 9, 1, 0.5f });
	}


	// 배경
	{
		// 사용할 스프라이트를 가져옵니다.
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");

		// 액터를 생성합니다.
		SpriteActor* background = new SpriteActor();
		// 스프라이트를 저장합니다.
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);

		// 액터의 위치를 설정합니다.
		const Vec2Int size = sprite->GetSize();
		background->SetPos(Vec2(size.x / 2, size.y / 2));
		
		// 씬에 액터를 저장합니다.
		AddActor(background);
	}

	// 플레이어
	{
		// 액터를 생성합니다.
		Player* player = new Player();
		player->SetPos({ 100, 100 });

		// 충돌 레이어 설정
		{
			// 콜라이더를 생성 및 크기를 조정합니다.
			BoxCollider* collider = new BoxCollider();
			collider->SetSize({ 100, 100 });

			// 콜리전 레이어 정보를 설정합니다.
			// * 오브젝트로 설정
			collider->SetCollisionLayer(CLT_OBJECT);

			// 콜리전 플래그 정보를 설정합니다.
			collider->ResetCollisionFlag();
			collider->AddCollisionFlagLayer(CLT_GROUND);
			//collider->AddCollisionFlagLayer(CLT_OBJECT);

			// 충돌체 매니저에 해당 충돌체를 저장합니다.
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			player->AddComponent(collider);
		}


		AddActor(player);
	}

	// 충돌 테스트를 위한 물체
	{
		// 테스트용 액터를 생성합니다.
		Actor* test = new Actor();
		test->SetLayer(LAYER_OBJECT);
		test->SetPos({ 200, 500 });

		// 충돌 정보 설정
		{
			// 콜라이더를 생성 및 크기를 조정합니다.
			BoxCollider* collider = new BoxCollider();
			collider->SetSize({ 10000, 100 });

			// 콜리전 레이어 정보를 설정합니다.
			// * 오브젝트로 설정
			collider->SetCollisionLayer(CLT_GROUND);

			// 충돌체 매니저에 해당 충돌체를 저장합니다.
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			test->AddComponent(collider);
		}

		// 씬에 액터를 저장합니다.
		AddActor(test);
	}

	// 충돌 테스트를 위한 물체
	{
		// 액터를 생성합니다.
		Actor* test = new Actor();
		test->SetLayer(LAYER_OBJECT);
		test->SetPos({ 300, 200 });

		// 충돌 설정
		{
			// 콜라이더 생성 및 크기를 조정합니다.
			BoxCollider* collider = new BoxCollider();
			collider->SetSize({ 100, 100 });

			// 콜리전 레이어 정보를 설정합니다.
			// * 땅으로 설정
			collider->SetCollisionLayer(CLT_OBJECT);

			// 충돌체 매니저에 해당 충돌체를 저장합니다.
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			test->AddComponent(collider);
		}


		// 씬에 액터를 저장합니다.
		AddActor(test);
	}

	// Tilemap
	{
		TilemapActor* actor = new TilemapActor();
		//AddActor(actor);

		//_tilemapActor = actor;

		// 실제 타일맵에 대한 정보
		{
			//// 타일 맵을 생성합니다.
			//auto* tm = GET_SINGLE(ResourceManager)->CreateTilemap(L"Tilemap_01");
			//// 타일 맵의 크기를 설정합니다.
			//tm->SetMapSize({ 63, 43 });
			//// 타일 크기를 설정합니다.
			//tm->SetTileSize(48);
			//
			//// 타일맵 액터에 타일맵에 대한 정보를 넘겨줍니다.
			//_tilemapActor->SetTilemap(tm);
			//// 출력하겠다고 설정합니다.
			//_tilemapActor->SetShowDebug(true);
		}
	}
	
	// Sound
	{
		// 사운드를 리소스 매니저에 로드합니다.
		GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\BGM.wav");

		// 리소스 매니저에서 저장된 사운드를 가져와 플레이합니다.
		Sound* sound = GET_SINGLE(ResourceManager)->GetSound(L"BGM");
		sound->Play(true);
	}

	Super::Init();
}

void DevScene::Update()
{
	Super::Update();

	// Update() 함수가 실행되는 간격은 환경(성능)에 따라달라집니다.
	// * 즉, 모든 컴퓨터에서 동일한 속도로 이동시키기 위해 이전 프레임에서 현재 프레임까지의 경과시간을 이용합니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// Save & Load TEST
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Q))
	{
		GET_SINGLE(ResourceManager)->SaveTilemap(L"Tilemap_01", L"Tilemap\\Tilemap01.txt");
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
	{
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_01", L"Tilemap\\Tilemap01.txt");
	}
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);


}

void DevScene::Clear()
{

}
