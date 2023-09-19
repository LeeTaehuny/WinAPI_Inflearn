#include "pch.h"
#include "CameraComponent.h"
#include "Actor.h"

#include "SceneManager.h"

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::BeginPlay()
{
}

void CameraComponent::TickComponent()
{
	// 연결된 주인이 존재하지 않는다면?
	if (_owner == nullptr)
	{
		// 종료합니다.
		return;
	}

	// 주인이 연결되어있는 경우입니다.
	// 주인의 위치를 불러옵니다.
	Vec2 pos = _owner->GetPos();

	// temp (카메라의 위치 보정)
	pos.x = ::clamp(pos.x, 400.0f, 3024.f - 400.0f);
	pos.y = ::clamp(pos.y, 300.0f, 2064.f - 300.0f);

	// 카메라의 위치를 주인의 위치로 설정합니다.
	GET_SINGLE(SceneManager)->SetCameraPos(pos);
}

void CameraComponent::Render(HDC hdc)
{
}
