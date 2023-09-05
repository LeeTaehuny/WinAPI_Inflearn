#pragma once
#include "Object.h"
class Monster : public Object
{
public:
	Monster();
	virtual ~Monster() override;

	// 부모 클래스에서 만들어진 순수 가상함수를 재정의합니다.
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	// 몬스터가 어떤 위치를 바라보고 있다고 가정합니다.
	// * 몬스터가 바라보는 위치를 저장하기 위한 변수를 선언합니다. (위치벡터)
	Vector _lookPos = {};
	// * 해당 위치까지의 방향을 저장하기 위한 변수를 선언합니다. (방향벡터)
	Vector _lookDir = {};

};

