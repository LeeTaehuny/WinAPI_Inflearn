#pragma once
#include "ResourceBase.h"

class Texture;

// 재생하는 애니메이션에 대한 정보를 담을 구조체를 선언합니다.
struct FlipbookInfo
{
	// 텍스쳐의 일부 영역을 애니메이션으로 인지해서 애니메이션을 재생할 것입니다.
	// * 텍스쳐에 대한 정보를 저장하는 변수를 선언합니다.
	Texture* texture = nullptr;
	// 완성된 애니메이션의 이름을 저장하는 변수를 선언합니다.
	wstring name;

	// 애니메이션을 재생하기 위한 텍스쳐 한 칸의 사이즈를 저장하기 위한 변수를 선언합니다.
	Vec2Int size = {};

	// 애니메이션을 재생하기 위한 텍스쳐의 순서(위치)를 저장하기 위한 변수를 선언합니다.
	// * 시작 위치 (x)
	int32 start;
	// * 종료 위치 (x)
	int32 end;
	// * 라인 정보 (y)
	int32 line;

	// 재생 속도를 저장하기 위한 변수를 선언합니다.
	// * 기본값 : 1초동안 (line, start) 위치의 텍스쳐부터 (line, end)까지의 텍스쳐를 재생
	float duration = 1.0f;

	// 반복 여부를 저장하기 위한 변수를 선언합니다.
	bool loop = true;
};

// 애니메이션을 저장하는 클래스입니다.
class Flipbook : public ResourceBase
{
public:
	Flipbook();
	virtual ~Flipbook() override;

	// 재생하는 애니메이션에 대한 정보를 설정해주기 위한 함수를 정의합니다.
	void SetInfo(const FlipbookInfo& info) { _info = info; }
	// 재생하는 애니메이션에 대한 정보를 반환해주기 위한 함수를 정의합니다.
	const FlipbookInfo& GetInfo() { return _info; }

	/**
	- const & 사용 이유 : 구조체의 정보량이 많아지면 일반 매개변수로 전달 시 복사 형식으로 효율성이 저하될 수 있음
						 즉, 원본을 복사하는 것이 아닌 참조 형식으로 해당 주소값을 공유하게 만들어두고,
						 const 키워드를 통해 해당 변수를 수정하지 못하게 하여 효율성을 높이고 안전하게 사용 가능하게 한 것.
	*/

private:
	// 재생하는 애니메이션에 대한 정보를 담은 구조체 타입의 변수를 선언합니다.
	FlipbookInfo _info;
};
