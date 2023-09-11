#include "pch.h"
#include "Bullet.h"
#include "FortressScene.h"

#include "TimeManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"

Bullet::Bullet() : Object(ObjectType::Projectile)
{

}

Bullet::~Bullet()
{

}

void Bullet::Init()
{
	_radius = 20.0f;
}

void Bullet::Update()
{
	// 프레임 시간을 저장합니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 바람, 중력 등 요소는 여기서 적용

	// 총알을 이동시켜줍니다.
	_pos += _speed * deltaTime;

	// 만약 총알의 y 좌표가 윈도우 세로 크기의 1.5배보다 커지거나 작아진다면?
	if (_pos.y > GWinSizeY * 1.5f || _pos.y < -GWinSizeY * 1.5f)
	{
		// 씬을 불러와 저장합니다.
		// * FortressScene인 경우만 체크하도록 dynamic_cast를 사용합니다.
		FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

		// 만약 씬이 존재한다면?
		if (scene)
		{
			// 턴을 변경해줍니다.
			scene->ChangePlayerTurn();
		}
		 
		// 총알을 삭제 시켜줍니다.
		GET_SINGLE(ObjectManager)->Remove(this);
		// 업데이트를 종료합니다.
		return;
	}
}

void Bullet::Render(HDC hdc)
{
	// 테스트로 총알을 간단하게 그려줍니다.
	Utils::DrawCircle(hdc, _pos, static_cast<int>(_radius));
}
