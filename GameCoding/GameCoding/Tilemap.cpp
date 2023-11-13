#include "pch.h"
#include "Tilemap.h"
#include <fstream>
#include <iostream>

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{
}

void Tilemap::LoadFile(const wstring& path)
{
	// C 스타일
	if (false)
	{
		// 빈 파일을 생성합니다.
		FILE* file = nullptr;
		// 파일을 읽기(read binary) 형식으로 오픈합니다.
		::_wfopen_s(&file, path.c_str(), L"rb");
		// 파일이 존재하지 않는다면 종료합니다.
		assert(file != nullptr);

		// 파일에 내용을 적어줍니다.
		// * 예시 _mapSize 기입
		//   -> 해당 변수의 주소, 크기, 길이, 저장할 파일
		::fread(&_mapSize.x, sizeof(_mapSize.x), 1, file);
		::fread(&_mapSize.y, sizeof(_mapSize.y), 1, file);

		// 내용을 불러오기 전에 배열을 먼저 초기화해줍니다.
		SetMapSize(_mapSize);

		// 벡터의 내용을 기입합니다.
		for (int32 y = 0; y < _mapSize.y; y++)
		{
			for (int32 x = 0; x < _mapSize.x; x++)
			{
				// 불러올 값을 임시로 초기화합니다.
				int32 value = -1;
				// 파일에 있는 내용을 읽어옵니다.
				::fread(&value, sizeof(value), 1, file);

				// 가져온 값을 tiles 벡터에 저장합니다.
				_tiles[y][x].value = value;
			}
		}

		// 파일 사용이 끝났으므로 파일을 닫아줍니다.
		::fclose(file);
	}

	// C++ 스타일
	{
		// input filestream을 선언합니다.
		wifstream ifs;
		// 경로에 input filestream을 오픈합니다.
		ifs.open(path);

		// input filestream에서 데이터를 추출합니다.
		ifs >> _mapSize.x;
		ifs >> _mapSize.y;

		// 내용을 불러오기 전에 배열을 먼저 초기화해줍니다.
		SetMapSize(_mapSize);

		// 벡터의 내용을 기입합니다.
		for (int32 y = 0; y < _mapSize.y; y++)
		{
			// C++에서는 얼만큼의 크기를 읽어야 하는지 지정을 하지 않았습니다.
			// * 즉, 라인을 통째로 읽고 거기서 세부 데이터를 추출해보도록 하겠습니다.
			wstring line;
			ifs >> line;

			for (int32 x = 0; x < _mapSize.x; x++)
			{
				_tiles[y][x].value = line[x] - L'0';
			}
		}
		// output filestream의 사용이 완료되었으므로 닫아줍니다.
		ifs.close();
	}
}

void Tilemap::SaveFile(const wstring& path)
{
	// C 스타일
	if (false)
	{
		// 빈 파일을 생성합니다.
		FILE* file = nullptr;
		// 파일을 쓰기(write binary) 형식으로 오픈합니다.
		::_wfopen_s(&file, path.c_str(), L"wb");
		// 파일이 존재하지 않는다면 종료합니다.
		assert(file != nullptr);

		// 파일에 내용을 적어줍니다.
		// * 예시 _mapSize 기입
		//   -> 해당 변수의 주소, 크기, 길이, 저장할 파일
		::fwrite(&_mapSize.x, sizeof(_mapSize.x), 1, file);
		::fwrite(&_mapSize.y, sizeof(_mapSize.y), 1, file);

		// 벡터의 내용을 기입합니다.
		for (int32 y = 0; y < _mapSize.y; y++)
		{
			for (int32 x = 0; x < _mapSize.x; x++)
			{
				// 실제 저장될 값을 추출합니다.
				int32 value = _tiles[y][x].value;
				// 파일에 내용을 적어줍니다.
				::fwrite(&value, sizeof(value), 1, file);
			}
		}

		// 파일 사용이 끝났으므로 파일을 닫아줍니다.
		::fclose(file);
	}

	// C++ 스타일
	{
		// output filestream을 선언합니다.
		wofstream ofs;
		// 경로에 output filestream을 오픈합니다.
		ofs.open(path);

		// output filestream에 데이터를 추가합니다.
		ofs << _mapSize.x << endl;
		ofs << _mapSize.y << endl;

		// 벡터의 내용을 기입합니다.
		for (int32 y = 0; y < _mapSize.y; y++)
		{
			for (int32 x = 0; x < _mapSize.x; x++)
			{
				ofs << _tiles[y][x].value;
			}
			ofs << endl;
		}

		// output filestream의 사용이 완료되었으므로 닫아줍니다.
		ofs.close();
	}
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
