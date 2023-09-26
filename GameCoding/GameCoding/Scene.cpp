#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "UI.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::Init()
{

	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->BeginPlay();
		}
	}

	for (UI* ui : _uis)
	{
		ui->BeginPlay();
	}
}

void Scene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	GET_SINGLE(CollisionManager)->Update();

	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->Tick();
		}
	}

	for (UI* ui : _uis)
	{
		ui->Tick();
	}
}

void Scene::Render(HDC hdc)
{
	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->Render(hdc);
		}
	}

	for (UI* ui : _uis)
	{
		ui->Render(hdc);
	}
}

void Scene::AddActor(Actor* actor)
{
	// 만약 액터가 존재하지 않는다면?
	if (actor == nullptr)
	{
		// 종료합니다.
		return;
	}

	// 액터가 존재하는 경우입니다.
	// * 액터의 레이어 타입에 맞는 목록에 해당 액터를 추가합니다.
	_actors[actor->GetLayer()].push_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
	// 만약 액터가 존재하지 않는다면?
	if (actor == nullptr)
	{
		// 종료합니다.
		return;
	}

	// 액터 레이어와 일치하는 목록을 받아옵니다.
	vector<Actor*>& v = _actors[actor->GetLayer()];

	// 목록에서 해당 액터를 제거합니다.
	v.erase(std::remove(v.begin(), v.end(), actor));
}