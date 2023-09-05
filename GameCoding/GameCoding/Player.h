#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player();
	virtual ~Player() override;

	// 부모 클래스에서 만들어진 순수 가상함수를 재정의합니다.
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// 메쉬 키를 반환하는 함수를 선언합니다.
	wstring GetMeshKey();

	// 플레이어 아이디를 세팅하기 위한 함수를 정의합니다.
	void SetPlayerId(int32 playerId) { _playerId = playerId; }
	// 플레이어 타입을 세팅하기 위한 함수를 정의합니다.
	void SetPlayerType(PlayerType playerType) { _playerType = playerType; }
	// 플레이어의 턴을 세팅하기 위한 함수를 정의합니다.
	void SetPlayerTurn(bool playerTurn) { _playerTurn = playerTurn; }

	// 플레이어 아이디를 반환하기 위한 함수를 정의합니다.
	int32 GetPlayerId() { return _playerId; }
	// 플레이어 타입을 반환하기 위한 함수를 정의합니다.
	PlayerType GetPlayerType() { return _playerType; }
	// 현재 자신의 차례인지를 반환하기 위한 함수를 정의합니다.
	bool GetPlayerTurn() { return _playerTurn; }

public:
	// 플레이어의 타입을 저장하기 위한 변수를 선언합니다.
	PlayerType	_playerType = PlayerType::CanonTank;

	// 플레이어를 구분하기 위한 변수를 선언합니다.
	int32		_playerId = 0;
	// 플레이어의 턴인지 판별해주기 위한 변수를 선언합니다.
	bool		_playerTurn = false;

	// 발사 각도를 저장하기 위한 변수를 선언합니다.
	float		_fireAngle = 0.0f;

};

