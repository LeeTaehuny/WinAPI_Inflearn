﻿#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Tilemap.h"
#include "Sound.h"

ResourceManager::~ResourceManager()
{
	// 모든 내용을 삭제합니다.
	Clear();
}

void ResourceManager::Init(HWND hWnd, fs::path resourcePath)
{
	_resourcePath = resourcePath;
	_hWnd = hWnd;

}

void ResourceManager::Clear()
{
	// 배열들을 순회하며 객체 정보를 삭제해줍니다.
	for (auto& item : _textures)
	{
		SAFE_DELETE(item.second);
	}

	for (auto& item : _sprites)
	{
		SAFE_DELETE(item.second);
	}

	for (auto& item : _flipbooks)
	{
		SAFE_DELETE(item.second);
	}

	for (auto& item : _tilemaps)
	{
		SAFE_DELETE(item.second);
	}

	// _textures 배열을 비워줍니다.
	_textures.clear();
	// _sprites 배열을 비워줍니다.
	_sprites.clear();
	// _flipbooks 배열을 비워줍니다.
	_flipbooks.clear();
	// _tilemaps 배열을 비워줍니다.
	_tilemaps.clear();
}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent)
{
	// 만약 해당 키가 _textures 배열에 있다면?
	if (_textures.find(key) != _textures.end())
	{
		// 키에 해당하는 텍스처를 반환합니다.
		return _textures[key];
	}

	// 입력받은 키에 해당되는 텍스처가 없는 상황입니다.

	// 전체 경로를 구해줍니다.
	// * _resourcePath : 절대 파일경로
	// * path		   : 상대 파일 경로
	// -> fullPath : 전체 파일 경로(절대 + 상대 파일 경로)
	fs::path fullPath = _resourcePath / path;

	// 텍스처를 생성합니다.
	Texture* texture = new Texture();
	// 텍스처에 이미지 파일을 저장합니다.
	texture->LoadBmp(_hWnd, fullPath.c_str());
	// 텍스처에 적용할 투명 색을 저장합니다.
	texture->SetTransparent(transparent);

	// 입력받은 키에 위에서 생성한 텍스쳐를 쌍으로 배열에 추가해줍니다.
	_textures[key] = texture;

	// 생성된 texture를 반환합니다.
	return texture;
}

Sprite* ResourceManager::CreateSprite(const wstring& key, Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
{
	// 만약 해당 키가 _sprites 배열에 있다면?
	if (_sprites.find(key) != _sprites.end())
	{
		// 해당 스프라이트를 반환합니다.
		return _sprites[key];
	}

	// 만약 자르고 싶은 사이즈가 0(기본값)이라면?
	if (cx == 0)
	{
		// 텍스쳐의 크기로 설정합니다.
		cx = texture->GetSize().x;
	}

	if (cy == 0)
	{
		// 텍스쳐의 크기로 설정합니다.
		cy = texture->GetSize().y;
	}

	// 스프라이트가 없는 경우입니다.

	// 새로운 스프라이트를 생성합니다.
	Sprite* sprite = new Sprite(texture, x, y, cx, cy);
	// _sprites 배열에 추가합니다.
	_sprites[key] = sprite;

	// 해당 스프라이트를 반환합니다.
	return sprite;
}

Flipbook* ResourceManager::CreateFlipbook(const wstring& key)
{
	// 만약 애니메이션들의 목록에서 키가 존재한다면?
	if (_flipbooks.find(key) != _flipbooks.end())
	{
		// 해당 키값을 가진 애니메이션을 반환합니다.
		return _flipbooks[key];
	}

	// 애니메이션이 없는 경우입니다.

	// 새로운 애니메이션을 생성합니다.
	Flipbook* fb = new Flipbook();
	// _flipbooks 배열에 추가합니다.
	_flipbooks[key] = fb;

	// 해당 애니메이션을 반환합니다.
	return fb;
}

Tilemap* ResourceManager::CreateTilemap(const wstring& key)
{
	// 만약 타일맵 목록에서 키가 존재한다면?
	if (_tilemaps.find(key) != _tilemaps.end())
	{
		// 해당 키값을 가진 타일맵을 반환합니다.
		return _tilemaps[key];
	}

	// 타일맵이 없는 경우입니다.

	// 새로운 타일맵을 생성합니다.
	Tilemap* tm = new Tilemap();
	// _tilemaps에 추가합니다.
	_tilemaps[key] = tm;

	// 해당 타일맵을 반환합니다.
	return tm;
}

void ResourceManager::SaveTilemap(const wstring& key, const wstring& path)
{
	// 키에 해당하는 타일맵을 받아옵니다.
	Tilemap* tm = GetTilemap(key);
	// 전체 경로를 설정합니다.
	fs::path fullPath = _resourcePath / path;

	// 전체 경로 위치에 파일을 저장합니다.
	tm->SaveFile(fullPath);
}

Tilemap* ResourceManager::LoadTilemap(const wstring& key, const wstring& path)
{
	// 타일맵 포인터 변수를 선언합니다.
	Tilemap* tm = nullptr;
	// 만약 tilemaps에 키 값에 해당하는 타일맵이 없다면?
	if (_tilemaps.find(key) == _tilemaps.end())
	{
		// 새로운 타일맵을 추가합니다.
		_tilemaps[key] = new Tilemap();
	}

	// 위에서 생성한 타일맵 포인터 변수에 찾은(생성한) 타일맵을 넣어줍니다.
	tm = _tilemaps[key];

	// 전체 경로를 설정합니다.
	fs::path fullPath = _resourcePath / path;
	// 전체 경로 위치에 있는 파일을 불러옵니다.
	tm->LoadFile(fullPath);

	return tm;
}

Sound* ResourceManager::LoadSound(const wstring& key, const wstring& path)
{
	// 이미 로드할 사운드가 존재한다면 해당 사운드를 반환합니다.
	if (_sounds.find(key) != _sounds.end())
	{
		return _sounds[key];
	}

	// 사운드가 _sounds에 존재하지 않는 상황입니다.
	// 전체 경로를 설정합니다.
	fs::path fullPath = _resourcePath / path;

	// 사운드 객체를 생성합니다.
	Sound* sound = new Sound();
	// 사운드 객체의 wave 파일을 로드합니다.
	sound->LoadWave(fullPath);
	// _sounds에 추가합니다.
	_sounds[key] = sound;

	return sound;
}
