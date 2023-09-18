#pragma once

// 씬에 배치 가능한 오브젝트 클래스입니다.
class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void BeginPlay();
	virtual void Tick();

	virtual void Render(HDC hdc);

	// 위치 정보를 설정하기 위한 함수를 정의합니다.
	void SetPos(Vec2 pos) { _pos = pos; }
	// 위치 정보를 반환하기 위한 함수를 정의합니다.
	Vec2 GetPos() { return _pos; }

protected:
	// 씬에 배치가 가능하다는 것은 위치 정보를 가지고 있다는 의미입니다.
	// * 위치 정보를 저장하기 위한 변수를 선언합니다.
	Vec2 _pos = { 0,0 };

private:
	// 여기에 스프라이트 or 텍스쳐를 넣어줄 수도 있음
	// * 하드코딩
	// * 모든 액터가 스프라이트를 들고 있는 것이 아닐 수도 있기 때문

	// * 언리얼은 상속 구조로 스프라이트를 들고 있는 액터를 추가로 만들어주는 방식
};

