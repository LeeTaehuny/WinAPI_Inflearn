#include "pch.h"
#include "ResourceManager.h"
#include "LineMesh.h"

ResourceManager::~ResourceManager()
{
	// 모든 내용을 삭제합니다.
	Clear();
}

void ResourceManager::Init()
{
	// LineMesh 객체를 생성합니다.
	LineMesh* mesh = new LineMesh();
	// 저장된 데이터를 로드합니다. (테스트로 player.txt라는 이름의 파일을 로드하도록 설정)
	mesh->Load(L"Player.txt");

	// 로드된 mesh를 _lineMeshes 컨테이너에 추가합니다.
	_lineMeshes[L"Player"] = mesh;

}

void ResourceManager::Clear()
{
	for (auto mesh : _lineMeshes)
	{
		SAFE_DELETE(mesh.second);
	}

	_lineMeshes.clear();
}

const LineMesh* ResourceManager::GetLineMesh(wstring key)
{
	// 해당 키 값에 맞는 위치를 저장합니다.
	auto findIt = _lineMeshes.find(key);

	// 만약 해당 위치가 존재하지 않는다면?
	if (findIt == _lineMeshes.end())
	{
		// 찾지 못했으므로 nullptr를 반환합니다.
		return nullptr;
	}

	// 해당 위치의 객체를 반환합니다.
	return findIt->second;
}
