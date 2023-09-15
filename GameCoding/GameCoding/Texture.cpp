#include "pch.h"
#include "Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

Texture* Texture::LoadBmp(HWND hwnd, const wstring& path)
{
	// DC를 추출합니다.
	HDC hdc = ::GetDC(hwnd);

	// hdc와 호환되는 dc를 생성합니다.
	_hdc = ::CreateCompatibleDC(hdc);
	// 이미지를 비트맵에 저장합니다.
	_bitmap = (HBITMAP)::LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	// 만약 비트맵이 존재하지 않는다면?
	if (_bitmap == 0)
	{
		// 이미지 로딩에 실패했다는 경고 메시지를 생성합니다.
		::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);
	}

	HBITMAP prev = (HBITMAP)::SelectObject(_hdc, _bitmap);
	::DeleteObject(prev);

	// 로드한 이미지에 대한 정보를 얻어옵니다.
	BITMAP bit = {};
	::GetObject(_bitmap, sizeof(BITMAP), &bit);

	// 로드한 이미지의 사이즈들을 저장합니다.
	_size.x = bit.bmWidth;
	_size.y = bit.bmHeight;

	return this;
}

HDC Texture::GetDC()
{
	return _hdc;
}
