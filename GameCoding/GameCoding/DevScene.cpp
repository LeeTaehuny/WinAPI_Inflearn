#include "pch.h"
#include "DevScene.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"

DevScene::DevScene()
{

}

DevScene::~DevScene()
{

}

void DevScene::Init()
{

}

void DevScene::Update()
{
	// Update() 함수가 실행되는 간격은 환경(성능)에 따라달라집니다.
	// * 즉, 모든 컴퓨터에서 동일한 속도로 이동시키기 위해 이전 프레임에서 현재 프레임까지의 경과시간을 이용합니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();


	// 테스트로 입력받은 키보드 값에 따라 _playerPos를 이동시킵니다.
	// * 대각선으로 이동하는 경우는 두 개의 키를 누르고, 두 좌표가 이동하기 때문에 이동 거리가 더욱 증가하는 문제가 생깁니다.
	//   (즉, 대각선 방향으로 이동 시 이동 속도가 증가합니다.)
	// ** 삼각함수 등 수학적인 처리가 필요합니다.
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		// 거리 = 시간 * 속도이므로 다시 수정해줍니다.
		// _playerPos.x -= 1;
		_playerPos.x -= deltaTime * _speed;
	}
	
	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		// _playerPos.x += 1;
		_playerPos.x += deltaTime * _speed;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		// 거리 = 시간 * 속도이므로 다시 수정해줍니다.
		// _playerPos.x -= 1;
		_playerPos.y -= deltaTime * _speed;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		// _playerPos.x += 1;
		_playerPos.y += deltaTime * _speed;
	}
}

void DevScene::Render(HDC hdc)
{
	// 플레이어를 화면에 그려줍니다.
	// * test이므로, 원으로 표현합니다.
	Utils::DrawCircle(hdc, _playerPos, 50);
}
