#include "pch.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "Sprite.h"
#include "Texture.h"

#include "TimeManager.h"
#include "SceneManager.h"


FlipbookActor::FlipbookActor()
{
}

FlipbookActor::~FlipbookActor()
{
}

void FlipbookActor::BeginPlay()
{
	Super::BeginPlay();
}

void FlipbookActor::Tick()
{
	Super::Tick();

	// 만약 애니메이션이 존재하지 않는다면?
	if (_flipbook == nullptr)
	{
		// 종료합니다.
		return;
	}

	// 해당 애니메이션의 정보를 받아옵니다.
	const FlipbookInfo& info = _flipbook->GetInfo();

	// 만약 애니메이션이 종료되었다면? (반복 여부 X면서 인덱스가 종료 위치인 경우)
	if (info.loop == false && _idx == info.end)
	{
		// 실행할 것이 없으므로 종료합니다.
		return;
	}

	// 실행할 애니메이션이 있는 경우입니다.
	
	// 누적 시간을 체크하기 위해 프레임 시간을 가져옵니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	// 누적 시간을 증가시켜줍니다.
	_sumTime += deltaTime;

	// 현재 실행하고 있는 애니메이션의 프레임 수를 계산합니다. (총 개수)
	int32 frameCount = (info.end - info.start + 1);
	// 전체 애니메이션을 실행하는 시간과 프레임 수를 계산해 한 프레임이 얼마의 시간동안 재생되어야 하는지를 계산합니다.
	float delta = info.duration / (float)frameCount;

	// 만약 누적 시간이 delta(프레임별 재생 시간)보다 커졌다면?
	if (_sumTime >= delta)
	{
		// 누적시간을 초기화합니다.
		_sumTime = 0.0f;
		// 인덱스를 증가시킵니다. (최대 프레임을 초과하면 0[처음]으로 돌아가게 만들기)
		_idx = (_idx + 1) % frameCount;
	}
}

void FlipbookActor::Render(HDC hdc)
{
	Super::Render(hdc);

	// 만약 애니메이션이 존재하지 않는다면?
	if (_flipbook == nullptr)
	{
		// 종료합니다.
		return;
	}

	// 해당 애니메이션의 정보를 받아옵니다.
	const FlipbookInfo& info = _flipbook->GetInfo();

	// 카메라의 위치 정보를 받불러옵니다.
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	// TransparentBlt() : 스프라이트 중 특정 색상을 투명화하고 출력하는 함수
	::TransparentBlt(hdc,													// 출력할 DC
		//(int32)_pos.x - info.size.x / 2, (int32)_pos.y - info.size.y / 2,	// 이미지를 중점에서부터 그리기 위함 (출력 위치)
		(int32)_pos.x - info.size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2), (int32)_pos.y - info.size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
		info.size.x, info.size.y,											// 애니메이션 한 프레임의 크기
		info.texture->GetDC(),												// 복사할 DC
		(info.start + _idx) * info.size.x, info.line * info.size.y,			// 복사를 시작할 위치
		info.size.x, info.size.y,											// 복사할 크기
		info.texture->GetTransparent()										// 무시할 색상
	);
}

void FlipbookActor::SetFlipbook(Flipbook* flipbook)
{
	// 만약 저장할 애니메이션이 기존 애니메이션과 동일한 경우라면?
	if (flipbook && _flipbook == flipbook)
	{
		// 종료합니다.
		return;
	}

	// 애니메이션을 저장합니다.
	_flipbook = flipbook;
	// 애니메이션을 초기화합니다.
	Reset();
}

void FlipbookActor::Reset()
{
	// 시간을 초기화합니다.
	_sumTime = 0.0f;
	// 인덱스를 초기화합니다.
	_idx = 0;
}
