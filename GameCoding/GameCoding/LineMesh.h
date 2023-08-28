#pragma once
#include "ResourceBase.h"

class LineMesh : public ResourceBase
{
public:
	// 경로를 받아 저장하는 함수를 선언합니다.
	void Save(wstring path);
	// 경로를 받아 로드하는 함수를 선언합니다.
	void Load(wstring path);
	// 렌더 함수를 선언합니다.
	void Render(HDC hdc, Pos pos) const;
protected:
	// 로드한 라인들의 정보를 저장하기 위한 벡터 컨테이너를 선언합니다.
	vector<pair<POINT, POINT>> _lines;
};

