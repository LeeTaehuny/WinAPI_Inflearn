#pragma once
#include "UI.h"
// UI들을 관리하는 UI 시트 (UI들을 묶어가지고 관리하는 용도로 사용할 클래스)

class Sprite;

class Panel : public UI
{
	using Super = UI;
public:
	Panel();
	virtual ~Panel() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void AddChild(UI* ui);
	bool RemoveChild(UI* ui);

private:
	vector<UI*> _children;
};

