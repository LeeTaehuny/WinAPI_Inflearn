#include "pch.h"
#include "Player.h"
#include "Missile.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "ObjectManager.h"



Player::Player() : Object(ObjectType::Player)
{
}

Player::~Player()
{
}

void Player::Init()
{
	// TODO : Data
	// * 데이터 시트는 기획자가 관리
	// * 고정된 데이터를 받아와서 초기화

	// 테스트를 위해 하드코딩 합니다.
	// * 스탯 정보
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	// * 위치 정보
	_pos.x = 400;
	_pos.y = 500;
}

void Player::Update()
{
	// 기존 DevScene에 있던 플레이어 업데이트 정보를 여기에 옮겨줍니다.

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
		// _pos.x -= 1;
		_pos.x -= deltaTime * _stat.speed;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		// _pos.x += 1;
		_pos.x += deltaTime * _stat.speed;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		// 거리 = 시간 * 속도이므로 다시 수정해줍니다.
		// _pos.x -= 1;
		_pos.y -= deltaTime * _stat.speed;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		// _pos.x += 1;
		_pos.y += deltaTime * _stat.speed;
	}

	// * "스페이스바"를 누르는 순간 미사일이 발사되도록 설정합니다.
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// TODO : 미사일 발사
		// 미사일을 생성합니다.
		Missile* missile = GET_SINGLE(ObjectManager)->CreateObject<Missile>();

		// 미사일의 위치를 설정합니다.
		missile->SetPos(_pos);
		// 미사일을 오브젝트 목록에 추가합니다.
		GET_SINGLE(ObjectManager)->Add(missile);
	}
}

void Player::Render(HDC hdc)
{
	// 간단한 테스트를 위해 플레이어를 원으로 그려줍니다.
	Utils::DrawCircle(hdc, _pos, 50);
}
