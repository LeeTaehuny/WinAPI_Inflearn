#pragma once
#include "Scene.h"

// 실제로 툴에서 선을 그려 해당 좌표를 파일로 저장 및 불러오는 것이 목적
class EditScene : public Scene
{
public:
	EditScene();
	virtual ~EditScene() override;

	// 부모 클래스의 함수를 오버라이드 합니다.
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	// 선을 저장하기 위한 벡터 컨테이너를 선언합니다.
	// * (시작위치, 종료위치)
	vector<pair<POINT, POINT>> _lines;

	// 처음 점을 찍을 때 이전 위치가 존재하지 않으므로 처음인 것을 판별하기 위한 변수를 선언합니다.
	bool _setOrigin = true;
	// 어디서부터 어디까지 가는지를 찍기 위해 마지막 좌표를 저장할 변수를 선언합니다.
	POINT _lastPos = {};
};

