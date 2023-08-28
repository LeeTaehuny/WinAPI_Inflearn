#pragma once

// class ResourceBase;
class LineMesh;

class ResourceManager
{
	DECLARE_SINGLE(ResourceManager);
public:
	~ResourceManager();

public:
	// 초기화 함수를 선언합니다.
	void Init();
	// 소멸할 때 모든 것을 삭제하기 위한 함수를 선언합니다.
	void Clear();

	// test
	// * 키값을 통해 LineMesh를 반환하는 Getter 함수를 선언합니다.
	const LineMesh* GetLineMesh(wstring key);

private:
	// (키값[파일경로], 리소스 객체) 형태로 LineMesh 객체들을 정렬하지 않고 저장하는 컨테이너를 선언합니다.
	unordered_map<wstring, LineMesh*> _lineMeshes;
};

