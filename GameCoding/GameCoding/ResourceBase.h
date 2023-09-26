#pragma once

class ResourceBase
{
public:
	ResourceBase();
	virtual ~ResourceBase();

	// 파일을 로드하기 위한 가상 함수를 선언합니다.
	virtual void LoadFile(const wstring& path);
	// 파일을 저장하기 위한 가상 함수를 선언합니다.
	virtual void SaveFile(const wstring& path);
};

