#include "pch.h"
#include "Tilemap.h"

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{
}

void Tilemap::LoadFile(const wstring& path)
{
}

void Tilemap::SaveFile(const wstring& path)
{
}

Tile* Tilemap::GetTileAt(Vec2Int pos)
{
	// 만약 위치가 맵 정보를 벗어난 경우라면?
	if (pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y >= _mapSize.y)
	{
		return nullptr;
	}

	// 위치가 정상이므로 해당 위치의 타일을 반환합니다.
	return &_tiles[pos.y][pos.x];
}

void Tilemap::SetMapSize(Vec2Int size)
{
	// 맵 사이즈를 설정합니다.
	_mapSize = size;

	// 갱신된 맵 사이즈를 바탕으로 타일들에 대한 정보를 갱신해줍니다.
	// * 먼저 이중 벡터를 사이즈에 맞게 초기화합니다.
	_tiles = vector<vector<Tile>>(size.y, vector<Tile>(size.x));

	for (int32 y = 0; y < size.y; y++)
	{
		for (int32 x = 0; x < size.x; x++)
		{
			// TODO : 내부정보 기입
			_tiles[y][x] = Tile{ 0 };
		}
	}
}

void Tilemap::SetTileSize(int32 size)
{
	_tileSize = size;
}
