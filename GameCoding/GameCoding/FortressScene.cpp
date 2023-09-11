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

		// 오브젝트 매니저에서 관리하는 오브젝트 목록에 플레이어를 추가합니다.
		GET_SINGLE(ObjectManager)->Add(player);

		// 시작 위치를 설정합니다.
		player->SetPos(Vector{ 100, 400 });
		// 해당 플레이어의 차례라고 설정합니다.
		player->SetPlayerTurn(true);
	}

	// 플레이어 2 생성 및 초기화
	{
		// 오브젝트 매니저를 이용해 플레이어를 생성해줍니다.
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		// 생성된 플레이어의 타입을 설정합니다.
		player->SetPlayerType(PlayerType::CanonTank);
		// 플레이어의 아이디를 설정합니다.
		player->SetPlayerId(1);

		// 오브젝트 매니저에서 관리하는 오브젝트 목록에 플레이어를 추가합니다.
		GET_SINGLE(ObjectManager)->Add(player);

		// 시작 위치를 설정합니다.
		player->SetPos(Vector{ 700, 400 });
		// 해당 플레이어의 차례가 아니라고 설정합니다.
		player->SetPlayerTurn(false);
	}

	// 플레이어의 턴을 바꾸며 모든 수치들을 초기화합니다.
	ChangePlayerTurn();
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

	// Turn
	{
		// 누적 시간을 증가시켜줍니다.
		_sumTime += deltaTime;

		// 만약 누적 시간이 1초가 넘었다면?
		if (_sumTime >= 1.0f)
		{
			// 누적 시간을 초기화합니다.
			_sumTime = 0.0f;

			// 남아있는 시간을 받아옵니다.
			int32 time = GET_SINGLE(UIManager)->GetRemainTime();
			
			// 1초를 줄여줍니다.
			// * 남아있는 시간이 음수가 되면 안되므로, 0과 비교해 큰 숫자를 저장합니다.
			time = max(0, time - 1);

			GET_SINGLE(UIManager)->SetRemainTime(time);

			// 만약 남은 시간이 0이라면?
			if (time == 0)
			{
				// 플레이어의 턴을 넘겨줍니다.
				ChangePlayerTurn();
			}
		}
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

void FortressScene::ChangePlayerTurn()
{
	// 플레이어를 다음 차례로 넘겨줍니다.
	// * 현재는 플레이어가 2명이므로 0, 1만 유지되면 됩니다.
	_playerTurn = (_playerTurn + 1) % 2;

	// 오브젝트 목록을 가져옵니다.
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	// 오브젝트 목록을 순회합니다.
	for (Object* obj : objects)
	{
		// 만약 오브젝트 타입이 플레이어가 아니라면?
		if (obj->GetObjectType() != ObjectType::Player)
		{
			// 넘겨줍니다.
			continue;
		}

		// 플레이어인 경우이므로 형변환을 해줍니다.
		Player* player = static_cast<Player*>(obj);
		// 만약 플레이어의 아이디가 _playerTurn번 이라면?
		if (player->GetPlayerId() == _playerTurn)
		{
			// 해당 플레이어의 턴으로 설정합니다.
			player->SetPlayerTurn(true);
		}
		// 만약 플레이어의 아이디가 _playerTurn이 아니라면?
		else
		{
			// 해당 플레이어의 턴을 종료합니다.
			player->SetPlayerTurn(false);
		}
	}

	// 턴이 변경되었으므로 플레이 시간을 초기화합니다.
	GET_SINGLE(UIManager)->SetRemainTime(10);
	// 플레이어의 스테미나를 최대로 회복시켜줍니다.
	GET_SINGLE(UIManager)->SetStaminaPercent(100.0f);
	// 공격 파워 게이지를 0으로 초기화합니다.
	GET_SINGLE(UIManager)->SetPowerPercent(0.0f);

	// 바람의 세기도 변경합니다. (-100 ~ 100)
	GET_SINGLE(UIManager)->SetWindPercent(static_cast<float>(-100 + rand() % 200));
}
