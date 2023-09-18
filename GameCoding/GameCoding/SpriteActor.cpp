#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"

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

	// 스프라이트를 출력합니다.
	::BitBlt(hdc,
		(int32)_pos.x - size.x / 2, (int32)_pos.y - size.y / 2,
		size.x, size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x, _sprite->GetPos().y,
		SRCCOPY
	);
}
