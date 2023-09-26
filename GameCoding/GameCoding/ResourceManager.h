#pragma once

class ResourceBase;
class Texture;
class Sprite;
class Flipbook;
class Tilemap;

class ResourceManager
{
	DECLARE_SINGLE(ResourceManager);
public:
	~ResourceManager();

public:
	// 초기화 함수를 선언합니다.
	// * 윈도우 핸들 번호를 필요로 하는 리소스가 있을 수 있으므로 매개변수를 추가합니다.
	// * 초기화하는 동시에 경로를 지정하기 위해 매개변수를 추가합니다.
	void Init(HWND hWnd, fs::path resourcePath);
	// 소멸할 때 모든 것을 삭제하기 위한 함수를 선언합니다.
	void Clear();

	// 리소스 저장 경로를 반환하는 함수를 정의합니다.
	const fs::path& GetResourcePath() { return _resourcePath; }

	// 특정 키에 해당하는 텍스처를 반환하는 함수를 정의합니다.
	Texture* GetTexture(const wstring& key) { return _textures[key]; }
	// 텍스처를 불러오는 함수를 선언합니다.
	Texture* LoadTexture(const wstring& key, const wstring& path, uint32 transparent = RGB(255, 0, 255));

	// 특정 키에 해당하는 스프라이트를 반환하는 함수를 정의합니다.
	Sprite* GetSprite(const wstring& key) { return _sprites[key]; }
	// 텍스처를 스프라이트로 만들어 반환하기 위한 함수를 선언합니다.
	Sprite* CreateSprite(const wstring& key, Texture* texture, int32 x = 0, int32 y = 0, int32 cx = 0, int32 cy = 0);

	// 특정 키에 해당하는 애니메이션을 반환하는 함수를 정의합니다.
	Flipbook* GetFilpbook(const wstring& key) { return _flipbooks[key]; }
	// 특정 키에 해당하는 애니메이션을 생성하기 위한 함수를 선언합니다.
	// * 애니메이션별로 설정할 값들이 너무 다르기 때문에 객체만 생성하여 리턴해주는 방식으로 구현합니다.
	Flipbook* CreateFlipbook(const wstring& key);

	// 특정 키에 해당하는 타일맵을 반환하는 함수를 정의합니다.
	Tilemap* GetTilemap(const wstring& key) { return _tilemaps[key]; }
	// 특정 키에 해당하는 타일맵을 생성하기 위한 함수를 선언합니다.
	Tilemap* CreateTilemap(const wstring& key);

	// 타일맵을 저장 / 로드하기 위한 함수를 선언합니다.
	void SaveTilemap(const wstring& key, const wstring& path);
	Tilemap* LoadTilemap(const wstring& key, const wstring& path);

private:
	// 윈도우 핸들 번호를 저장할 변수를 선언합니다.
	HWND _hWnd = {};

	// 절대 파일 경로를 저장하기 위한 변수를 선언합니다.
	fs::path _resourcePath;

	// (키값[파일경로], 리소스 객체) 형태로 Texture 객체들을 정렬하지 않고 저장하는 컨테이너를 선언합니다.
	unordered_map<wstring, Texture*> _textures;
	// (키값[파일경로], 리소스 객체) 형태로 Sprite 객체들을 정렬하지 않고 저장하는 컨테이너를 선언합니다.
	unordered_map<wstring, Sprite*> _sprites;
	// (키값[파일경로], 리소스 객체) 형태로 Flipbook 객체들을 정렬하지 않고 저장하는 컨테이너를 선언합니다.
	unordered_map<wstring, Flipbook*> _flipbooks;

	// (키값[파일경로], 리소스 객체) 형태로 Tilemap 객체들을 정렬하지 않고 저장하는 컨테이너를 선언합니다.
	unordered_map<wstring, Tilemap*> _tilemaps;
};

