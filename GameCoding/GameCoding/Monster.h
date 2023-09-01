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
	// 로밍할 수 있는 범위를 저장할 변수를 선언합니다.
	// * 로밍 시작위치
	Vector _start = { 300,100 };
	// * 로밍 종료위치
	Vector _end = { 600, 250 };

};

