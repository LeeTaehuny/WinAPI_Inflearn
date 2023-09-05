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
	// * 그릴 이미지의 크기 비율을 같이 받아 크기를 설정합니다.
	void Render(HDC hdc, Pos pos, float ratioX = 1.0f, float ratioY = 1.0f) const;
protected:
	// 로드한 라인들의 정보를 저장하기 위한 벡터 컨테이너를 선언합니다.
	vector<pair<POINT, POINT>> _lines;

	// 렌더링 크기를 조절하기 위한 변수를 선언합니다.
	int32 _width = 0;
	int32 _height = 0;
};

