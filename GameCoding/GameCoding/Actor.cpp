#include "pch.h"
#include "Actor.h"
#include "Component.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::BeginPlay()
{
	for (Component* component : _components)
	{
		component->BeginPlay();
	}
}

void Actor::Tick()
{
	for (Component* component : _components)
	{
		component->TickComponent();
	}
}

void Actor::Render(HDC hdc)
{
	for (Component* component : _components)
	{
		component->Render(hdc);
	}
}

void Actor::AddComponent(Component* component)
{
	// 만약 컴포넌트가 존재하지 않는다면?
	if (component == nullptr)
	{
		// 종료합니다.
		return;
	}

	// 컴포넌트가 존재하는 상황입니다.
	
	// 컴포넌트의 주인을 설정합니다.
	component->SetOwner(this);
	// 컴포넌트를 배열에 추가합니다.
	_components.push_back(component);
}

void Actor::RemoveComponent(Component* component)
{
	// 삭제할 컴포넌트를 찾습니다.
	auto findIt = std::find(_components.begin(), _components.end(), component);

	// 만약 해당 컴포넌트가 존재하지 않는다면?
	if (findIt == _components.end())
	{
		// 종료합니다.
		return;
	}

	// 해당 컴포넌트를 삭제합니다.
	_components.erase(findIt);
}
