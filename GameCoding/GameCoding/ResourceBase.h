#pragma once

class ResourceBase
{
public:
	ResourceBase();
	virtual ~ResourceBase();

	// ������ �ε��ϱ� ���� ���� �Լ��� �����մϴ�.
	virtual void LoadFile(const wstring& path);
	// ������ �����ϱ� ���� ���� �Լ��� �����մϴ�.
	virtual void SaveFile(const wstring& path);
};

