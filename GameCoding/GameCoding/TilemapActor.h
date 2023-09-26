#pragma once
#include "Actor.h"

class Tilemap;

// 타일맵을 들고있는 액터입니다. (타일맵 출력용)
class TilemapActor : public Actor
{
	using Super = Actor;
public:
	TilemapActor();
	virtual ~TilemapActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	// 마우스 클릭으로 타일맵 정보를 변환시키기 위한 함수를 선언합니다.
	void TilePicking();

	// 타일맵을 설정하기 위한 함수를 정의합니다.
	void SetTilemap(Tilemap* tilemap) { _tilemap = tilemap; }
	// 타일맵을 반환하기 위한 함수를 정의합니다.
	Tilemap* GetTilemap() { return _tilemap; }

	// 실제 출력 여부를 설정하기 위한 함수를 정의합니다.
	void SetShowDebug(bool showDebug) { _showDebug = showDebug; }

protected:
	// 타일맵 정보를 저장하기 위한 변수를 선언합니다.
	Tilemap* _tilemap = nullptr;
	// 타일맵을 렌더할지 판별하기 위한 변수를 선언합니다.
	bool _showDebug = false;
};

