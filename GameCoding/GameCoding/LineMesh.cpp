#include "pch.h"
#include "LineMesh.h"

// 파일 스트림 방식을 사용하기 위해 헤더를 추가합니다.
#include <fstream>

void LineMesh::Save(wstring path)
{
	// Save를 진행합니다.

	// 파일을 저장할 변수를 선언합니다.
	wofstream file;
	// 특정 경로에 있는 파일을 오픈합니다.
	file.open(path);

	// 그린 선들의 중앙을 구하기 위해 x, y좌표의 최대 최소값을 역으로 설정합니다.
	int32 minX = INT32_MAX;
	int32 maxX = INT32_MIN;
	int32 minY = INT32_MAX;
	int32 maxY = INT32_MIN;

	// _lines를 순회합니다.
	for (auto& line : _lines)
	{
		// lines 컨테이너에 저장된 요소의 시작위치, 종료위치를 저장합니다.
		POINT from = line.first;
		POINT to = line.second;

		// 위에서 구한 값을 바탕으로 가장 작은 x, y값을 구해줍니다.
		minX = min(min(minX, from.x), to.x);
		minY = min(min(minY, from.y), to.y);

		// 위에서 구한 값을 바탕으로 가장 큰 x, y값을 구해줍니다.
		maxX = max(max(maxX, from.x), to.x);
		maxY = max(max(maxY, from.y), to.y);
	}

	// 위에서 구한 가장 작은 x, y / 가장 큰 x, y값을 이용해 중간 좌표를 구해줍니다.
	int32 midX = (maxX + minX) / 2;
	int32 midY = (maxY + minY) / 2;

	// 라인 개수가 몇 개 있는지 파일에 추가합니다.
	file << static_cast<int32>(_lines.size()) << endl;

	// _lines를 순회합니다.
	for (auto& line : _lines)
	{
		// 시작 위치를 저장합니다.
		POINT from = line.first;
		// 시작 위치의 x, y값에 중앙 위치를 빼줍니다.
		from.x -= midX;
		from.y -= midY;

		// 종료 위치를 저장합니다.
		POINT to = line.second;
		// 종료 위치의 x, y값에 중앙 위치를 빼줍니다.
		to.x -= midX;
		to.y -= midY;

		// 꺼내온 위치들을 포맷을 맞춰 file에 저장합니다.
		// * ex. (0,0)->(1,1)

		// wstring 형식으로 포맷을 맞춰줍니다.
		wstring str = std::format(L"({0},{1})->({2},{3})", from.x, from.y, to.x, to.y);
		// 위에서 만든 wstring을 파일에 저장합니다. (줄 단위)
		file << str << endl;
	}

	// 파일 사용을 완료했으므로 파일을 닫아줍니다.
	file.close();
}

void LineMesh::Load(wstring path)
{
	// 파일을 불러오기 위한 변수를 선언합니다.
	wifstream file;
	// 파일을 열어줍니다.
	// 어떤 경로에 저장할지를 선택하여 파일을 오픈합니다.
	file.open(path);

	// 라인 개수를 저장할 변수를 선언합니다.
	int32 count;
	// 파일에서 라인 개수를 꺼내줍니다.
	file >> count;

	// 기존에 남아있던 원본을 삭제합니다.
	_lines.clear();

	// 위에서 받아온 라인 개수만큼 복원합니다.
	for (int i = 0; i < count; i++)
	{
		// 파일에서 복원한 내용을 저장할 변수를 선언합니다.
		POINT pt1;
		POINT pt2;

		// 파일에서 읽어온 문자열(wstring)을 저장하기 위한 변수를 선언합니다.
		wstring str;
		// 파일에서 문자열을 읽어옵니다. (줄 단위)
		file >> str;

		// 특정 포맷의 string을 추출합니다.
		// swscanf_s(작업할 문자열, 포맷정보, 저장 위치)
		::swscanf_s(str.c_str(), L"(%d,%d)->(%d,%d)", &pt1.x, &pt1.y, &pt2.x, &pt2.y);

		// 추출한 정보를 바탕으로 lines 컨테이너에 정보를 채워줍니다.
		_lines.push_back(make_pair(pt1, pt2));
	}

	// 파일 사용을 완료했으므로 파일을 닫아줍니다.
	file.close();

	// 그린 그림의 크기를 구하기 위해 x, y좌표의 최대 최소값을 역으로 설정합니다.
	int32 minX = INT32_MAX;
	int32 maxX = INT32_MIN;
	int32 minY = INT32_MAX;
	int32 maxY = INT32_MIN;

	// _lines를 순회하며 모든 라인에 대한 minX/Y, maxX/Y를 구합니다.
	for (auto& line : _lines)
	{
		// lines 컨테이너에 저장된 요소의 시작위치, 종료위치를 저장합니다.
		POINT from = line.first;
		POINT to = line.second;

		// 위에서 구한 값을 바탕으로 가장 작은 x, y값을 구해줍니다.
		minX = min(min(minX, from.x), to.x);
		minY = min(min(minY, from.y), to.y);

		// 위에서 구한 값을 바탕으로 가장 큰 x, y값을 구해줍니다.
		maxX = max(max(maxX, from.x), to.x);
		maxY = max(max(maxY, from.y), to.y);
	}

	// 실제 그림의 크기를 저장합니다.
	_width = maxX - minX;
	_height = maxY - minY;
}

void LineMesh::Render(HDC hdc, Pos pos, float ratioX, float ratioY) const
{
	// _lines을 순회합니다.
	for (auto& line : _lines)
	{
		// 요소에 저장되어 있는 시작위치, 종료 위치를 저장합니다.
		POINT pt1 = line.first;
		POINT pt2 = line.second;

		// 선을 이을 시작 위치를 설정합니다.
		Pos pos1;
		pos1.x = (static_cast<float>(pt1.x) * ratioX) + pos.x;
		pos1.y = (static_cast<float>(pt1.y) * ratioY) + pos.y;

		// 선을 이을 종료 위치를 설정합니다.
		Pos pos2;
		pos2.x = (static_cast<float>(pt2.x) * ratioX) + pos.x;
		pos2.y = (static_cast<float>(pt2.y) * ratioY) + pos.y;

		// 선을 그려줍니다.
		Utils::DrawLine(hdc, pos1, pos2);
	}
}
