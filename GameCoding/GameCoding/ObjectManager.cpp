#include "pch.h"
#include "ObjectManager.h"
#include "Object.h"

ObjectManager::~ObjectManager()
{
	Clear();
}

void ObjectManager::Add(Object* object)
{
	// null 체크
	if (object == nullptr)
	{
		return;
	}

	// 같은 오브젝트가 이중으로 추가되면 문제가 발생할 수도 있습니다.
	// * 기존 벡터 컨테이너에서 해당 오브젝트가 있는지 검사합니다.
	// * find() : 특정 val을 찾아 해당 iterator를 반환합니다. (없으면 end() 반환)
	auto findIt = std::find(_objects.begin(), _objects.end(), object);

	// 이미 해당 오브젝트가 배열에 존재하는 경우 함수를 종료합니다.
	if (findIt != _objects.end())
	{
		return;
	}

	// 벡터 컨테이너에 해당 오브젝트를 추가합니다.
	_objects.push_back(object);
}

void ObjectManager::Remove(Object* object)
{
	// null 체크
	if (object == nullptr)
	{
		return;
	}

	// 벡터 컨테이너에서 특정 object을 제거합니다.
	// * remove() : 삭제해야 하는 것들을 뒤로 모아 해당 지점의 iterator를 반환합니다.
	auto it = std::remove(_objects.begin(), _objects.end(), object);
	// * 즉, 반환받은 it부터 end()까지 직접 삭제해줘야 합니다.
	_objects.erase(it, _objects.end());

	// TODO : 해당 오브젝트의 삭제를 고민해봐야 합니다.
	delete object;
}

void ObjectManager::Clear()
{
	// 모든 요소를 순회하며 객체를 삭제합니다.
	std::for_each(_objects.begin(), _objects.end(), [=](Object* obj) { delete obj; });
	// 해당 벡터를 비워줍니다.
	_objects.clear();
}
