#include "pch.h"
#include "Player.h"
#include "LineMesh.h"
#include "Bullet.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "UIManager.h"


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

	// 만약 자신의 턴이 아니라면?
	if (_playerTurn == false)
	{
		// 조기리턴합니다.
		return;
	}

	// 앵글을 업데이트 합니다.
	UpdateFireAngle();

	// 테스트로 입력받은 키보드 값에 따라 _playerPos를 이동시킵니다.
	// * 대각선으로 이동하는 경우는 두 개의 키를 누르고, 두 좌표가 이동하기 때문에 이동 거리가 더욱 증가하는 문제가 생깁니다.
	//   (즉, 대각선 방향으로 이동 시 이동 속도가 증가합니다.)
	// ** 삼각함수 등 수학적인 처리가 필요합니다.
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		// 이동거리 = 시간 * 속도
		_pos.x -= deltaTime * _stat.speed;
		// 왼쪽 방향으로 설정합니다.
		_dir = Dir::Left;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += deltaTime * _stat.speed;
		// 오른쪽 방향으로 설정합니다.
		_dir = Dir::Right;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		// 포신을 반시계방향으로 회전시킵니다.
		// * clamp(값, 최소값, 최대값) : 값을 최소값과 최대값 사이에서만 나오도록 해주는 함수
		_fireAngle = ::clamp(_fireAngle + 50 * deltaTime, 0.0f, 75.0f);
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		// 포신을 시계방향으로 회전시킵니다.
		// * clamp(값, 최소값, 최대값) : 값을 최소값과 최대값 사이에서만 나오도록 해주는 함수
		_fireAngle = ::clamp(_fireAngle - 50 * deltaTime, 0.0f, 75.0f);
	}

	// 포탄 발사 실습
	// * Q와 E를 이용해 포신을 회전시킬 것입니다.
	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q))
	{

	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::E))
	{

	}

	// 스페이스바를 누르고 있다면?
	if (GET_SINGLE(InputManager)->GetButton(KeyType::SpaceBar))
	{
		// 현재 파워 퍼센트를 가져옵니다.
		float percent = GET_SINGLE(UIManager)->GetPowerPercent();

		// 파워 게이지를 증가시켜줍니다.
		// * 최대값이 100을 넘지 않게 설정합니다.
		percent = min(100, percent + 100 * deltaTime);

		// 파워 게이지를 세팅합니다.
		GET_SINGLE(UIManager)->SetPowerPercent(percent);
	}

	// 스페이스바에서 손을 뗀다면?
	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::SpaceBar))
	{
		// 슈팅

		// 이동할 수 없도록 턴을 종료합니다.
		_playerTurn = false;

		// 현재 파워 퍼센트를 가져옵니다.
		float percent = GET_SINGLE(UIManager)->GetPowerPercent();
		// 발사 속도를 설정합니다.
		float speed = 10.0f * percent;
		// 각도를 받아옵니다.
		float angle = GET_SINGLE(UIManager)->GetBarrelAngle();

		// 총알을 생성합니다.
		Bullet* bullet = GET_SINGLE(ObjectManager)->CreateObject<Bullet>();
		// 총알의 위치를 플레이어 위치로 설정합니다.
		bullet->SetPos(_pos);
		// 총알의 속도를 지정합니다.
		// * x : speed * cos(angle)
		// * y : speed * -sin(angle)
		bullet->SetSpeed(Vector(speed * ::cos(angle * PI / 180.0f), -1 * speed * ::sin(angle * PI / 180.0f)));

		// 총알의 주체를 저장합니다.
		bullet->SetOwner(this);

		// 총알을 오브젝트 목록에 추가합니다.
		GET_SINGLE(ObjectManager)->Add(bullet);
	}
}

void Player::Render(HDC hdc)
{
	// 만약에 왼쪽 방향을 바라보고 있다면?
	if (_dir == Dir::Left)
	{
		// 리소스 매니저에 특정 키를 입력해 해당되는 mesh를 전달받습니다.
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());

		// 만약 전달받은 mesh가 존재한다면?
		if (mesh)
		{
			mesh->Render(hdc, _pos, 0.5f, 0.5f);
		}
	}
	// 만약에 오른쪽 방향을 바라보고 있다면?
	else if (_dir == Dir::Right)
	{
		// 리소스 매니저에 특정 키를 입력해 해당되는 mesh를 전달받습니다.
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());

		// 만약 전달받은 mesh가 존재한다면?
		if (mesh)
		{
			mesh->Render(hdc, _pos, -0.5f, 0.5f);
		}
	}

	// 만약 현재 플레이어 차례라면?
	if (_playerTurn)
	{
		// 플레이어의 차례를 표현하기 위한 RECT를 설정합니다.
		RECT rect;
		rect.bottom = static_cast<LONG>(_pos.y - 60);
		rect.left = static_cast<LONG>(_pos.x - 10);
		rect.right = static_cast<LONG>(_pos.x + 10);
		rect.top = static_cast<LONG>(_pos.y - 80);

		// 브러쉬를 생성 및 선택합니다.
		HBRUSH brush = ::CreateSolidBrush(RGB(250, 236, 197));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

		// 플레이어의 차례를 표현합니다.
		::Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

		// 브러시 설정을 해제하고, 삭제합니다.
		::SelectObject(hdc, oldBrush);
		::DeleteObject(brush);
	}

}

wstring Player::GetMeshKey()
{
	// 플레이어 타입이 미사일 탱크라면?
	if (_playerType == PlayerType::MissileTank)
	{
		return L"MissileTank";
	}

	return L"CanonTank";
}

void Player::UpdateFireAngle()
{
	// 이동방향에 따라서 처리합니다.
	if (_dir == Dir::Left)
	{
		// 각도를 9시 방향으로 설정합니다.
		GET_SINGLE(UIManager)->SetPlayerAngle(180);
		GET_SINGLE(UIManager)->SetBarrelAngle(180 - _fireAngle);
	}
	else
	{
		// 각도를 3시 방향으로 설정합니다.
		GET_SINGLE(UIManager)->SetPlayerAngle(0);
		GET_SINGLE(UIManager)->SetBarrelAngle(_fireAngle);
	}
}
