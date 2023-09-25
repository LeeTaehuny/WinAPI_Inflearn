#include "pch.h"
#include "Button.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Sprite.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::BeginPlay()
{
	Super::BeginPlay();

	// 시작과 동시에 버튼을 디폴트 상태로 설정합니다.
	SetButtonState(BS_Default);

	//AddOnClickDelegate(this, &Button::OnClickButton);
}

void Button::Tick()
{
	Super::Tick();

	// 마우스의 위치를 받아옵니다.
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	// 프레임 시간을 받아옵니다.
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 만약 버튼이 클릭 상황이라면?
	if (_state == BS_Clicked)
	{
		// 시간을 누적합니다.
		_sumTime += deltaTime;

		// 만약 누적 시간이 0.2초보다 커진다면?
		if (_sumTime >= 0.2f)
		{
			// 누적 시간을 초기화합니다.
			_sumTime = 0.0f;
			// 버튼을 디폴트 상태로 변경합니다.
			SetButtonState(BS_Default);
		}
	}

	// 만약 마우스가 버튼 영역 내부에 들어왔다면?
	if (IsMouseInRect())
	{
		// 만약 마우스를 누르고 있는 상태라면?
		if (GET_SINGLE(InputManager)->GetButton(KeyType::LeftMouse))
		{
			// 버튼의 상태를 누르고 있는 상태로 변경합니다.
			SetButtonState(BS_Pressed);

			// TODO : OnPressed
		}
		// 마우스를 뗀 상황
		else
		{
			// 이전 프레임에서의 버튼 상태가 Pressed였다면?
			if (_state == BS_Pressed)
			{
				// 이제는 마우스를 뗏으므로 클릭 상태로 변경합니다.
				SetButtonState(BS_Clicked);

				// TODO : OnClicked
				if (_onClick)
				{
					_onClick();
				}
			}
		}
	}
	else
	{
		// 마우스가 영역 내부에 없으므로 버튼의 상태를 디폴트 상태로 변경합니다.
		SetButtonState(BS_Default);
	}
}

void Button::Render(HDC hdc)
{
	// 만약 현재 스프라이트가 존재한다면?
	if (_currentSprite)
	{
		// 이미지를 출력합니다.
		::TransparentBlt(hdc,
			(int32)_pos.x - _size.x / 2,
			(int32)_pos.y - _size.y / 2,
			_size.x,
			_size.y,
			_currentSprite->GetDC(),
			_currentSprite->GetPos().x,
			_currentSprite->GetPos().y,
			_currentSprite->GetSize().x,
			_currentSprite->GetSize().y,
			_currentSprite->GetTransparent()
		);
	}
	// 스프라이트가 존재하지 않는다면?
	else
	{
		// 테스트 출력
		Utils::DrawRect(hdc, _pos, _size.x, _size.y);
	}

}

void Button::SetButtonState(ButtonState state)
{
	// 버튼의 상태를 설정합니다.
	_state = state;

	// 만약 해당 상태에 대한 스프라이트가 존재한다면?
	if (_sprites[state])
	{
		// 현재 스프라이트를 해당 스프라이트로 설정합니다.
		SetCurrentSprite(_sprites[state]);
	}
}
