#include "pch.h"
#include "DevScene.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"

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

	// 스프라이트 테스트
	// * 스프라이트에 필요한 텍스쳐를 받아옵니다.
	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Start");
	// * 스프라이트를 생성합니다.
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", tex, 150, 0, 150, 150);
}

void DevScene::Update()
{
	// Update() 함수가 실행되는 간격은 환경(성능)에 따라달라집니다.
	// * 즉, 모든 컴퓨터에서 동일한 속도로 이동시키기 위해 이전 프레임에서 현재 프레임까지의 경과시간을 이용합니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

}

void DevScene::Render(HDC hdc)
{
	// 테스트로 출력하고 싶은 텍스처를 가져옵니다.
	//Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Stage01");
	Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Start_On");

	// 해당 텍스처를 출력합니다.
	//::BitBlt(hdc,
	//	  0, 0, 
	//	  GWinSizeX, GWinSizeY, 
	//	  tex->GetDC(),
	//	  0, 0, 
	//	  SRCCOPY
	//);

	::BitBlt(hdc,
		0, 0,
		GWinSizeX, GWinSizeY,
		sprite->GetDC(),
		sprite->GetPos().x, sprite->GetPos().y,
		SRCCOPY
	);
}
