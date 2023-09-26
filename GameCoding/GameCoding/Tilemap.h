#pragma once
#include "ResourceBase.h"

// 타일에 저장될 값들의 정보들을 저장하기 위한 구조체를 선언합니다.
struct Tile
{
	// TODO
	int32 value = 0;
};

// 맵의 정보와 타일의 크기를 구분하기 위한 열거형을 선언합니다.
enum TILE_SIZE
{
	TILE_WIDTH = 63,
	TILE_HEIGHT = 43,

	TILE_SIZEX = 48,
	TILE_SIZEY = 48,
};

class Tilemap : public ResourceBase
{
public:
	Tilemap();
	virtual ~Tilemap() override;

	// 파일을 로드하기 위한 가상 함수를 오버라이드합니다.
	virtual void LoadFile(const wstring& path) override;
	// 파일을 저장하기 위한 가상 함수를 오버라이드합니다.
	virtual void SaveFile(const wstring& path) override;

	// 맵 사이즈를 반환하기 위한 함수를 정의합니다.
	Vec2Int GetMapSize() { return _mapSize; }
	// 타일 사이즈를 반환하기 위한 함수를 정의합니다.
	int32 GetTileSize() { return _tileSize; }
	// 모든 타일들을 반환하기 위한 함수를 정의합니다.
	vector<vector<Tile>>& GetTiles() { return _tiles; }

	// 특정 위치에 있는 타일의 정보를 반환하기 위한 함수를 선언합니다.
	Tile* GetTileAt(Vec2Int pos);

	// 전체 맵의 크기와 한 개의 타일 크기를 설정하기 위한 함수를 선언합니다.
	void SetMapSize(Vec2Int size);
	void SetTileSize(int32 size);

private:
	// 가지고 있어야 할 핵심 정보
	// * 전체 타일 맵의 크기를 저장하기 위한 변수를 선언합니다.
	Vec2Int _mapSize = {};
	// * 타일 한 칸의 사이즈를 저장하기 위한 변수를 선언합니다.
	int32 _tileSize = {};

	// * 각 타일에 저장될 값들을 저장하기 위한 벡터 컨테이너를 선언합니다.
	//   -> 이중 벡터로 선언해 _tiles[y][x] 형태로 해당 값을 사용하기 위함
	vector<vector<Tile>> _tiles;
};

