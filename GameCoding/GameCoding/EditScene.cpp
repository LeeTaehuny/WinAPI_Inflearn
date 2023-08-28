#include "pch.h"
#include "EditScene.h"
#include "InputManager.h"

// 파일 스트림 방식을 사용하기 위해 헤더를 추가합니다.
#include <fstream>

EditScene::EditScene()
{
}

EditScene::~EditScene()
{
}

void EditScene::Init()
{
}

void EditScene::Update()
{
	// 만약 왼쪽 마우스 다운 입력이 들어왔다면?
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		// 해당 시점에서의 마우스 위치를 저장합니다.
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

		// 만약 내가 처음 클릭했다면?
		if (_setOrigin)
		{
			// 마지막 좌표를 현재 마우스 좌표로 설정합니다.
			_lastPos = mousePos;
			// 처음이 아니라고 표시합니다.
			_setOrigin = false;
		}
		// 처음 클릭한 것이 아니라면?
		else
		{
			// 점이 두 개 완성되었으므로 (마지막 좌표, 현재 마우스 좌표)를 lines 컨테이너에 추가해줍니다.
			_lines.push_back(make_pair(_lastPos, mousePos));
			// 마지막 좌표를 마우스 위치로 업데이트 합니다.
			_lastPos = mousePos;
		}
	}

	// 만약 오른쪽 마우스 다운 입력이 들어왔다면?
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))
	{
		// 라인을 그만 이을 것입니다.
		// * 처음이라고 표시합니다.
		_setOrigin = true;
	}

	// Save
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::S))
	{
		// Save를 진행합니다.

		// 파일을 저장할 변수를 선언합니다.
		wofstream file;
		// 파일 이름 : Unit.txt
		file.open(L"Unit.txt");

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

	// Load
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D))
	{
		// 파일을 불러오기 위한 변수를 선언합니다.
		wifstream file;
		// 파일을 열어줍니다.
		// * open(열고싶은 파일 이름)
		file.open(L"Unit.txt");

		// 라인 개수를 저장할 변수를 선언합니다.
		int32 count;
		// 파일에서 라인 개수를 꺼내줍니다.
		file >> count;

		// 기존에 남아있던 원본을 삭제합니다.
		_lines.clear();

		// 파일에는 이미지의 중점이 0,0으로 설정되어 있습니다.
		// * 보정값을 추가해 0,0이 아닌 원하는 위치에 로드해봅니다.
		int32 midX = 400;
		int32 midY = 300;

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

			// 보정값을 로딩할 때 적용해줍니다.
			pt1.x += midX;
			pt1.y += midY;
			pt2.x += midX;
			pt2.y += midY;

			// 추출한 정보를 바탕으로 lines 컨테이너에 정보를 채워줍니다.
			_lines.push_back(make_pair(pt1, pt2));

			// 모두 복구했으므로 다시 처음부터라고 지정합니다.
			_setOrigin = true;
		}

		// 파일 사용을 완료했으므로 파일을 닫아줍니다.
		file.close();
	}
}

void EditScene::Render(HDC hdc)
{
	// _lines을 순회합니다.
	for (auto& line : _lines)
	{
		// 요소에 저장되어 있는 시작위치, 종료 위치를 저장합니다.
		POINT pt1 = line.first;
		POINT pt2 = line.second;

		// 선을 이을 시작 위치를 설정합니다.
		Pos pos1;
		pos1.x = static_cast<float>(pt1.x);
		pos1.y = static_cast<float>(pt1.y);

		// 선을 이을 종료 위치를 설정합니다.
		Pos pos2;
		pos2.x = static_cast<float>(pt2.x);
		pos2.y = static_cast<float>(pt2.y);

		// 선을 그려줍니다.
		Utils::DrawLine(hdc, pos1, pos2);
	}
}
