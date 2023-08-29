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

	// 각도를 설정할 수 있도록 Setter 함수를 정의합니다.
	void SetAngle(float angle) { _angle = angle; }

protected:
	// 이동할 각도를 저장할 변수를 선언합니다.
	float _angle = 0.0f;

	// 미사일은 발사되고 0.2초 후 유도탄으로 변경되게 설정할 것입니다.
	// * 누적된 시간을 저장할 변수를 선언합니다.
	float _sumTime = 0.0f;
	
	// 미사일이 타겟팅할 타겟을 저장하는 변수를 선언합니다.
	Object* _target = nullptr;
};

