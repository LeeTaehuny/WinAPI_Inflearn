#pragma once
#include "Scene.h"

// 실제 게임 씬 클래스입니다.
class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene() override;

	// 부모 클래스의 함수를 오버라이드 합니다.
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	// 플레이어 객체를 저장할 변수를 선언합니다.
	// * 헤더파일에서는 include를 최소화하는 것이 좋으므로 전방 선언을 통해 cpp에서 추가해줍시다.
	
	// ** 게임의 장면에서 이렇게 플레이어 하나만 들고 있는 것은 말이 안되는 상황입니다.
	// ** 테스트하기에는 좋았지만 구조를 변경해줍니다.
	//class Player* _player = nullptr;

	// 오브젝트 관리 방법
	// 1. 씬에 등장하는 모든 오브젝트를 해당 씬에서 관리합니다.
	// * 해당 씬의 상위 클래스인 Scene 클래스에 vector, list 등의 자료구조로 오브젝트를 관리합니다.
	// 2. 씬에 등장하는 모든 오브젝트를 오브젝트 매니저를 생성해 해당 매니저 클래스에서 관리합니다.
};

