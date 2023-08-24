#pragma once
#include "Object.h"
class Missile : public Object
{
public:
	Missile();
	virtual ~Missile() override;

	// 부모 클래스에서 만들어진 순수 가상함수를 재정의합니다.
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
};

