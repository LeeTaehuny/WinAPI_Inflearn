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
		
		// 구체 콜라이더 컴포넌트를 생성합니다.
		SphereCollider* collider = new SphereCollider();
		// 구체 콜라이더 컴포넌트의 반지름 및 디버그 유무를 세팅합니다.
		collider->SetRadius(50.0f);
		collider->SetShowDebug(true);
		// 구체 콜라이더 컴포넌트를 플레이어에 추가합니다.
		player->AddComponent(collider);

		// 충돌체 매니저에 해당 충돌체를 저장합니다.
		GET_SINGLE(CollisionManager)->AddCollider(collider);

		// 액터의 종류에 따라 레이어를 설정합니다.
		player->SetLayer(LAYER_OBJECT);

		// 씬에 액터를 저장합니다.
		AddActor(player);
	}

	// 충돌 테스트를 위한 물체
	{
		// 액터를 생성합니다.
		Actor* player = new Actor();

		// 구체 콜라이더 컴포넌트를 생성합니다.
		SphereCollider* collider = new SphereCollider();
		// 구체 콜라이더 컴포넌트의 반지름 및 디버그 유무를 세팅합니다.
		collider->SetRadius(25.0f);
		collider->SetShowDebug(true);
		// 구체 콜라이더 컴포넌트를 플레이어에 추가합니다.
		player->AddComponent(collider);

		// 충돌체 매니저에 해당 충돌체를 저장합니다.
		GET_SINGLE(CollisionManager)->AddCollider(collider);

		// 위치를 설정합니다.
		player->SetPos({ 400, 200 });
		// 액터의 종류에 따라 레이어를 설정합니다.
		player->SetLayer(LAYER_OBJECT);

		// 씬에 액터를 저장합니다.
		AddActor(player);
	}

	// BeginPlay() 함수는 게임 실행과 동시에 호출되는 함수입니다.
	// * 일단 테스트를 위해 여기서 호출하도록 하겠습니다.

	// * 2차원 벡터이므로 이중 for문을 통해 순회합니다.
	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->BeginPlay();
		}
	}
}

void DevScene::Update()
{
	// Update() 함수가 실행되는 간격은 환경(성능)에 따라달라집니다.
	// * 즉, 모든 컴퓨터에서 동일한 속도로 이동시키기 위해 이전 프레임에서 현재 프레임까지의 경과시간을 이용합니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 충돌체 매니저를 업데이트 해줍니다.
	GET_SINGLE(CollisionManager)->Update();

	// * 2차원 벡터이므로 이중 for문을 통해 순회합니다.
	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->Tick();
		}
	}
}

void DevScene::Render(HDC hdc)
{
	// 액터를 렌더합니다.
	// * 2차원 벡터이므로 이중 for문을 통해 순회합니다.
	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->Render(hdc);
		}
	}
}

void DevScene::AddActor(Actor* actor)
{
	// 만약 액터가 존재하지 않는다면?
	if (actor == nullptr)
	{
		// 종료합니다.
		return;
	}

	// 액터가 존재하는 경우입니다.
	// * 액터의 레이어 타입에 맞는 목록에 해당 액터를 추가합니다.
	_actors[actor->GetLayer()].push_back(actor);
}

void DevScene::RemoveActor(Actor* actor)
{
	// 만약 액터가 존재하지 않는다면?
	if (actor == nullptr)
	{
		// 종료합니다.
		return;
	}

	// 액터 레이어와 일치하는 목록을 받아옵니다.
	vector<Actor*>& v = _actors[actor->GetLayer()];

	// 목록에서 해당 액터를 제거합니다.
	v.erase(std::remove(v.begin(), v.end(), actor));
}
