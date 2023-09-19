#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"

#include "SceneManager.h"

SpriteActor::SpriteActor()
{
}

SpriteActor::~SpriteActor()
{
}

void SpriteActor::BeginPlay()
{
	// 부모의 함수 내용을 불러옵니다.
	Super::BeginPlay();
}

void SpriteActor::Tick()
{
	// 부모의 함수 내용을 불러옵니다.
	Super::Tick();
}

void SpriteActor::Render(HDC hdc)
{
	// 부모의 함수 내용을 불러옵니다.
	Super::Tick();

	// 만약 스프라이트가 저장되지 않았다면?
	if (_sprite == nullptr)
	{
		// 반환해줍니다.
		return;
	}

	// 출력할 스프라이트의 크기를 불러옵니다.
	Vec2Int size = _sprite->GetSize();

	// 카메라의 위치 정보를 받불러옵니다.
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	// 스프라이트를 출력합니다.
	// TransparentBlt() : 스프라이트 중 특정 색상을 투명화하고 출력하는 함수
	// * 매개변수 : 출력DC, 출력할 위치, 출력할 크기, 복사DC, 스프라이트 복사 시작 위치(x, y), 복사할 크기, 투명화 시킬 색상
	::TransparentBlt(hdc,
		(int32)_pos.x - size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2), (int32)_pos.y - size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
		size.x, size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x, _sprite->GetPos().y, // 스프라이트 복사 시작 위치를 설정
		_sprite->GetSize().x, _sprite->GetSize().y,
		_sprite->GetTransparent()
	);
}
